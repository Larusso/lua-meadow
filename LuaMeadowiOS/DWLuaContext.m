//
//  DWLuaContext.m
//  LuaMeadow
//
//  Created by Larusso on 01.09.13.
//  Copyright (c) 2013 Larusso. All rights reserved.
//

#import "DWLuaContext.h"
#import "DWLuaModuleDescription.h"
#import "DWLuaClassBridgeDescription.h"
#import "objc/runtime.h"

static DWLuaContext *context;

void stackdump_g(lua_State *l)
{
    int i;
    int top = lua_gettop(l);
    
    printf("total in stack %d\n", top);
    
    for (i = 1; i <= top; i++)
    { /* repeat for each level */
        int t = lua_type(l, i);
        switch (t)
        {
            case LUA_TSTRING: /* strings */
                printf("string: '%s'\n", lua_tostring(l, i));
                break;
            case LUA_TBOOLEAN: /* booleans */
                printf("boolean %s\n", lua_toboolean(l, i) ? "true" : "false");
                break;
            case LUA_TNUMBER: /* numbers */
                printf("number: %g\n", lua_tonumber(l, i));
                break;
            default: /* other values */
                printf("%s\n", lua_typename(l, t));
                break;
        }
        printf(" "); /* put a separator */
    }
    printf("\n"); /* end the listing */
}

static int callMethod(lua_State *L)
{
    int n = lua_gettop(L); // Number of arguments
    if (n == 0)
        return luaL_error(L, "Got %d arguments expected at least 1 (class)", n);
    return 0;
}

static int initClassMetatable(lua_State *L, const char* mt, const char* ns)
{
    lua_pop(L, 1);
    luaL_newmetatable(L, mt);
    
    DWLuaModuleDescription *moduleDescriptor = [[context modules] objectForKey:to_objcString(ns)];
    DWLuaClassBridgeDescription *classDescriptor = [[moduleDescriptor registeredClassNames] objectForKey:to_objcString(mt)];
    
    NSSet* selectors = [classDescriptor selectors];
    for(NSString* selector in selectors) {
        lua_pushcfunction(L, callMethod);
        lua_setfield(L, -2, to_cString(selector));
    }
        
    return 1;
}

static int initClassFactoryMetatable(lua_State *L, const char* ns, const char* className)
{
    const char* mt = to_cString([NSString stringWithFormat:@"%s.%s",ns,className]);
    luaL_newmetatable(L, to_cString([NSString stringWithFormat:@"%s.%s",mt,"factory"]));
    
    lua_pushstring(L, mt);
    lua_setfield(L, -2, "__mt");
    
    lua_pushstring(L, ns);
    lua_setfield(L, -2, "__ns");
    
    lua_pushstring(L, className);
    lua_setfield(L, -2, "__class");
    
    lua_pushstring(L, "protected");
    lua_setfield(L, -2, "__metatable");
    
    return 1;
}

static int newInstance(lua_State *L)
{
    int n = lua_gettop(L); // Number of arguments
    if (n != 1)
        return luaL_error(L, "Got %d arguments expected 1 (class)", n);
    // First argument is now a table that represent the class to instantiate
    luaL_checktype(L, 1, LUA_TTABLE);
    
    lua_getmetatable(L, 1);

    lua_getfield(L, -1, "__class");
    const char* className = lua_tostring(L, -1);
    lua_pop(L, 1);
    
    lua_getfield(L, -1, "__mt");
    const char* mt = lua_tostring(L, -1);
    lua_pop(L, 1);
    
    lua_getfield(L, -1, "__ns");
    const char* ns = lua_tostring(L, -1);
    lua_pop(L, 1);
    
    lua_newtable(L);
    lua_pushvalue(L, -2);
    luaL_getmetatable(L, mt);
    
    if(lua_isnil(L, -1))
    {
        initClassMetatable(L,mt,ns);
    }
    
    lua_setfield(L, -2, "__index");
        
    lua_setmetatable(L, -2);
    
    // Allocate memory for a pointer to to object
    Class class = NSClassFromString(to_objcString(className));
    struct objc_object *go = (__bridge  struct objc_object *)([[class alloc] init]);
    struct objc_object **lgo = (struct objc_object **)lua_newuserdata(L, sizeof(class));
    *lgo = go;
    
    lua_setfield(L, -2, "__self");
    return 1;
}

static int destroyInst(lua_State *L)
{
    return 0;
}

static int registerClassTable(lua_State *L)
{
    static const luaL_Reg gClassFactoryFuncs[] = {
        // Creation
        {"new", newInstance},
        {NULL, NULL}
    };
    
    luaL_newlib(L, gClassFactoryFuncs );
    return 1;
}



static int luaOpen_module(lua_State *L)
{
    const char* moduleCName = lua_tostring(L, -1);
    NSString * moduleName = to_objcString(moduleCName);
    DWLuaModuleDescription *description = [[context modules] objectForKey:moduleName];
    
    if([[description registeredClassNames] count] > 0)
    {
        lua_newtable(L);
        NSArray *classDescriptors = [[description registeredClassNames] allValues];
        for(DWLuaClassBridgeDescription* classBrideDescriptor in classDescriptors) {
            NSString *className = NSStringFromClass([classBrideDescriptor class]);
            lua_newtable(L);
            
            initClassFactoryMetatable(L,moduleCName, to_cString(className));
            lua_setmetatable(L, -2);
            
            lua_pushcfunction(L, newInstance);
            lua_setfield(L, -2, "new");
            
            lua_setfield(L, -2, to_cString([classBrideDescriptor className]));
        }
        
        return 1;
    }
    
    return 0;
}

@implementation DWLuaContext
@synthesize modules=_modules;

- (id) init
{
    self = [super init];
    if(self)
    {
        state = luaL_newstate();
        context = self;
        registerClassTable(state);
        luaL_newmetatable(state, "class.factory");
        lua_pushvalue(state, -2);
        lua_setfield(state, -2, "__index");
        
        _modules = [[NSMutableDictionary alloc]init];
        luaL_openlibs(state);
    }
    return self;
}

- (void)doFile:(NSString *)path
{
    const char *scriptPath = [path cStringUsingEncoding:[NSString defaultCStringEncoding]];
    lua_settop(state, 0); //empty the lua stack
    if (luaL_dofile(state, scriptPath))
    {
        fprintf(stderr, "error: %s\n", lua_tostring(state, -1));
        lua_pop(state, 1);
        exit(1);
    }
    assert(lua_gettop(state) == 0);
}

- (void)registerModule:(DWLuaModuleDescription *)module;
{
    [_modules setObject:module forKey:[module name]];
    const char *modname = [[module name] cStringUsingEncoding:[NSString defaultCStringEncoding]];
    luaL_requiref(state, modname, luaOpen_module, 1);
}

@end

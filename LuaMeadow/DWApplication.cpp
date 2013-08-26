//
//  DWApplication.cpp
//  LuaMeadow
//
//  Created by Larusso on 25.08.13.
//  Copyright (c) 2013 Larusso. All rights reserved.
//

#include "DWApplication.h"
#include "DWMediator.h"

#pragma mark - LUA stack manipulation

extern "C" {

void stackdump_g(lua_State *l)
{
    int i;
    int top = lua_gettop(l);

    printf("total in stack %d\n", top);

    for (i = 1; i <= top; i++)
    {  /* repeat for each level */
        int t = lua_type(l, i);
        switch (t)
        {
            case LUA_TSTRING:  /* strings */
                printf("string: '%s'\n", lua_tostring(l, i));
                break;
            case LUA_TBOOLEAN:  /* booleans */
                printf("boolean %s\n", lua_toboolean(l, i) ? "true" : "false");
                break;
            case LUA_TNUMBER:  /* numbers */
                printf("number: %g\n", lua_tonumber(l, i));
                break;
            default:  /* other values */
                printf("%s\n", lua_typename(l, t));
                break;
        }
        printf("  ");  /* put a separator */
    }
    printf("\n");  /* end the listing */
}

static int newMediator(lua_State *L)
{
    int n = lua_gettop(L);  // Number of arguments
    if (n != 1)
        return luaL_error(L, "Got %d arguments expected 1 (class)", n);
    // First argument is now a table that represent the class to instantiate
    luaL_checktype(L, 1, LUA_TTABLE);

    lua_newtable(L);      // Create table to represent instance

    // Set first argument of new to metatable of instance
    lua_pushvalue(L, 1);
    lua_setmetatable(L, -2);

    // Do function lookups in metatable
    lua_pushvalue(L, 1);
    lua_setfield(L, 1, "__index");

    // Allocate memory for a pointer to to object
    DWMediator **s = (DWMediator **) lua_newuserdata(L, sizeof(DWMediator *));

    //double x = luaL_checknumber (L, 2);
    //double y = luaL_checknumber (L, 3);
    //double dir = luaL_checknumber (L, 4);
    //double speed = luaL_checknumber (L, 5);

    *s = new DWMediator();

    // Get metatable 'dire.Mediator' store in the registry
    luaL_getmetatable(L, "dire.Mediator");

    // Set user data for Sprite to use this metatable
    lua_setmetatable(L, -2);

    // Set field '__self' of instance table to the sprite user data
    lua_setfield(L, -2, "__self");

    return 1;
}

static int printMediator(lua_State *L)
{
    int n = lua_gettop(L);  // Number of arguments
    if (n != 1)
        return luaL_error(L, "Got %d arguments expected 1 (class)", n);
    // First argument is now a table that represent the class to instantiate
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L,1,"__self");
    DWMediator **mediator = static_cast<DWMediator **>(luaL_checkudata(L, -1, "dire.Mediator"));
    (*mediator)->printType();
    return 0;
}
    
    static int moveMediator(lua_State *L)
    {
        int n = lua_gettop(L);  // Number of arguments
        if (n != 3)
            return luaL_error(L, "Got %d arguments expected 3 (class,x,y)", n);
        
        luaL_checktype(L, 1, LUA_TTABLE);
        luaL_checktype(L, 2, LUA_TNUMBER);
        luaL_checktype(L, 3, LUA_TNUMBER);
        
        int x = luaL_checknumber (L, 2);
        int y = luaL_checknumber (L, 3);
        
        lua_getfield(L,1,"__self");
        DWMediator **mediator = static_cast<DWMediator **>(luaL_checkudata(L, -1, "dire.Mediator"));
        (*mediator)->move(x, y);
        
        return 0;
    }

static int destroyMediator(lua_State *L)
{
    DWMediator *mediator = 0;

    //checkUserData(L, "dire.Mediator", mediator);
    mediator->release();
    return 0;
}


static int registerMediatorTable(lua_State *L)
{
    static const luaL_Reg gMediatorFuncs[] = {
            // Creation
            {"new", newMediator},
            {"print", printMediator},
            {"move",moveMediator},
            {"__gc", destroyMediator},
            {NULL, NULL}
    };

    luaL_newlib(L, gMediatorFuncs );
    return 1;
}

static int luaOpen_direwolf(lua_State *L)
{
    registerMediatorTable(L);

    luaL_newmetatable(L, "dire.Mediator");
    lua_pushvalue(L, -2);
    lua_setfield(L, -2, "__index");

    lua_newtable(L);
    lua_pushvalue(L, -3);
    lua_setfield(L, -2, "Mediator");
    return 1;
}
}


DWApplication::DWApplication()
{
    L = luaL_newstate();
    luaL_openlibs(L);
}

DWApplication::~DWApplication()
{
    lua_close(L);
}

void DWApplication::runScript()
{
    lua_settop(L, 0); //empty the lua stack
    if (luaL_dofile(L, "./luascript.lua"))
    {
        fprintf(stderr, "error: %s\n", lua_tostring(L, -1));
        lua_pop(L, 1);
        exit(1);
    }
    assert(lua_gettop(L) == 0); //empty the lua stack
}

void DWApplication::registerMediatorType()
{
    std::cout << "set the mediator class in lua" << std::endl;
    luaL_openlibs(L);
    luaL_requiref(L, "direwolf", luaOpen_direwolf, 1);
}

void DWApplication::registerListType()
{
    std::cout << "Set the list object in lua" << std::endl;
    luaL_newmetatable(L, "ListMT");
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index"); // ListMT .__index = ListMT
    //lua_pushcclosure(L, (l_list_push), 0);
    //lua_pushcfunction(L, l_list_push);
    lua_setfield(L, -2, "push"); // push in lua will call l_list_push in C++
    // lua_pushcfunction(L, l_list_pop);
    lua_setfield(L, -2, "pop"); // pop in lua will call l_list_pop in C++
}

void DWApplication::run()
{

    registerMediatorType();
    runScript();
}
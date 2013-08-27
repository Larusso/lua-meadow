//
//  DWApplication.cpp
//  LuaMeadow
//
//  Created by Larusso on 25.08.13.
//  Copyright (c) 2013 Larusso. All rights reserved.
//

#include "DWApplication.h"
#include <stdio.h>
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#pragma mark - LUA stack manipulation
extern "C" {
    extern int luaopen_direwolf(lua_State* L);
    
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
}

DWApplication::DWApplication()
{
    L = luaL_newstate();
    luaL_openlibs(L);
    luaopen_base(L);
    luaopen_direwolf(L);
}

DWApplication::~DWApplication()
{
    lua_close(L);
}

void DWApplication::runScript()
{
    //lua_settop(L, 0); //empty the lua stack
    if (luaL_dofile(L, "./luascript.lua"))
    {
        fprintf(stderr, "error: %s\n", lua_tostring(L, -1));
        lua_pop(L, 1);
        exit(1);
    }
    //assert(lua_gettop(L) == 0); //empty the lua stack
}

void DWApplication::registerMediatorType()
{
    std::cout << "set the mediator class in lua" << std::endl;
}

void DWApplication::registerListType()
{
    std::cout << "Set the list object in lua" << std::endl;
}

void DWApplication::run()
{
    runScript();
}
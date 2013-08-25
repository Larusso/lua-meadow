//
//  DWApplication.h
//  LuaMeadow
//
//  Created by Larusso on 25.08.13.
//  Copyright (c) 2013 Larusso. All rights reserved.
//
#include <lua.hpp>
#include <iostream>
#include <list>
#include <assert.h>

extern "C" {
    static int l_list_push(lua_State *L) { // Push elements from LUA
        assert(lua_gettop(L) == 2); // check that the number of args is exactly 2
        std::list<int> **ud = static_cast<std::list<int> **>(luaL_checkudata(L,1, "ListMT")); // first arg is the list
        int v =luaL_checkint(L,2); // seconds argument is the integer to be pushed to the std::list<int>
        (*ud)->push_back(v); // perform the push on C++ object through the pointer stored in user data
        return 0; // we return 0 values in the lua stack
    }
    static int l_list_pop(lua_State *L) {
        assert(lua_gettop(L) == 1); // check that the number of args is exactly 1
        std::list<int> **ud = static_cast<std::list<int> **>(luaL_checkudata(L, 1, "ListMT")); // first arg is the userdata
        if ((*ud)->empty()) {
            lua_pushnil(L);
            return 1; // if list is empty the function will return nil
        }
        lua_pushnumber(L,(*ud)->front()); // push the value to pop in the lua stack
                                          // it will be the return value of the function in lua
        (*ud)->pop_front(); // remove the value from the list
        return 1; //we return 1 value in the stack
    }
}


#ifndef __LuaMeadow__DWApplication__
#define __LuaMeadow__DWApplication__

#include <iostream>

class DWApplication
{
public:
    DWApplication();
    ~DWApplication();
    void run();
    
    /* data */
private:
    lua_State *L;
    std::list<int> theList;
    void registerListType();
    void runScript();
};


#endif /* defined(__LuaMeadow__DWApplication__) */

//
//  DWApplication.cpp
//  LuaMeadow
//
//  Created by Larusso on 25.08.13.
//  Copyright (c) 2013 Larusso. All rights reserved.
//

#include "DWApplication.h"

DWApplication::DWApplication() {
    L = luaL_newstate();
    luaL_openlibs(L);
}

DWApplication::~DWApplication() {
    lua_close(L);
}

void DWApplication::runScript() {
    lua_settop(L,0); //empty the lua stack
    if(luaL_dofile(L, "./luascript.lua")) {
        fprintf(stderr, "error: %s\n", lua_tostring(L,-1));
        lua_pop(L,1);
        exit(1);
    }
    assert(lua_gettop(L) == 0); //empty the lua stack
}

void DWApplication::registerListType() {
    std::cout << "Set the list object in lua" << std::endl;
    luaL_newmetatable(L, "ListMT");
    lua_pushvalue(L,-1);
    lua_setfield(L,-2, "__index"); // ListMT .__index = ListMT
    lua_pushcfunction(L, l_list_push);
    lua_setfield(L,-2, "push"); // push in lua will call l_list_push in C++
    lua_pushcfunction(L, l_list_pop);
    lua_setfield(L,-2, "pop"); // pop in lua will call l_list_pop in C++
}

void DWApplication::run() {
    for(unsigned int i = 0; i<10; i++) // add some input data to the list
        theList.push_back(i*100);
    registerListType();
    std::cout << "creating an instance of std::list in lua" << std::endl;
    std::list<int> **ud = static_cast<std::list<int> **>(lua_newuserdata(L, sizeof(std::list<int> *)));
    *(ud) = &theList;
    luaL_setmetatable(L, "ListMT"); // set userdata metatable
    lua_setglobal(L, "the_list"); // the_list in lua points to the new userdata
    
    runScript();
    
    while(!theList.empty()) { // read the data that lua left in the list
        std::cout << "from C++: pop value " << theList.front() << std::endl;
        theList.pop_front();
    }
}
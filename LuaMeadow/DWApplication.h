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
    void runScript();
};


#endif /* defined(__LuaMeadow__DWApplication__) */

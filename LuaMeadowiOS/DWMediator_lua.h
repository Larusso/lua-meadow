//
//  DWMediator_lua.h
//  LuaMeadow
//
//  Created by Larusso on 30.08.13.
//  Copyright (c) 2013 Larusso. All rights reserved.
//

#ifndef LuaMeadow_DWMediator_lua_h
#define LuaMeadow_DWMediator_lua_h

#ifdef SWIG
%ignore Mediator();
%native(Mediator) int Mediator_new(lua_State*L);
%{
int Mediator_new(lua_State*L)
{
    void *m = Mediator();
    
    SWIG_NewPointerObj(L,m,NULL,1);
    return 1;
}
%}
#endif


void * Mediator();

#endif

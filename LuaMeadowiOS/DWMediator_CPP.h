//
//  DWMediator_CPP.h
//  LuaMeadow
//
//  Created by Larusso on 28.08.13.
//  Copyright (c) 2013 Larusso. All rights reserved.
//

#ifndef LuaMeadow_DWMediator_CPP_h
#define LuaMeadow_DWMediator_CPP_h

#include <iostream>

#ifdef SWIG
%{
#include <iostream>
#include "DWMediator_CPP.h"
%}

%rename(Mediator) DWMediatorImpl;
%ignore doSomething();
%ignore init(void);
#endif

class DWMediatorImpl
{
    int x,y;
public:
    DWMediatorImpl(void);
    ~DWMediatorImpl(void);
    void release();
    void printType();
    void move(int x, int y);
    void doSomething();
    
private:
    void *instance;
};


#endif

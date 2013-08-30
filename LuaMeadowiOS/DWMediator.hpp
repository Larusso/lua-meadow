//
//  DWMediator_CPP.h
//  LuaMeadow
//
//  Created by Larusso on 28.08.13.
//  Copyright (c) 2013 Larusso. All rights reserved.
//

#ifndef LuaMeadow_DWMediator_hpp
#define LuaMeadow_DWMediator_hpp

#include <iostream>

#ifdef SWIG
%{
#include <iostream>
#include "DWMediator.hpp"
%}

%rename(Mediator) DWMediatorImpl;
%ignore doSomething();
%ignore init(void);
#endif

OBJC_CLASS(DWMediator);

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
    DWMediator *wrapped;
};

#endif

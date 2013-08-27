//
//  DWMediator.h
//  LuaMeadow
//
//  Created by Larusso on 25.08.13.
//  Copyright (c) 2013 Larusso. All rights reserved.
//

#ifndef __LuaMeadow__DWMediator__
#define __LuaMeadow__DWMediator__

#include <iostream>

#ifdef SWIG
%{
#include "DWMediator.h"
%}

%rename(Mediator) DWMediator;
%ignore doSomething();
#endif

class DWMediator
{
    int x,y;
public:
    DWMediator();
    ~DWMediator();
    void release();
    void printType();
    void move(int x, int y);
    void doSomething();
};

#endif /* defined(__LuaMeadow__DWMediator__) */

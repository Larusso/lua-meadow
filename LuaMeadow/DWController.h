//
// Created by Larusso on 26.08.13.
// Copyright (c) 2013 Larusso. All rights reserved.
//
// To change the template use AppCode | Preferences | File Templates.
//



#ifndef __DWController_H_
#define __DWController_H_

#include <iostream>
#include "DWMediator.h"

class DWController
{
public:
    DWController();
    ~DWController();
    void release();
    void registerView(DWMediator *mediator);
};


#endif //__DWController_H_

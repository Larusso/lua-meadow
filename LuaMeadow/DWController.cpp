//
// Created by Larusso on 26.08.13.
// Copyright (c) 2013 Larusso. All rights reserved.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include "DWController.h"

DWController::DWController()
{
    std::cout << "++ ------- new DWController" << std::endl;
}

DWController::~DWController()
{
    std::cout << "++ ------- destroy ~DWController" << std::endl;
}

void DWController::release()
{
    
}

void DWController::registerView(DWMediator *mediator)
{
    printf("++ ------- registerView called mediator:%p\n", mediator);
    mediator->move(400, 20);
}
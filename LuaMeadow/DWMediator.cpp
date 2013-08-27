//
//  DWMediator.cpp
//  LuaMeadow
//
//  Created by Larusso on 25.08.13.
//  Copyright (c) 2013 Larusso. All rights reserved.
//

#include "DWMediator.h"

DWMediator::DWMediator()
{
    this->x = 100;
    this->y = 100;
    std::cout << "++ ------- new DWMediator" << std::endl;
}

DWMediator::~DWMediator()
{
    std::cout << "++ ------- destroy DWMediator" << std::endl;
}

void DWMediator::release()
{

}

void DWMediator::printType()
{
    std::cout << "++ ------- printType called" << std::endl;
}

void DWMediator::move(int x, int y)
{
    this->x = x;
    this->y = y;
    printf("++ ------- move called x:%d, y:%d\n", x,y);
}

Point DWMediator::getPos()
{
    return Point{this->x,this->y};
}

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

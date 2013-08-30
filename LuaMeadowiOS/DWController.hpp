//
//  DWController.hpp
//  LuaMeadow
//
//  Created by Larusso on 30.08.13.
//  Copyright (c) 2013 Larusso. All rights reserved.
//

#ifndef LuaMeadow_DWController_hpp
#define LuaMeadow_DWController_hpp

#include <iostream>

#ifdef SWIG
%{
#import <iostream>
#import "DWController.hpp"
#import "DWMediator.hpp"
%}

%rename(Controller) DWControllerImpl;
%ignore wrapped;
#endif

#import "DWMediator.hpp"

OBJC_CLASS(DWController);

class DWControllerImpl
{
public:
    DWControllerImpl();
    ~DWControllerImpl();
    void release();
    void registerView(DWMediatorImpl *mediator);
private:
    DWController *wrapped;
};


#endif

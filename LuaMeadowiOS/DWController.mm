//
//  DWController.m
//  LuaMeadow
//
//  Created by Larusso on 30.08.13.
//  Copyright (c) 2013 Larusso. All rights reserved.
//

#import "DWController.h"
#import "DWController.hpp"
#import "DWMediator.h"

DWControllerImpl::DWControllerImpl():
    wrapped([[DWController alloc]initFromExtern])
{
    std::cout << "++ ------- new DWControllerImpl" << std::endl;
}

DWControllerImpl::~DWControllerImpl()
{
    std::cout << "++ ------- destroy ~DWControllerImpl" << std::endl;
}

void DWControllerImpl::release()
{
    [wrapped release_me];
}

void DWControllerImpl::registerView(DWMediatorImpl *mediator)
{
    printf("++ ------- registerView called mediator:%p\n", mediator);
    [wrapped registerMediator: mediator->wrapped];
}

@implementation DWController

- (id) init
{
    self = [super init];
    if (self)
    {
        
    }
    return self;
}

- (id) initFromExtern
{
    self = [super init];
    return self;
}


- (void) release_me
{
    NSLog(@"----OBJ-C-> release called");
}

- (void) registerMediator:(DWMediator *)mediator
{
    NSLog(@"----OBJ-C-> registerMediator called");
    [mediator move: 40 andY:20];
}
@end

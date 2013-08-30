//
//  DWMediator.m
//  LuaMeadow
//
//  Created by Larusso on 28.08.13.
//  Copyright (c) 2013 Larusso. All rights reserved.
//

#import "DWMediator.h"
#import "DWMediator.hpp"

DWMediatorImpl::DWMediatorImpl(void):
    wrapped([[DWMediator alloc] init])
{
    this->x = 100;
    this->y = 100;
    std::cout << "++ ------- new DWMediator" << std::endl;
}

DWMediatorImpl::~DWMediatorImpl(void)
{
    std::cout << "++ ------- destroy ~DWMediator" << std::endl;
    this->release();
    //CFRelease(instance);
}

void DWMediatorImpl::release()
{
    [wrapped release_me];
}

void DWMediatorImpl::printType()
{
    std::cout << "++ ------- printType called" << std::endl;
    [wrapped printType];
}

void DWMediatorImpl::move(int x, int y)
{
    this->x = x;
    this->y = y;
    printf("++ ------- move called x:%d, y:%d\n", x,y);
     [wrapped move:x andY:y];
}

void DWMediatorImpl::doSomething()
{
    
}

@implementation DWMediator

- (void) release_me
{
    NSLog(@"----OBJ-C-> release called");
}

- (void) printType
{
    NSLog(@"----OBJ-C-> printType called");
}

- (void) move:(int) x andY:(int) y
{
    NSLog(@"----OBJ-C-> move %d,%d called",x,y);
}

- (void) doSomething
{
    NSLog(@"----OBJ-C-> doSomething called");
}
@end

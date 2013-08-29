//
//  DWMediator.m
//  LuaMeadow
//
//  Created by Larusso on 28.08.13.
//  Copyright (c) 2013 Larusso. All rights reserved.
//

#import "DWMediator.h"

DWMediatorImpl::DWMediatorImpl(void)
{
    this->x = 100;
    this->y = 100;
    instance = (__bridge void *)[[DWMediator alloc]init];
    std::cout << "++ ------- new DWMediator" << std::endl;
}

DWMediatorImpl::~DWMediatorImpl(void)
{
    std::cout << "++ ------- destroy ~DWMediator" << std::endl;
    //[(__bridge id)self dealloc];
}

void DWMediatorImpl::release()
{
    [(__bridge id)instance release_me];
}

void DWMediatorImpl::printType()
{
    std::cout << "++ ------- printType called" << std::endl;
    [(__bridge id)instance printType];
}

void DWMediatorImpl::move(int x, int y)
{
    this->x = x;
    this->y = y;
    printf("++ ------- move called x:%d, y:%d\n", x,y);
     [(__bridge id)instance move:x andY:y];
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

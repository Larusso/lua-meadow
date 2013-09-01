//
//  DWMediator.m
//  LuaMeadow
//
//  Created by Larusso on 28.08.13.
//  Copyright (c) 2013 Larusso. All rights reserved.
//

#import "DWMediator.h"

@implementation DWMediator

void * Mediator()
{
    return (__bridge void *)([[DWMediator alloc]init]);
}

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

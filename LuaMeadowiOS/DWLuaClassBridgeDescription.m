//
//  LuaClassBridgeDescription.m
//  LuaMeadow
//
//  Created by Larusso on 02.09.13.
//  Copyright (c) 2013 Larusso. All rights reserved.
//

#import "DWLuaClassBridgeDescription.h"

@implementation DWLuaClassBridgeDescription

+(DWLuaClassBridgeDescription*)descriptionWith:(NSString*)className andClass:(Class)class andSelectors:(NSSet*)selectors
{
    DWLuaClassBridgeDescription *descriptor = [[DWLuaClassBridgeDescription alloc]init];
    
    [descriptor setClass:class];
    [descriptor setClassName:className];
    [descriptor setSelectors:selectors];
    
    return descriptor;
}

@end

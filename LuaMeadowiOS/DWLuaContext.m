//
//  DWLuaContext.m
//  LuaMeadow
//
//  Created by Larusso on 01.09.13.
//  Copyright (c) 2013 Larusso. All rights reserved.
//

#import "DWLuaContext.h"
#import "objc/runtime.h"

@interface DWLuaContext ()
- (NSString*)getClassNameForClass:(Class)class;
- (NSSet *)getClassSelectors:(Class)class;
@end
@implementation DWLuaContext

- (void)doFile:(NSString *)path
{
    
}

- (void)registerClass:(Class)class
{
    [self registerClass:class as:nil andIncludeSelectors:nil];
}

- (void)registerClass:(Class)class as:(NSString*)luaClassName
{
    [self registerClass:class as:luaClassName andIncludeSelectors:nil];
}

- (void)registerClass:(Class)class andIncludeSelectors:(NSSet *)includedSelectors
{
    [self registerClass:class as:nil andIncludeSelectors:includedSelectors];
}

- (void)registerClass:(Class)class as:(NSString*)luaClassName andIncludeSelectors:(NSSet *)includedSelectors
{
    NSString *className = luaClassName;
    
    if(className == nil)
    {
        className = [self getClassNameForClass:class];
    }
    
    NSSet *selectors = includedSelectors;
    if(selectors == nil)
    {
        selectors = [self getClassSelectors:class];
    }
}

#pragma runtime helper functions

- (NSString*)getClassNameForClass:(Class)class
{
    const char * rawClassName = class_getName(class);
    return[NSString stringWithCString:rawClassName encoding:[NSString defaultCStringEncoding]];
}

- (NSSet *)getClassSelectors:(Class)class
{
    uint outCount;
    Method* classMethods = class_copyMethodList(class, &outCount);
    
    NSMutableSet *methodSelectors;
    Class superClass = class_getSuperclass(class);
    
    if([[self getClassNameForClass:superClass] isEqual: @"NSObject"])
    {
        superClass = nil;
    }
    
    if(superClass != nil)
    {
        NSSet *superClassSelectors = [self getClassSelectors:superClass];
        methodSelectors = [NSMutableSet setWithSet:superClassSelectors];
    }
    else
    {
        methodSelectors = [[NSMutableSet alloc]initWithCapacity:outCount];
    }
    
    for(int i = 0; i < outCount; i++)
    {
        SEL classMethodSelector = method_getName(classMethods[i]);
        NSString *selectorName = NSStringFromSelector(classMethodSelector);
        [methodSelectors addObject:selectorName];
    }
    
    free(classMethods);
    return methodSelectors;
}

@end

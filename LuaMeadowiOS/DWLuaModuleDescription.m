//
//  DWLuaModuleDescription.m
//  LuaMeadow
//
//  Created by Larusso on 01.09.13.
//  Copyright (c) 2013 Larusso. All rights reserved.
//

#import "DWLuaModuleDescription.h"
#import "DWLuaClassBridgeDescription.h"

#import "objc/runtime.h"
@interface DWLuaModuleDescription ()
- (NSString*)getClassNameForClass:(Class)class;
- (NSSet *)getClassSelectors:(Class)class;
@end

@implementation DWLuaModuleDescription
@synthesize registeredClassNames=_registeredClassNames;

- (id)initWithName:(NSString*)moduleName
{
    self = [super init];
    if(self)
    {
        [self setName:moduleName];
        _registeredClassNames = [[NSMutableDictionary alloc]init];
    }
    return self;
}

#pragma mark runtime helper functions

- (NSString*)getClassNameForClass:(Class)class
{
    return to_objcString(class_getName(class));
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

#pragma mark FACTORY

@implementation DWLuaModuleDescription (factory)

+(id)descriptorWithName:(NSString *)moduleName
{
    return [[DWLuaModuleDescription alloc]initWithName:moduleName];
}

@end

#pragma mark CLASS REGISTRY

@implementation DWLuaModuleDescription (class_registry)

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
    
    DWLuaClassBridgeDescription *description = [DWLuaClassBridgeDescription descriptionWith:className andClass:class andSelectors:selectors];
    [_registeredClassNames setObject:description forKey:[NSString stringWithFormat:@"%@.%@",[self name],className]];
}

@end

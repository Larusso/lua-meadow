//
//  DWLuaModuleDescription.h
//  LuaMeadow
//
//  Created by Larusso on 01.09.13.
//  Copyright (c) 2013 Larusso. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DWLuaModuleDescription : NSObject
{
    NSMutableDictionary *_registeredClassNames;
}

@property (nonatomic,strong) NSString *name;
@property (nonatomic,strong,readonly) NSDictionary *registeredClassNames;

- (id)initWithName:(NSString*)moduleName;
@end

@interface DWLuaModuleDescription (factory)
+ (id)descriptorWithName:(NSString*)moduleName;
@end

@interface DWLuaModuleDescription (class_registry)
- (void)registerClass:(Class)class;
- (void)registerClass:(Class)class as:(NSString*)luaClassName;
- (void)registerClass:(Class)class andIncludeSelectors:(NSSet *)includedSelectors;
- (void)registerClass:(Class)class as:(NSString*)luaClassName andIncludeSelectors:(NSSet *)includedSelectors;
@end

//
//  LuaClassBridgeDescription.h
//  LuaMeadow
//
//  Created by Larusso on 02.09.13.
//  Copyright (c) 2013 Larusso. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DWLuaClassBridgeDescription : NSObject

@property (strong) NSString *className;
@property Class class;
@property (strong) NSSet* selectors;

+(DWLuaClassBridgeDescription*)descriptionWith:(NSString*)className andClass:(Class)class andSelectors:(NSSet*)selectors;

@end

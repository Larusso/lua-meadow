//
//  DWLuaContext.h
//  LuaMeadow
//
//  Created by Larusso on 01.09.13.
//  Copyright (c) 2013 Larusso. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

@interface DWLuaContext : NSObject
- (void)doFile:(NSString *)path;
- (void)registerClass:(Class)class;
- (void)registerClass:(Class)class as:(NSString*)luaClassName;
- (void)registerClass:(Class)class andIncludeSelectors:(NSSet *)includedSelectors;
- (void)registerClass:(Class)class as:(NSString*)luaClassName andIncludeSelectors:(NSSet *)includedSelectors;
@end

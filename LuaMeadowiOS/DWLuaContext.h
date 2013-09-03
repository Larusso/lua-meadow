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
@class DWLuaModuleDescription;
@interface DWLuaContext : NSObject
{
    lua_State *state;
    NSMutableDictionary *_modules;
}

@property(nonatomic,strong,readonly)NSDictionary *modules;

- (void)doFile:(NSString *)path;
- (void)registerModule:(DWLuaModuleDescription *)module;

@end

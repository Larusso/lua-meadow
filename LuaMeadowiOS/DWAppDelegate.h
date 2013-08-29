//
//  DWAppDelegate.h
//  LuaMeadowiOS
//
//  Created by Larusso on 28.08.13.
//  Copyright (c) 2013 Larusso. All rights reserved.
//

#import <UIKit/UIKit.h>
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

extern int luaopen_direwolf(lua_State* L);

@interface DWAppDelegate : UIResponder <UIApplicationDelegate>
{

}
@property (nonatomic) lua_State *state;
@property (strong, nonatomic) UIWindow *window;

@end

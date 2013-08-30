//
//  DWViewController.h
//  LuaMeadow
//
//  Created by Larusso on 30.08.13.
//  Copyright (c) 2013 Larusso. All rights reserved.
//

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

@interface DWViewController : UIViewController
{
    NSString *luaFilePath;
}
- (void)run;
- (IBAction)runLuaDown:(id)sender;
@property (nonatomic) lua_State *state;
@end

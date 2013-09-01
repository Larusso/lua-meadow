//
//  DWViewController.h
//  LuaMeadow
//
//  Created by Larusso on 30.08.13.
//  Copyright (c) 2013 Larusso. All rights reserved.
//

@class DWLuaContext;

@interface DWViewController : UIViewController
{
    NSString *luaFilePath;
}
- (void)run;
- (IBAction)runLuaDown:(id)sender;
@property (nonatomic, strong) DWLuaContext *luaContext;
@end

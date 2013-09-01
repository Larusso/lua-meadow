//
//  DWViewController.m
//  LuaMeadow
//
//  Created by Larusso on 30.08.13.
//  Copyright (c) 2013 Larusso. All rights reserved.
//

#import "DWViewController.h"
#import "DWMediator.h"
#import "DWLuaContext.h"

const char* to_cString(NSString* s){
    return [s cStringUsingEncoding:[NSString defaultCStringEncoding]];
}

@implementation DWViewController

- (IBAction)runLuaDown:(id)sender {
    [self run];
}

- (void)run
{
    [[self luaContext] doFile:luaFilePath];
    
    /*lua_State *L = self.state;

    if (luaL_dofile(L, to_cString(luaFilePath)))
    {
        fprintf(stderr, "error: %s\n", lua_tostring(L, -1));
        lua_pop(L, 1);
        //exit(1);
    }*/
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    
    [self setLuaContext: [[DWLuaContext alloc]init]];
    [[self luaContext] registerClass:[DWMediator class] as:@"Mediator"];
    [[self luaContext] registerClass:[DWMediator class]];
    
    NSString *luaPath = [[[NSBundle mainBundle] resourcePath] stringByAppendingString:@"/lua"];
    NSString *mainLua = [luaPath stringByAppendingString:@"/luascript.lua"];
    luaFilePath = mainLua;
    chdir(to_cString(luaPath));
    
    /*
    NSLog(@"%@",mainLua);
    lua_State *L = self.state;
    luaL_openlibs(L);
    luaopen_base(L);
    luaopen_direwolf(L);
    */
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}
@end

//
//  DWAppDelegate.h
//  LuaMeadowiOS
//
//  Created by Larusso on 28.08.13.
//  Copyright (c) 2013 Larusso. All rights reserved.
//

#import <UIKit/UIKit.h>

@class DWViewController;

@interface DWAppDelegate : UIResponder <UIApplicationDelegate>
{

}
@property (strong, nonatomic) UIWindow *window;
@property (strong, nonatomic) DWViewController *viewController;

@end

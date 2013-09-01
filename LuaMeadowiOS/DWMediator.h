//
//  DWMediator.h
//  LuaMeadow
//
//  Created by Larusso on 28.08.13.
//  Copyright (c) 2013 Larusso. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DWLuaBridgeDescription.h"

@interface DWMediator : NSObject<DWLuaBridgeDescription>

- (void) release_me;
- (void) printType;
- (void) move:(int) x andY:(int) y;
- (void) doSomething;

@end

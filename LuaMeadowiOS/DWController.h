//
//  DWController.h
//  LuaMeadow
//
//  Created by Larusso on 30.08.13.
//  Copyright (c) 2013 Larusso. All rights reserved.
//

#import <Foundation/Foundation.h>
@class DWMediator;

@interface DWController : NSObject
{
    
}
- (id) initFromExtern;
- (void) release_me;
- (void) registerMediator:(DWMediator *)mediator;
@end

//
//  DWLuaBridgeDescription.h
//  LuaMeadow
//
//  Created by Larusso on 01.09.13.
//  Copyright (c) 2013 Larusso. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol DWLuaBridgeDescription <NSObject>
@optional
+ (NSSet*) getIncludedSelectorNames;
@end

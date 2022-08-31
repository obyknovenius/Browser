//
//  View.h
//  Browser
//
//  Created by Vitaly Dyachkov on 21.12.21.
//

#import "CSS/Display/TextRun.h"
#import <Cocoa/Cocoa.h>

NS_ASSUME_NONNULL_BEGIN

@interface View : NSView

@property CSS::BoxTree::Node *boxTree;

@end

NS_ASSUME_NONNULL_END

//
//  AppDelegate.m
//  Browser
//
//  Created by Vitaly Dyachkov on 21.12.21.
//

#import "AppDelegate.h"

#include "Tokenizer.h"
#include "TreeConstruction.h"

@interface AppDelegate ()


@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    // Insert code here to initialize your application
    
    std::ifstream input_stream { "/Users/obyknovenius/Developer/Personal/Browser/test.html" };
    HTML::Tokenizer tokenizer { input_stream };
    HTML::TreeConstruction tree_construction {};
    
    HTML::Token* next_token {};
    do {
        tokenizer >> &next_token;
    } while (!tree_construction.dispatch(next_token));
}


- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}


- (BOOL)applicationSupportsSecureRestorableState:(NSApplication *)app {
    return YES;
}


@end

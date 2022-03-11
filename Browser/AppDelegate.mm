//
//  AppDelegate.m
//  Browser
//
//  Created by Vitaly Dyachkov on 21.12.21.
//

#import "AppDelegate.h"

#include "DOM/Document.h"
#include "Tokenizer.h"
#include "TreeConstruction.h"

@interface AppDelegate ()


@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    // Insert code here to initialize your application
    
    DOM::Document document = DOM::Document {};
    
    std::ifstream input_stream { "/Users/obyknovenius/Developer/Personal/Browser/test.html" };
    HTML::Tokenizer tokenizer { input_stream };
    HTML::TreeConstruction tree_construction { document };
    
    for (;;)
    {
        HTML::Token next_token {};
        
        tokenizer >> next_token;
        
        std::cout << next_token;
        
        if (next_token.is_end_of_file()) {
            break;
        }
        tree_construction.dispatch(next_token);
    }
    
    std::cout << "\n";
    DOM::print_tree(&document);
}


- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}


- (BOOL)applicationSupportsSecureRestorableState:(NSApplication *)app {
    return YES;
}


@end

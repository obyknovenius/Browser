//
//  AppDelegate.m
//  Browser
//
//  Created by Vitaly Dyachkov on 21.12.21.
//

#import "AppDelegate.h"

#include "HTML/Parser.h"
#include "DOM/Document.h"
#include "CSS/Tokenizer.h"
#include <iostream>

@interface AppDelegate ()


@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    // Insert code here to initialize your application
        
    std::ifstream input_stream { "/Users/obyknovenius/Developer/Personal/Browser/test.html" };
    HTML::Parser parser { input_stream };
    DOM::Document* document { parser.parse() };

    DOM::print_tree(document);
    
    std::ifstream input { "/Users/obyknovenius/Developer/Personal/Browser/test.css" };
    CSS::Tokenizer tokenizer { input };
    
    CSS::Token token {};
    do
    {
        token = tokenizer.consume_token();
        std::cout << token;
    }
    while (!token.is_eof());
}


- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}


- (BOOL)applicationSupportsSecureRestorableState:(NSApplication *)app {
    return YES;
}


@end

//
//  AppDelegate.m
//  Browser
//
//  Created by Vitaly Dyachkov on 21.12.21.
//

#import "AppDelegate.h"

#include "HTML/Parser.h"
#include "DOM/Document.h"
#include "CSS/Parser.h"
#include "CSS/Tokenizer.h"
#include "CSS/StyleSheet.h"
#include <iostream>

@interface AppDelegate ()


@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    // Insert code here to initialize your application
        
    std::ifstream input_stream { "/Users/obyknovenius/Developer/Personal/Browser/test.html" };
    HTML::Parser html_parser { input_stream };
    DOM::Document* document { html_parser.parse() };

    DOM::print_tree(document);
    
    std::ifstream input { "/Users/obyknovenius/Developer/Personal/Browser/test.css" };
    CSS::Tokenizer css_tokenizer { input };
    css_tokenizer.tokenize();
    
    CSS::Parser css_parser { css_tokenizer.tokens() };
    CSS::StyleSheet stylesheet = css_parser.parse_stylesheet();
    
    std::cout << std::endl << stylesheet;
}


- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}


- (BOOL)applicationSupportsSecureRestorableState:(NSApplication *)app {
    return YES;
}


@end

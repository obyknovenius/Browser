//
//  AppDelegate.m
//  Browser
//
//  Created by Vitaly Dyachkov on 21.12.21.
//

#import "AppDelegate.h"

#include "HTML/Parser.h"
#include "DOM/Document.h"
#include "DOM/Tree.h"
#include "CSS/Parser.h"
#include "CSS/Tokenizer.h"
#include "CSS/StyleSheet.h"
#include "CSS/TokenStream.h"
#include "CSS/ComponentValue.h"
#include "CSS/Display/BoxTree.h"
#include "CSS/Display/BoxTreeConstructor.h"
#include <iostream>

@interface AppDelegate ()

@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    // Insert code here to initialize your application
    
    NSBundle *bundle = [NSBundle bundleForClass:[self class]];
    
    const char *testHtml = [[bundle pathForResource:@"test" ofType:@"html"] cStringUsingEncoding:NSUTF8StringEncoding];
    std::ifstream input_stream { testHtml };
    HTML::Parser html_parser { input_stream };
    DOM::Document* document { html_parser.parse() };
    DOM::dump_tree(document);
    
    const char *testCss = [[bundle pathForResource:@"test" ofType:@"css"] cStringUsingEncoding:NSUTF8StringEncoding];
    std::ifstream input { testCss };
    CSS::Tokenizer css_tokenizer { input };
    CSS::TokenStream<CSS::Token> tokens = css_tokenizer.tokenize();
    CSS::CSSStyleSheet* stylesheet { CSS::parse_css_stylesheet(tokens) };
    
    CSS::BoxTreeConstructor box_tree_constructor {};
    CSS::BoxTree::Node* box_tree { box_tree_constructor.construct_tree(document) };
}

- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}

- (BOOL)applicationSupportsSecureRestorableState:(NSApplication *)app {
    return YES;
}


@end

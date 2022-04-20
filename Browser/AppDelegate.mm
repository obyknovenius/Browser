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
#include "CSS/TokenStream.h"
#include "CSS/ComponentValue.h"
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
    DOM::print_tree(document);
    
    const char *testCss = [[bundle pathForResource:@"test" ofType:@"css"] cStringUsingEncoding:NSUTF8StringEncoding];
    std::ifstream input { testCss };
    CSS::Parser::Tokenizer css_tokenizer { input };
    CSS::Parser::TokenStream<CSS::Parser::Token> tokens = css_tokenizer.tokenize();
    const CSS::Parser::StyleSheet* stylesheet { CSS::Parser::parse_stylesheet(tokens) };
    std::cout << std::endl << *stylesheet;
    
    const CSS::Parser::QualifiedRule *rule = stylesheet->value().front();
    CSS::Parser::TokenStream<CSS::Parser::ComponentValue> selector_tokens { rule->prelude() };
    CSS::SimpleSelector selector = CSS::Parser::parse_simple_selector(selector_tokens);
}


- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}


- (BOOL)applicationSupportsSecureRestorableState:(NSApplication *)app {
    return YES;
}


@end

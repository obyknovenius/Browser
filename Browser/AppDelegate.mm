//
//  AppDelegate.m
//  Browser
//
//  Created by Vitaly Dyachkov on 21.12.21.
//

#import "AppDelegate.h"

#include "Tokenizer.h"

@interface AppDelegate ()


@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    // Insert code here to initialize your application
    
    std::ifstream input_stream { "/Users/obyknovenius/Developer/Personal/Browser/test.html" };
    HTML::Tokenizer tokenizer { input_stream };
    
    auto done { false };
    while (!done)
    {
        auto* token = tokenizer.next_token();
                        
        if (auto* doctype = token->as<HTML::DOCTYPE*>())
        {
            std::cout << *doctype;
        }
        
        if (auto* start_tag = token->as<HTML::StartTag*>())
        {
            std::cout << *start_tag;
        }
        
        if (auto* end_tag = token->as<HTML::EndTag*>())
        {
            std::cout << *end_tag;
        }
        
        if (auto* comment = token->as<HTML::Comment*>())
        {
            std::cout << *comment;
        }
        
        if (auto* character = token->as<HTML::Character*>())
        {
            std::cout << *character;
        }
        
        if (auto* end_of_file = token->as<HTML::EndOfFile*>())
        {
            std::cout << *end_of_file;
            done = true;
        }
        
        delete token;
    }
}


- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}


- (BOOL)applicationSupportsSecureRestorableState:(NSApplication *)app {
    return YES;
}


@end

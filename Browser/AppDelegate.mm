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
        auto token = tokenizer.next_token();
        
        if (auto doctype = dynamic_cast<HTML::DOCTYPE*>(token))
        {
            std::cout << *doctype;
        }
        
        if (auto start_tag = dynamic_cast<HTML::StartTag*>(token))
        {
            std::cout << *start_tag;
        }
        
        if (auto end_tag = dynamic_cast<HTML::EndTag*>(token))
        {
            std::cout << *end_tag;
        }
        
        if (auto comment = dynamic_cast<HTML::Comment*>(token))
        {
            std::cout << *comment;
        }
        
        if (auto character = dynamic_cast<HTML::Character*>(token))
        {
            std::cout << *character;
        }
        
        if (auto end_of_file = dynamic_cast<HTML::EndOfFile*>(token))
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

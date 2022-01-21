//
//  AppDelegate.m
//  Browser
//
//  Created by Vitaly Dyachkov on 21.12.21.
//

#import "AppDelegate.h"

#include "Tokenizer.h"

#include <iostream>

@interface AppDelegate ()


@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    // Insert code here to initialize your application
        
    HTML::Tokenizer tokenizer;
    
    auto done { false };
    while (!done)
    {
        auto token = tokenizer.next_token();
        
        if (auto doctype = dynamic_cast<HTML::DOCTYPE*>(token))
        {
            std::cout << "DOCTYPE";
        }
        
        if (auto start_tag = dynamic_cast<HTML::StartTag*>(token))
        {
            std::cout << "<" << start_tag->tag_name();
            for (const auto& attribute : start_tag->attributes())
            {
                std::cout << " " << attribute.name << "=" << attribute.value;
            }
            std::cout << ">";
        }
        
        if (auto end_tag = dynamic_cast<HTML::EndTag*>(token))
        {
            std::cout << "</" << end_tag->tag_name() << ">";
        }
        
        if (auto comment = dynamic_cast<HTML::Comment*>(token))
        {
            std::cout << "//" << comment->data;
        }
        
        if (auto character = dynamic_cast<HTML::Character*>(token))
        {
            std::cout << character->data();
        }
        
        if (auto end_of_file = dynamic_cast<HTML::EndOfFile*>(token))
        {
            std::cout << "end-of-file";
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

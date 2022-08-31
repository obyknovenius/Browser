//
//  ViewController.m
//  Browser
//
//  Created by Vitaly Dyachkov on 21.12.21.
//

#import "ViewController.h"
#import "View.h"
#import "CSS/Display/BoxTree.h"
#import "CSS/Display/BoxTreeConstructor.h"
#import "CSS/Display/TextRun.h"
#import "DOM/Document.h"
#import "DOM/Tree.h"
#import "HTML/Parser.h"
#import <iostream>

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    NSBundle *bundle = [NSBundle bundleForClass:[self class]];
    
    const char *testHtml = [[bundle pathForResource:@"test" ofType:@"html"] cStringUsingEncoding:NSUTF8StringEncoding];
    std::ifstream input_stream { testHtml };
    HTML::Parser html_parser { input_stream };
    DOM::Document* document { html_parser.parse() };
    DOM::dump_tree(document);
    
    CSS::BoxTreeConstructor box_tree_constructor {};
    CSS::BoxTree::Node* box_tree { box_tree_constructor.construct_tree(document) };

    View* view = (View *)self.view;
    view.boxTree = box_tree;
}


- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];

    // Update the view, if already loaded.
}


@end

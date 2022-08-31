//
//  ViewController.m
//  Browser
//
//  Created by Vitaly Dyachkov on 21.12.21.
//

#import "ViewController.h"
#import "View.h"
#import "CSS/Display/TextRun.h"

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    View* view = (View *)self.view;
    view.textRun = new CSS::TextRun("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nullam ac feugiat erat. Donec venenatis mattis rutrum. Curabitur id nisi vehicula lacus volutpat fringilla vitae eu est. Sed id ultricies ligula, non mattis nisi. Vestibulum blandit nisl id sem egestas eleifend. In porttitor maximus aliquam. Sed id aliquam dui. Aliquam a pretium elit. Phasellus pretium nisl vel mi efficitur ultrices.");
}


- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];

    // Update the view, if already loaded.
}


@end

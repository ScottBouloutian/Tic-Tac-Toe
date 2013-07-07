//
//  TTTViewController.h
//  Tic Tac Toe
//

//  Copyright (c) 2013 Scott Bouloutian. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <SpriteKit/SpriteKit.h>
#import "TTTMyScene.h"

@interface TTTViewController : UIViewController{
    TTTMyScene *scene;
}
- (IBAction)restartTouched;
- (IBAction)turnToggled;
@end

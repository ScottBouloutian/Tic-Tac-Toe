//
//  TTTMyScene.h
//  Tic Tac Toe
//

//  Copyright (c) 2013 Scott Bouloutian. All rights reserved.
//

#import <SpriteKit/SpriteKit.h>
#import "TTTEngine.h"

@interface TTTMyScene : SKScene{
    NSArray *pieces;
    float pieceSize;
    SKSpriteNode *board;
    TTTEngine engine;
}
@property bool userGoesFirst;
-(void)computerMove;
-(void)restartGame;
@end

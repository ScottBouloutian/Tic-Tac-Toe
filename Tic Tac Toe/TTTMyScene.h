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
    bool isUsersTurn;
    float pieceSize;
    SKSpriteNode *board;
    TTTEngine engine;
}

@end

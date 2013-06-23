//
//  TTTMyScene.m
//  Tic Tac Toe
//
//  Created by Scott Bouloutian on 6/21/13.
//  Copyright (c) 2013 Scott Bouloutian. All rights reserved.
//

#import "TTTMyScene.h"

@implementation TTTMyScene

-(id)initWithSize:(CGSize)size {    
    if (self = [super initWithSize:size]) {
        /* Setup your scene here */
        
        self.backgroundColor = [SKColor whiteColor];
        
        SKLabelNode *myLabel = [[SKLabelNode alloc]init];
        
        myLabel.text = @"Tic Tac Toe";
        myLabel.fontColor=[SKColor blackColor];
        myLabel.fontSize = 30;
        myLabel.position = CGPointMake(CGRectGetMidX(self.frame),self.frame.size.height-60);
        [self addChild:myLabel];
        
        //Draw the tic tac toe board
        board=[[SKSpriteNode alloc]initWithImageNamed:@"board"];
        board.position=CGPointMake(CGRectGetMidX(self.frame),CGRectGetMidY(self.frame));
        [self addChild:board];
        
        //Calculate the piece positions on the board
        NSMutableArray *temp=[[NSMutableArray alloc]initWithCapacity:9];
        pieceSize=board.frame.size.width/3;
        for(int x=0;x<3;x++){
            for(int y=0;y<3;y++){
                SKLabelNode *piece=[[SKLabelNode alloc]init];
                piece.fontColor=[SKColor blackColor];
                piece.fontSize=pieceSize;
                piece.text=@"X";
                piece.position=CGPointMake((x-1)*pieceSize, (y-1.5)*pieceSize+9);
                piece.name=[NSString stringWithFormat:@"%i",x+3*(2-y)];
                piece.hidden=YES;
                [board addChild:piece];
                [temp addObject:piece];
            }
        }
        pieces=[[NSArray alloc]initWithArray:temp];
    }
    return self;
}

-(void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
    /* Called when a touch begins */
    if(touches.count==1){
        UITouch *touch=touches.anyObject;
        for(SKLabelNode *piece in pieces){
            if([piece containsPoint:[touch locationInNode:board]] && engine.canPlaceToken(piece.name.intValue)){
                engine.placeToken(piece.name.intValue);
                piece.hidden=NO;
                [self computerMove];
            }
        }
    }
}

-(void)computerMove{
    int move=engine.getComputerMove();
    SKLabelNode *piece=(SKLabelNode*)[board childNodeWithName:[NSString stringWithFormat:@"%i",move]];
    engine.placeToken(move);
    piece.text=@"O";
    piece.hidden=NO;
}

-(void)update:(CFTimeInterval)currentTime {
    /* Called before each frame is rendered */
}

@end

//
//  TTTMyScene.m
//  Tic Tac Toe
//
//  Created by Scott Bouloutian on 6/21/13.
//  Copyright (c) 2013 Scott Bouloutian. All rights reserved.
//

#import "TTTMyScene.h"

@interface TTTMyScene()
-(void)updateStatusLabel;
-(id)randomElement:(NSArray*)array;
@end

@implementation TTTMyScene{
    SKLabelNode *statusLabel;
    NSArray *tieStatuses;
    NSArray *winStatuses;
}
@synthesize userGoesFirst;

-(id)initWithSize:(CGSize)size {    
    if (self = [super initWithSize:size]) {
        /* Setup your scene here */
        
        //Initialize the possible status messages
        tieStatuses=[NSArray arrayWithObjects:@"Tie.",@"Suit and Tie.",@"Evenly matched.",@"Again.",@"Just wait.",@"Tie-dye.",@"You didn't win.", nil];
        winStatuses=[NSArray arrayWithObjects:@"I win.",@"You lose.",@"I'm the best.",@"You can't win!",@"U mad bro?",@"I win!",@"iWin", nil];
        
        //Set the background to white
        self.backgroundColor = [SKColor whiteColor];
        
        //Draw the title
        SKLabelNode *myLabel = [[SKLabelNode alloc]init];
        myLabel.text = @"Tic Tac Toe";
        myLabel.fontColor=[SKColor blackColor];
        myLabel.fontSize = 30;
        myLabel.position = CGPointMake(CGRectGetMidX(self.frame),self.frame.size.height-60);
        [self addChild:myLabel];
        
        //Draw the status label
        statusLabel = [[SKLabelNode alloc]init];
        statusLabel.text = @"Good Luck.";
        statusLabel.fontColor=[SKColor blackColor];
        statusLabel.fontSize = 25;
        statusLabel.position = CGPointMake(CGRectGetMidX(self.frame),80);
        [self addChild:statusLabel];
        
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
        
        //By default let the computer move first
        userGoesFirst=NO;
        [self computerMove];
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
                piece.text=@"X";
                piece.hidden=NO;
                if(engine.isGameOver()){
                    [self updateStatusLabel];
                }else{
                    [self computerMove];
                }
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
    [self updateStatusLabel];
}

-(void)updateStatusLabel{
    switch(engine.gameResult()){
        case 0:
            break;
        case 1:
            statusLabel.text=@"Hacker!!!";
            break;
        case 2:
            statusLabel.text=[self randomElement:winStatuses];
            break;
        case 3:
            statusLabel.text=[self randomElement:tieStatuses];
            break;
        default:
            break;
    }
}

-(id)randomElement:(NSArray *)array{
    return [array objectAtIndex:arc4random()%array.count];
}

-(void)update:(CFTimeInterval)currentTime {
    /* Called before each frame is rendered */
}

-(void)restartGame{
    statusLabel.text=@"Good Luck.";
    for(SKLabelNode *piece in pieces){
        piece.hidden=YES;
    }
    engine.restart(userGoesFirst);
    if(!engine.didUserGoFirst()){
        [self computerMove];
    }
}

@end

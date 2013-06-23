//
//  TTTEngine.h
//  Tic Tac Toe
//
//  Created by Scott Bouloutian on 6/21/13.
//  Copyright (c) 2013 Scott Bouloutian. All rights reserved.
//

#ifndef __Tic_Tac_Toe__TTTEngine__
#define __Tic_Tac_Toe__TTTEngine__

#include <iostream>
#include <algorithm>
#include <stdlib.h>

typedef unsigned char byte;

struct Node{
private:
    //Values in the state can either be 0,1, or 2
    //0 represents an empty space
    //1 represents the user's token
    //2 represents the computer's token
    byte state[9];
    bool userTurn;
public:
    Node(){
    }
    Node(bool _userTurn){
        for(byte i=0;i<9;i++){
            state[i]=0;
        }
        userTurn=_userTurn;
    }
    Node(const Node &node){
        for(byte i=0;i<9;i++){
            state[i]=node.state[i];
        }
        userTurn=node.userTurn;
    }
    byte* getState(){
        return state;
    }
    bool isUserTurn() const{
        return userTurn;
    }
    void changeTurns(){
        userTurn=!userTurn;
    }
};

class TTTEngine{
private:
    Node state;
    void possibleMoves(Node&,bool[9]);
    byte minimax(Node&);
    int maxValue(Node&,int,int);
    int minValue(Node&,int,int);
    byte gameStatus(Node&);
    Node placeToken(const Node&,byte);
    int utility(byte);
    bool userWentFirst;
public:
    TTTEngine();
    void restart(bool);
    void placeToken(byte);
    bool canPlaceToken(byte);
    byte getComputerMove();
    bool didUserGoFirst();
    bool isGameOver();
};

#endif /* defined(__Tic_Tac_Toe__TTTEngine__) */

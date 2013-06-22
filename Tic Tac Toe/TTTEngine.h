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
        for(byte i=0;i<9;i++){
            state[i]=0;
        }
        userTurn=true;
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
    void print(){
        for(int x=0;x<3;x++){
            for(int y=0;y<3;y++){
                std::cout<<(int)state[x+y*3]<<" ";
            }
            std::cout<<std::endl;
        }
    }
};

class TTTEngine{
private:
    Node state;
    void possibleMoves(Node&,bool[9]);
    int minimax(Node&);
    byte gameStatus(Node&);
    Node placeToken(const Node& node,byte);
    int utility(byte);
public:
    TTTEngine();
    void placeToken(byte,byte);
    bool canPlaceToken(byte);
    byte getComputerMove();
};

#endif /* defined(__Tic_Tac_Toe__TTTEngine__) */

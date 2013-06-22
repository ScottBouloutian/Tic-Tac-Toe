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
public:
    Node(){
        
    }
    Node(const Node &node){
        for(byte i=0;i<9;i++){
            state[i]=node.state[i];
        }
    }
    byte* getState(){
        return state;
    }
    void print(){
        for(int x=0;x<3;x++){
            for(int y=0;y<3;y++){
                std::cout<<state[x+y*3]<<" ";
            }
            std::cout<<std::endl;
        }
    }
};

class TTTEngine{
private:
    Node state;
    void possibleMoves(Node&,bool[9]);
    byte minimax(Node&);
    int maxValue(Node&,int,int);
    int minValue(Node&,int,int);
    int utility(Node&);
    bool isTie(Node&);
    Node placeToken(const Node& node,byte,byte);
public:
    TTTEngine();
    void placeToken(byte,byte);
    bool canPlaceToken(byte);
};

#endif /* defined(__Tic_Tac_Toe__TTTEngine__) */

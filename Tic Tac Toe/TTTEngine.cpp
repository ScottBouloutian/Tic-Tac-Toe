//
//  TTTEngine.cpp
//  Tic Tac Toe
//
//  Created by Scott Bouloutian on 6/21/13.
//  Copyright (c) 2013 Scott Bouloutian. All rights reserved.
//

using namespace std;

#include "TTTEngine.h"

TTTEngine::TTTEngine(){
}

void TTTEngine::placeToken(byte index,byte token){
    state=placeToken(state, index);
}

bool TTTEngine::canPlaceToken(byte index){
    return (state.isUserTurn() && state.getState()[index]==0);
}

int TTTEngine::minimax(Node &node){
    byte status=gameStatus(node);
    if(status!=0){
        if(node.isUserTurn()){
            return utility(status);
        }else{
            return -utility(status);
        }
    }
    int a=-999;
    bool moves[9];
    possibleMoves(node,moves);
    for(int i=0;i<9;i++){
        if(moves[i]){
            Node child=placeToken(node, i);
            a=max(a,-minimax(child));
        }
    }
    return a;
}

int TTTEngine::utility(byte gameStatus){
    switch(gameStatus){
        case 0:
            return 0;
        case 1:
            return -50;
        case 2:
            return 50;
        case 3:
            return 0;
        default:
            return 0;
    }
}

void TTTEngine::possibleMoves(Node &node,bool moves[9]){
    for(byte i=0;i<9;i++){
        if(node.getState()[i]==0){
            moves[i]=true;
        }else{
            moves[i]=false;
        }
    }
    
}

byte TTTEngine::gameStatus(Node &node){
    //Check for winners in every row
    for(byte row=0;row<3;row++){
        if (node.getState()[row*3]==1 && node.getState()[row*3+1]==1 && node.getState()[row*3+2]==1){
            return 1;
        }
        if (node.getState()[row*3]==2 && node.getState()[row*3+1]==2 && node.getState()[row*3+2]==2){
            return 2;
        }
    }
    
    //Check for winners in every column
    for(byte col=0;col<3;col++){
        if (node.getState()[col]==1 && node.getState()[col+3]==1 && node.getState()[col+6]==1){
            return 1;
        }
        if (node.getState()[col]==2 && node.getState()[col+3]==2 && node.getState()[col+6]==2){
            return 2;
        }
    }
    
    //Check for winners in the diagonals
    if(node.getState()[0]==1 && node.getState()[4]==1 && node.getState()[8]==1){
        return 1;
    }
    if(node.getState()[0]==2 && node.getState()[4]==2 && node.getState()[8]==2){
        return 2;
    }
    if(node.getState()[2]==1 && node.getState()[4]==1 && node.getState()[6]==1){
        return 1;
    }
    if(node.getState()[2]==2 && node.getState()[4]==2 && node.getState()[6]==2){
        return 2;
    }
    
    //Check for a tie
    for(byte i=0;i<9;i++){
        if(state.getState()[i]==0){
            return 0;
        }
    }
    return 3;
}

Node TTTEngine::placeToken(const Node &node, byte index){
    Node result(node);
    if(node.isUserTurn()){
        result.getState()[index]=1;
    }else{
        result.getState()[index]=2;
    }
    result.changeTurns();
    return result;
}

byte TTTEngine::getComputerMove(){
    byte bestMove=0;
    int bestUtility=-999;
    int utility;
    
    bool moves[9];
    possibleMoves(state,moves);
    for(int i=0;i<9;i++){
        if(moves[i]){
            Node child=placeToken(state, i);
            utility=minimax(child);
            if(utility>bestUtility){
                bestUtility=utility;
                bestMove=i;
            }
        }
    }

    return bestMove;
}
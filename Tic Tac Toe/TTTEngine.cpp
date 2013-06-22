//
//  TTTEngine.cpp
//  Tic Tac Toe
//
//  Created by Scott Bouloutian on 6/21/13.
//  Copyright (c) 2013 Scott Bouloutian. All rights reserved.
//

#include "TTTEngine.h"

TTTEngine::TTTEngine(){
    
}

void TTTEngine::placeToken(byte index,byte token){
    state=placeToken(state, index,token);
}

bool TTTEngine::canPlaceToken(byte index){
    return (state.getState()[index]==0);
}

byte TTTEngine::minimax(Node &node){
    int v=maxValue(node, -999, 999);
    std::cout<<"Solution found: "<<v<<std::endl;
    return 0;
}

int TTTEngine::maxValue(Node &node, int alpha, int beta){
    //If we are at a terminal node return the utility
    if(isTie(node)){
        return 0;
    }else{
        int util=utility(node);
        if(util!=0){
            return util;
        }
    }
    
    int v=-999;
    bool moves[9];
    possibleMoves(node, moves);
    for(int i=0;i<9;i++){
        if(moves[i]){
            
        }
    }
    return 0;
}

int TTTEngine::minValue(Node &node, int alpha, int beta){
    return 0;
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

int TTTEngine::utility(Node &node){
    //Check for winners in every row
    for(byte row=0;row<3;row++){
        if (node.getState()[row*3]==1 && node.getState()[row*3+1]==1 && node.getState()[row*3+2]==1){
            return -1;
        }
        if (node.getState()[row*3]==2 && node.getState()[row*3+1]==2 && node.getState()[row*3+2]==2){
            return 1;
        }
    }
    
    //Check for winners in every column
    for(byte col=0;col<3;col++){
        if (node.getState()[col]==1 && node.getState()[col+3]==1 && node.getState()[col+6]==1){
            return -1;
        }
        if (node.getState()[col]==2 && node.getState()[col+3]==2 && node.getState()[col+6]==2){
            return 1;
        }
    }

    //Check for winners in the diagonals
    if(node.getState()[0]==1 && node.getState()[4]==1 && node.getState()[8]==1){
        return -1;
    }
    if(node.getState()[0]==2 && node.getState()[4]==2 && node.getState()[8]==2){
        return 1;
    }
    if(node.getState()[2]==1 && node.getState()[4]==1 && node.getState()[6]==1){
        return -1;
    }
    if(node.getState()[2]==2 && node.getState()[4]==2 && node.getState()[6]==2){
        return 1;
    }
    return 0;
}

bool TTTEngine::isTie(Node &node){
    for(int i=0;i<9;i++){
        if (state.getState()[i]==0){
            return false;
        }
    }
    return true;
}

Node TTTEngine::placeToken(const Node &node, byte index, byte token){
    Node result(node);
    result.getState()[index]=token;
    return result;
}
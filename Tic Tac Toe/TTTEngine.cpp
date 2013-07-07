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
    restart(false);
}

void TTTEngine::placeToken(byte index){
    state=placeToken(state, index);
}

bool TTTEngine::canPlaceToken(byte index){
    return (state.isUserTurn() && !isGameOver() && state.getState()[index]==0);
}

byte TTTEngine::minimax(Node &node){
    int utility;
    byte bestMoves[9]={0,0,0,0,0,0,0,0,0};
    byte numMoves=0;
    int bestUtility=-999;

    bool moves[9];
    possibleMoves(node, moves);
    for(byte i=0;i<9;i++){
        if(moves[i]){
            Node child=placeToken(node, i);
            utility=minValue(child,-999,999);
            if(utility>bestUtility){
                bestUtility=utility;
                bestMoves[0]=i;
                numMoves=1;
            }else if(utility==bestUtility){
                bestMoves[numMoves]=i;
                numMoves++;
            }
        }
    }
    return bestMoves[rand() % numMoves];
}

int TTTEngine::maxValue(Node &node,int alpha,int beta){
    byte status=gameStatus(node);
    if(status!=0){
        return utility(status);
    }
    
    bool moves[9];
    possibleMoves(node, moves);
    int v=-999;
    for(byte i=0;i<9;i++){
        if(moves[i]){
            Node child=placeToken(node, i);
            v=max(v,minValue(child,alpha,beta));
            if(v>=beta){
                return v;
            }
            alpha=max(alpha,v);
        }
    }
    return v;
}

int TTTEngine::minValue(Node &node,int alpha,int beta){
    byte status=gameStatus(node);
    if(status!=0){
        return utility(status);
    }
    
    bool moves[9];
    possibleMoves(node, moves);
    int v=999;
    for(byte i=0;i<9;i++){
        if(moves[i]){
            Node child=placeToken(node, i);
            v=min(v,maxValue(child,alpha,beta));
            if(v<=alpha){
                return v;
            }
            beta=min(beta,v);
        }
    }
    return v;
}

int TTTEngine::utility(byte gameStatus){
    if(gameStatus==1){
        return -1;
    }
    if(gameStatus==2){
        return 1;
    }
    if(gameStatus==3){
        return 0;
    }
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

byte TTTEngine::gameStatus(Node &node){
    for(byte t=1;t<=2;t++){
        //Check for winners in every row
        for(byte row=0;row<3;row++){
            if (node.getState()[row*3]==t && node.getState()[row*3+1]==t && node.getState()[row*3+2]==t){
                return t;
            }
        }
        
        //Check for winners in every column
        for(byte col=0;col<3;col++){
            if (node.getState()[col]==t && node.getState()[col+3]==t && node.getState()[col+6]==t){
                return t;
            }
        }
        
        //Check for winners in the diagonals
        if(node.getState()[0]==t && node.getState()[4]==t && node.getState()[8]==t){
            return t;
        }
        if(node.getState()[2]==t && node.getState()[4]==t && node.getState()[6]==t){
            return t;
        }
    }
    
    //Check for a tie
    for(byte i=0;i<9;i++){
        if(node.getState()[i]==0){
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
    return minimax(state);
}

bool TTTEngine::isGameOver(){
    return (gameStatus(state)!=0);
}

byte TTTEngine::gameResult(){
    return gameStatus(state);
}

void TTTEngine::restart(bool userStarts){
    userWentFirst=userStarts;
    state=Node(userStarts);
}

bool TTTEngine::didUserGoFirst(){
    return userWentFirst;
}
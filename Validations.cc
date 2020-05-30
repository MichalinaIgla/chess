#include<iostream>
#include "Piece.h"
#include "Square.h"
#include "Game.h"
#include <sstream>
#include <ctype.h>
#include <cmath>
#include <ncurses.h>
#include <unistd.h>
void Sleep(unsigned milliseconds)
{
	usleep(milliseconds * 1000); // takes microseconds
}
using namespace std;

    //this function performs all chess rules validation of the previously correctly-formatted move
    bool Game::validateGameRules(string move, Square board[8][8], char currPlayer){

        //convert to INT
        stringstream stream;

        int n1, n2;
        stream<<move[1];  //convert the char number to an int number
        stream>>n1;
        stream.clear();

        stream<<move[7]; //convert the char number to an int number
        stream>>n2;

        
        // for (int i=0; i<move.length(); ++i)
        move[0] = tolower(move[0]);
        move[6] = tolower(move[6]);

        int l1, l2;	
        //convert the letter to a number so it can be used as an index
        if(move[0] == 'a')
            l1 = 0;
        else if(move[0] == 'b')
            l1 = 1;
        else if(move[0] == 'c')
            l1 = 2;
        else if(move[0] == 'd')
            l1 = 3;
        else if(move[0] == 'e')
            l1 = 4;
        else if(move[0] == 'f')
            l1 = 5;
        else if(move[0] == 'g')
            l1 = 6;
        else
            l1 = 7;

        
        if(move[6] == 'a')
            l2 = 0;
        else if(move[6] == 'b')
            l2 = 1;
        else if(move[6] == 'c')
            l2 = 2;
        else if(move[6] == 'd')
            l2 = 3;
        else if(move[6] == 'e')
            l2 = 4;
        else if(move[6] == 'f')
            l2 = 5;
        else if(move[6] == 'g')
            l2 = 6;
        else
            l2 = 7;
            


        if(board[n1][l1].piece == nullptr){
            printw("There's no piece at the specified location.");
            return false;
        }

        //check if the piece is the current Player's piece
        if(board[n1][l1].piece != nullptr && currPlayer != board[n1][l1].piece->player){
            cout<<"That's not your piece."<<endl<<endl;
            return false;
        }

        //check if the player has a friendly piece at the desired move location
        if(board[n2][l2].piece != nullptr && currPlayer == board[n2][l2].piece->player){
            cout<<"You already have a piece there."<<endl<<endl;
            return false;
        }


        //X AND Y DIFFERENCES
        int rowDiff = n1-n2;
        int colDiff = l1-l2;


    /* W'S PAWN  */
        if(board[n1][l1].piece->name.compare("Pawn") == 0 && currPlayer == 'W'){

            //this is to take into account that pawns can move 2 spaces on their first move, but not after
            if(n1 != 1 && rowDiff <= -2){
                printw("Pawns can't move like that!!!!!");
                return false;	
            }

            //if it is the pawn's first move and they try to move like 12 spaces
            else if(n1 == 1 && rowDiff < -2){
                cout<<"Pawns may move 2 spaces forward on their first move."<<endl<<endl;
                return false;
            }

            //rowDiff must ALWAYS be negative...no backwards or side to side movement for pawns
            else if(rowDiff >= 0){
                cout<<"Pawns can't move like that."<<endl<<endl;
                return false;
            }
            
            //no matter what pawns can only move a maximum of one column over at a time
            else if(abs(colDiff) > 1){
                cout<<"Pawns can't move like that."<<endl<<endl;
                return false;
            }

            //if they try to move diagonally without there being an enemy piece there
            else if(abs(colDiff) == 1 && rowDiff == -1 && board[n2][l2].piece == nullptr){
                cout<<"There must be an enemy piece at "<<l2<<n2<<" for you to move there."<<endl<<endl;
                return false;
            }

            //if they try to move 1 space forward but there's an enemy there...
            else if(rowDiff == -1 && colDiff == 0 && board[n2][l2].piece != nullptr && board[n2][l2].piece->player == 'B'){
                cout<<"An enemy piece is blocking your move!"<<endl<<endl;
                return false;
            }

            //if they try to move diagonally to a space and there's an enemy piece there...
            else if(rowDiff == -1 && abs(colDiff) == 1 && board[n2][l2].piece->player == 2){

                cout<<"You have taken the enemy's "<<board[n2][l2].piece->name<<"!"<<endl<<endl;

                board[n2][l2].piece = board[n1][l1].piece;	//piece taken
                board[n1][l1].piece = nullptr;

                Sleep(2000);
                return true;
            }

            //valid forward move with no enemy pieces in the way...
            else{
                printw("Move successful!");
                board[n2][l2].piece = board[n1][l1].piece;
                board[n1][l1].piece = nullptr;
                Sleep(1000);
                return true;
            }
        }

    /* B'S PAWN */
        else if(board[n1][l1].piece->name.compare("Pawn") == 0 && currPlayer == 'B'){

            //this is to take into account that pawns can move 2 spaces on their first move, but not after
            if(n1 != 6 && rowDiff >= 2){
                cout<<"Pawns can't move like that."<<endl<<endl;
                return false;
            }

            //if it is the pawn's first move and they try to move like 12 spaces...
            else if(n1 == 6 && rowDiff > 2){            
                cout<<"Pawns may move 2 spaces forward their first move."<<endl<<endl;
                return false;            
            }

            //rowDiff must ALWAYS be negative...no backwards or side to side movement for pawns
            else if(rowDiff <= 0){            
                cout<<"Pawns can't move like that."<<endl<<endl;
                return false;
            }
            
            //no matter what pawns can only move a maximum of one column over at a time
            else if(abs(colDiff) > 1){            
                cout<<"Pawns can't move like that."<<endl<<endl;
                return false;            
            }

            //if they try to move diagonally without there being an enemy piece there
            else if(abs(colDiff) == 1 && rowDiff == 1 && board[n2][l2].piece == nullptr){            
                cout<<"There must be an enemy piece at "<<l2<<n2<<" for you to move there."<<endl<<endl;
                return false;
            }

            //if they try to move 1 space forward but there's an enemy there...
            else if(rowDiff == 1 && colDiff == 0 && board[n2][l2].piece != nullptr && board[n2][l2].piece->player == 1){
            
                cout<<"An enemy piece is blocking your move!"<<endl<<endl;
                return false;
            
            }

            //if they try to move diagonally to a space and there's an enemy piece there...
            else if(rowDiff == 1 && abs(colDiff) == 1 && board[n2][l2].piece->player == 1){

                cout<<"You have taken the enemy's "<<board[n2][l2].piece->name<<"!"<<endl<<endl;

                board[n2][l2].piece = board[n1][l1].piece;	//piece taken
                board[n1][l1].piece = nullptr;
                Sleep(2000);
                return true;
            
            }

            //valid forward move with no enemy pieces in the way...
            else{
                printw("Move successful!");
                board[n2][l2].piece = board[n1][l1].piece;
                board[n1][l1].piece = nullptr;
                Sleep(1000);
                return true;
            }
        }


        /*  King  */
        else if(board[n1][l1].piece->name.compare("King") == 0){
            if(abs(rowDiff) > 1 || abs(colDiff) > 1){
                printw("Kings may only move one space at a time.");
                return false;
            }
        
        
            if(board[n2][l2].piece != nullptr && board[n2][l2].piece->player != currPlayer){ 
                printw("You have taken the enemy's %s ", board[n2][l2].piece->name);
                // cout<<"You have taken the enemy's "<<board[n2][l2].piece->name<<"!"<<endl<<endl;
                board[n2][l2].piece = board[n1][l1].piece;	//piece taken
                board[n1][l1].piece = nullptr;
                Sleep(2000);
                return true;
            }

            else{
                cout<<"Move successful!"<<endl<<endl;
                board[n2][l2].piece = board[n1][l1].piece;
                board[n1][l1].piece = nullptr;
                Sleep(2000);
                return true;
            
            }
        }


        /* Queeen */
        else if(board[n1][l1].piece->name.compare("Queen") == 0){

            //if they just try to move to some random spot
            if(abs(rowDiff) != abs(colDiff) && rowDiff != 0 && colDiff != 0){
            
                cout<<"Queens can do a lot of things, but not this."<<endl<<endl;
                return false;
            
            }

            //COLLISION CHECKING IF STATEMENTS//
            if(rowDiff > 0 && colDiff > 0){

                //cout<<"rowDiff > 0 && colDiff > 0"<<endl<<endl;
                for(int i = n1-1; i > n2; i--){                
                    for(int j = l1-1; j > l2; j --){                    
                        if(board[i][j].piece != nullptr){                        
                            cout<<"There's a piece blocking your move!"<<endl<<endl;
                            return false;                        
                        }
                    }
                }
            }

            else if(rowDiff < 0 && colDiff < 0){

                //cout<<"rowDiff < 0 && colDiff < 0"<<endl<<endl;
            
                for(int i = n1+1; i < n2; i++){                
                    for(int j = l1+1; j < l2; j ++){                    
                        if(board[i][j].piece != nullptr){                        
                            cout<<"There's a piece blocking your move!"<<endl<<endl;
                            return false;
                        
                        }
                    }
                }
            }

            else if(rowDiff > 0 && colDiff < 0){

                //cout<<"rowDiff > 0 && colDiff < 0"<<endl<<endl;
            
                for(int i = n1-1; i > n2; i--){                
                    for(int j = l1+1; j < l2; j ++){                    
                        if(board[i][j].piece != nullptr){                        
                            cout<<"There's a piece blocking your move!"<<endl<<endl;
                            return false;
                        
                        }
                    }
                }
            }

            else if(rowDiff < 0 && colDiff > 0){

                //cout<<"rowDiff < 0 && colDiff > 0"<<endl<<endl;
            
                for(int i = n1+1; i < n2; i++){                
                    for(int j = l1-1; j > l2; j --){                    
                        if(board[i][j].piece != nullptr){                        
                            cout<<"There's a piece blocking your move!"<<endl<<endl;
                            return false;
                        
                        }
                    }
                }
            }

            else if(rowDiff == 0 && colDiff > 0){

                //cout<<"rowDiff == 0 && colDiff > 0"<<endl<<endl;
            
                for(int i = l1-1; i > l2; i--){                
                    if(board[n1][i].piece != nullptr){                    
                        cout<<"There's a piece blocking your move!"<<endl<<endl;
                        return false;
                    
                    }
                }
            }

            else if(rowDiff == 0 && colDiff < 0){
                //cout<<"rowDiff == 0 && colDiff < 0"<<endl<<endl;
                for(int i = l1+1; i < l2; i++){                
                    if(board[n1][i].piece != nullptr){                    
                        cout<<"There's a piece blocking your move!"<<endl<<endl;
                        return false;
                    
                    }
                }
            }

            else if(rowDiff > 0 && colDiff == 0){

                //cout<<"rowDiff > 0 && colDiff == 0"<<endl;
            
                for(int i = n1-1; i > n2; i--){
                    if(board[i][l1].piece != nullptr){
                        cout<<"There's a piece blocking your move!"<<endl<<endl;
                        return false;
                    }
                }
            }

            else if(rowDiff < 0 && colDiff == 0){

                //cout<<"rowDiff < 0 && colDiff == 0"<<endl<<endl;
            
                for(int i = n1+1; i < n2; i++){
                    if(board[i][l1].piece != nullptr){
                        cout<<"There's a piece blocking your move!"<<endl<<endl;
                        return false;
                    
                    }
                }
            }

            //Sleep(5000);

            if(board[n2][l2].piece != nullptr && board[n2][l2].piece->player != currPlayer){
            
                cout<<"You have taken the enemy's "<<board[n2][l2].piece->name<<"!"<<endl<<endl;
                board[n2][l2].piece = board[n1][l1].piece;	//piece taken
                board[n1][l1].piece = nullptr;
                Sleep(2000);
                return true;
            
            }

            else{
            
                cout<<"Move successful!"<<endl<<endl;
                board[n2][l2].piece = board[n1][l1].piece;
                board[n1][l1].piece = nullptr;
                Sleep(2000);
                return true;

            }
        }

        else if(board[n1][l1].piece->name.compare("Knight") == 0){
        
            //I think I'm rather clever for figuring this out...
            if(abs(rowDiff)*abs(colDiff) != 2){
                cout<<"Knights can't move like that."<<endl<<endl;
                return false;                        
            }
        
            if(board[n2][l2].piece != nullptr && board[n2][l2].piece->player != currPlayer){
            
                // cout<<"You have taken the enemy's "<<board[n2][l2].piece->name<<"!"<<endl<<endl;
                printw("You have taken the enemy's %s ", board[n2][l2].piece->name);
                board[n2][l2].piece = board[n1][l1].piece;	//piece taken
                board[n1][l1].piece = nullptr;
                Sleep(2000);
                return true;
            }

            else{
                printw("Move successful!");
                board[n2][l2].piece = board[n1][l1].piece;
                board[n1][l1].piece = nullptr;
                Sleep(2000);
                return true;
            }
        }

        else if(board[n1][l1].piece->name.compare("Bishop") == 0){
        
            //just specifying diagonal movmement only
            if(abs(rowDiff) != abs(colDiff)){
                // cout<<"Bishops can't move like that."<<endl;
                printw("Bishops can't move like that.");
                return false;
            }

            //COLLISION CHECKING IF STATEMENTS
            if(rowDiff > 0 && colDiff > 0){            
                for(int i = n1-1; i > n2; i--){                
                    for(int j = l1-1; j > l2; j --){                    
                        if(board[i][j].piece != nullptr){                        
                            cout<<"There's a piece blocking your move!"<<endl<<endl;
                            return false;                        
                        }
                    }
                }
            }

            else if(rowDiff < 0 && colDiff < 0){
            
                for(int i = n1+1; i < n2; i++){                
                    for(int j = l1+1; j < l2; j ++){                    
                        if(board[i][j].piece != nullptr){                        
                            cout<<"There's a piece blocking your move!"<<endl<<endl;
                            return false;                        
                        }
                    }
                }
            }

            else if(rowDiff > 0 && colDiff < 0){

                for(int i = n1-1; i > n2; i--){
                    for(int j = l1+1; j < l2; j ++){
                        if(board[i][j].piece != nullptr){
                            cout<<"There's a piece blocking your move!"<<endl<<endl;
                            return false;
                        }
                    }
                }
            }

            else if(rowDiff < 0 && colDiff > 0){
            
                for(int i = n1+1; i < n2; i++){    
                    for(int j = l1-1; j > l2; j --){
                        if(board[i][j].piece != nullptr){
                            cout<<"There's a piece blocking your move!"<<endl<<endl;
                            return false;
                        }
                    }
                }
            }

            //STANDARD PIECE TAKING CODE (SAME FOR ALL PIECES FOR P1)
            if(board[n2][l2].piece != nullptr && board[n2][l2].piece->player != currPlayer){
            
                cout<<"You have taken the enemy's "<<board[n2][l2].piece->name<<"!"<<endl<<endl;
                board[n2][l2].piece = board[n1][l1].piece;	//piece taken
                board[n1][l1].piece = nullptr;
                Sleep(2000);
                return true;
            }

            else{

                printw("Move successful!");
                board[n2][l2].piece = board[n1][l1].piece;
                board[n1][l1].piece = nullptr;
                Sleep(2000);
                return true;                        
            }
        }

        else if(board[n1][l1].piece->name.compare("Rook") == 0){
            if(rowDiff != 0 && colDiff != 0){            
                cout<<"Rooks can't move like that."<<endl<<endl;
                return false;
            
            }

            //COLLISION CHECKING IF STATEMENTS
            if(rowDiff == 0 && colDiff > 0){            
                for(int i = l1-1; i > l2; i--){                
                    if(board[n1][i].piece != nullptr){                    
                        cout<<"There's a piece blocking your move!"<<endl<<endl;
                        return false;
                    
                    }
                }
            }

            else if(rowDiff == 0 && colDiff < 0){            
                for(int i = l1+1; i < l2; i++){
                    if(board[n1][i].piece != nullptr){                    
                        cout<<"There's a piece blocking your move!"<<endl<<endl;
                        return false;
                    }
                }
            }

            else if(rowDiff > 0 && colDiff == 0){
            
                for(int i = n1-1; i > n2; i--){
                    if(board[i][l1].piece != nullptr){
                        cout<<"There's a piece blocking your move!"<<endl<<endl;
                        return false;
                    }
                }
            }

            else if(rowDiff < 0 && colDiff == 0){
            
                for(int i = n1+1; i < n2; i++){
                    if(board[i][l1].piece != nullptr){
                        cout<<"There's a piece blocking your move!"<<endl<<endl;
                        return false;
                    
                    }
                }
            }
        
            if(board[n2][l2].piece != nullptr && board[n2][l2].piece->player != currPlayer){
            
                cout<<"You have taken the enemy's "<<board[n2][l2].piece->name<<"!"<<endl<<endl;
                board[n2][l2].piece = board[n1][l1].piece;	//piece taken
                board[n1][l1].piece = nullptr;
                Sleep(2000);
                return true;
            }

            else{
                // cout<<"Move successful!"<<endl<<endl;
                printw("Move successful!");
                board[n2][l2].piece = board[n1][l1].piece;
                board[n1][l1].piece = nullptr;
                Sleep(2000);
                return true;
            }
        }
        
        else {
            return false;	
        }
    }
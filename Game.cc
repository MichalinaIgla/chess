#include<iostream>
#include "Piece.h"
#include "Square.h"
#include "Game.h"
#include <sstream>
#include <ctype.h>
#include <cmath>
#include <ncurses.h>
// git push -u origin master
using namespace std;
// g++ Game.cc Piece.cc Square.cc main.cc Validations.cc -lncurses -o play2
Game :: Game(){}
Game :: ~Game(){}

void Game::play(){

        initscr(); 
        int row,col;
        keypad(stdscr, TRUE);
        getmaxyx(stdscr,row,col);

        Square board[8][8];	//chess board

        Piece k10("King", 'W');		 //the first digit indicates which player's piece it is followed by the piece's unique number
        Piece q10("Queen", 'W');
        Piece r10("Rook", 'W');
        Piece r11("Rook", 'W');		//the pieces are designated solely by their name; a string. 
        Piece b10("Bishop", 'W');	//string comparisons must be used to figure out which piece is which.
        Piece b11("Bishop", 'W');
        Piece kn10("Knight", 'W');
        Piece kn11("Knight", 'W');
        Piece p10("Pawn", 'W');
        Piece p11("Pawn", 'W');
        Piece p12("Pawn", 'W');
        Piece p13("Pawn", 'W');
        Piece p14("Pawn", 'W');
        Piece p15("Pawn", 'W');
        Piece p16("Pawn", 'W');
        Piece p17("Pawn", 'W');


        Piece k20("King", 'B');		 
        Piece q20("Queen", 'B');
        Piece r20("Rook", 'B');
        Piece r21("Rook", 'B');		
        Piece b20("Bishop", 'B');	
        Piece b21("Bishop", 'B');
        Piece kn20("Knight", 'B');
        Piece kn21("Knight", 'B');
        Piece p20("Pawn", 'B');
        Piece p21("Pawn", 'B');
        Piece p22("Pawn", 'B');
        Piece p23("Pawn", 'B');
        Piece p24("Pawn", 'B');
        Piece p25("Pawn", 'B');
        Piece p26("Pawn", 'B');
        Piece p27("Pawn", 'B');

        //placing the pieces on the board for P1
        board[0][0].piece = &r10;
        board[0][1].piece = &kn10;
        board[0][2].piece = &b10;
        board[0][3].piece = &q10;
        board[0][4].piece = &k10;
        board[0][5].piece = &b11;
        board[0][6].piece = &kn11;
        board[0][7].piece = &r11;

        board[1][0].piece = &p10;
        board[1][1].piece = &p11;
        board[1][2].piece = &p12;
        board[1][3].piece = &p12;
        board[1][4].piece = &p13;
        board[1][5].piece = &p14;
        board[1][6].piece = &p15;
        board[1][7].piece = &p16;

        //placing the pieces on the board for P2
        board[7][0].piece = &r20;
        board[7][1].piece = &kn20;
        board[7][2].piece = &b20;
        board[7][3].piece = &q20;
        board[7][4].piece = &k20;
        board[7][5].piece = &b21;
        board[7][6].piece = &kn21;
        board[7][7].piece = &r21;

        board[6][0].piece = &p20;
        board[6][1].piece = &p21;
        board[6][2].piece = &p22;
        board[6][3].piece = &p22;
        board[6][4].piece = &p23;
        board[6][5].piece = &p24;
        board[6][6].piece = &p25;
        board[6][7].piece = &p26;


        char currPlayer = 'B';

        int p1Pieces = 16;	//these will be used to determine when the game is over (# of pieces = 0 for either player)
        int p2Pieces = 16;

        // string move;	//move to be parsed


        // Main loop 
        while(true){	

            clear();

            //switching the player
            if(currPlayer == 'W')
                currPlayer = 'B';
            else
                currPlayer = 'W';
                
            display(board);
            

            printw( "\n%c enter your move: ", currPlayer);
            
            refresh(); 
 
            char* move = new char[10];
            // string move;
            getstr(move);
            
            while(validateFormat(move) == false){
            

                printw( "Format e.g. 'a1 to a2' Please re-enter.");
                printw( "\n%c enter your move: ", currPlayer);
                // getline(cin, move);
                getstr(move);
            }	

            while(validateGameRules(move, board, currPlayer) == false){
        
                 printw( "\n%c enter your move: ", currPlayer);
                getstr(move);
            
            }
        }
    }

    // // make sure that the user has entered a potentially correct move based on formatting alone
    bool Game::validateFormat(string move){

            for (int i=0; i<move.length(); ++i)
                move[i] = tolower(move[i]);

            //a valid move has 8 characters
            if(move.length() != 8)
                return false;
            
            // letters for destination index
            if(move[0] != 'a' && move[0] != 'b' && move[0] != 'c' && move[0] != 'd' &&  move[0] != 'e' && move[0] != 'f' && move[0] != 'g' && move[0] != 'h')
                return false;
            
            // numbers for destination index
            if(move[1] != '0' && move[1] != '1' && move[1] != '2' && move[1] != '3' && move[1] != '4' && move[1] != '5' && move[1] != '6' && move[1] != '7')
                return false;
            
            //check if player typed 'to'
            if(move[3] != 't' || move[4] != 'o')
                return false;
            
            // letters for destination index
            if(move[6] != 'a' && move[6] != 'b' && move[6] != 'c' && move[6] != 'd' && move[6] != 'e' && move[6] != 'f' && move[6] != 'g' && move[6] != 'h'){
                return false;
                }
                
            // numbers for destination index
            if(move[7] != '0' && move[7] != '1' && move[7] != '2' && move[7] != '3' && move[7] != '4' && move[7] != '5' && move[7] != '6' && move[7] != '7')
                return false;
            
            else return true;
    }


void Game::display(Square board[8][8]){

        char displayBoard[27][54] = {
 
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', 'A', ' ', ' ', ' ', ' ', ' ', 'B', ' ', ' ', ' ', ' ', ' ', 'C', ' ', ' ', ' ', ' ', ' ', 'D', ' ', ' ', ' ', ' ', ' ', 'E', ' ', ' ', ' ', ' ', ' ', 'F', ' ', ' ', ' ', ' ', ' ', 'G', ' ', ' ', ' ', ' ', ' ', 'H', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, 
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' '},
        {' ', ' ', '7', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' '}, 
        {' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', '6', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, 
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' '},
        {' ', ' ', '5', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' '}, 
        {' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', '4', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' '},
        {' ', ' ', '3', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' '},
        {' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', '2', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' '},
        {' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' '},
        {' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', '0', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', 'Q', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' '},

    };

        //"displayColumn"
        int dC0 = 7;
        int dC1 = 13;
        int dC2 = 19;
        int dC3 = 25;
        int dC4 = 31;
        int dC5 = 37;
        int dC6 = 43;
        int dC7 = 49;

        int tempRow = 0;
        int tempColumn = 0;

        //updates real piece locations on the "display board"
        for(int i = 0; i < 8; i++){ //row
            if(i == 0)
                tempRow = 24;   
            else if(i == 1)
                tempRow =  21;
            else if(i == 2)
                tempRow = 18;
            else if(i == 3)
                tempRow = 15;
            else if(i == 4)
                tempRow = 12;
            else if(i == 5)
                tempRow = 9;
            else if(i == 6)
                tempRow =  6;
            else
                tempRow = 3;
            
            for(int j = 0; j < 8; j++){ //column
                if(j == 0)
                    tempColumn = 7; //dC0
                else if(j == 1)
                    tempColumn = 13;
                else if(j == 2)	
                    tempColumn = 19;
                else if(j == 3)
                    tempColumn = 25;
                else if(j == 4)
                    tempColumn = 31;
                else if(j == 5)
                    tempColumn = 37;
                else if(j == 6)
                    tempColumn = 43;
                else
                    tempColumn = 49;
                    
                
                //update display board pieces to match the real board
                if(board[i][j].piece == nullptr){

                }
                else if(board[i][j].piece->name.compare("Pawn") == 0)
                    displayBoard[tempRow][tempColumn] = 'P';
                
                else if(board[i][j].piece->name.compare("King") == 0)
                    displayBoard[tempRow][tempColumn] = 'K';

                else if(board[i][j].piece->name.compare("Queen") == 0)
                    displayBoard[tempRow][tempColumn] = 'Q';
                
                else if(board[i][j].piece->name.compare("Bishop") == 0)
                    displayBoard[tempRow][tempColumn] = 'B';

                else if(board[i][j].piece->name.compare("Knight") == 0)
                    displayBoard[tempRow][tempColumn] = 'N';
                
                else 
                    displayBoard[tempRow][tempColumn] = 'R';
                

                //W or B before pieces
                attron(A_STANDOUT);
                if (board[i][j].piece != nullptr){
                    if(board[i][j].piece->player == 'W')
                        displayBoard[tempRow][tempColumn-1] = 'W';
                    else 
                        displayBoard[tempRow][tempColumn-1] = 'B';
                }
            }
        }

        //DISPLAY
        for(int i = 0; i < 26; i++){ //row
            for(int j = 0; j < 53; j++){ //column
                attron(A_BOLD );
                mvaddch(i, j, displayBoard[i][j]);
            }
        }

        printw("\n"); 
}



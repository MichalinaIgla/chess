#include "Square.h"

class Game{
public:
	Game();
    void play();
    void display(Square board[8][8]);
    bool validateFormat(string move);
    bool validateGameRules(string move, Square board[8][8], char currPlayer);
    ~Game(void);
};
#include "Square.h"


Square::Square(){

	piece = nullptr; //empty pointer
}

Square::Square(Piece *p){

	piece = p;
}

Square::~Square(void){}

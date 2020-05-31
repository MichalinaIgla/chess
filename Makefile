chess.o: main.o Game.o
    g++ Game.cc Piece.cc Square.cc main.cc Validations.cc -lncurses -o play.o

Game.o:
    g++ 

clean:
    rm -rf *.o
    rm -rf MyProgram

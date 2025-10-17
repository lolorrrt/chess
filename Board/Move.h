#include "board.cpp"

#ifndef MOVE
#define MOVE

class Move{
    private:
        Field moveOrigin;
        Field moveTarget;

    public:
        Move();
        Move(Field origin, Field target);

        bool isValid();

        bool hasPiece();

        bool piecesWithinBoard();

        bool piecesOfDifferentColor();

        void drawUpdatedBoard();

        void execute(sf::RenderWindow &window, Board chessboard);

        void printInformation();
};

#endif MOVE
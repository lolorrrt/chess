#include "../Pieces/piece.cpp"
#include <SFML/Graphics.hpp>
#include <iostream>

/*#ifndef FIELD
#define FIELD*/

class Field{
    private:
        const float squareSize = 100;
        std::pair<int,int> coordinates;
        Piece piece;
        sf::RectangleShape square;
        sf::Texture pieceTexture;

    public:
        Field();
        Field(std::pair<int,int> initialCoordinates, Piece initialPiece);

        Piece getPiece();

        sf::RectangleShape getSquare();

        int getIndex();

        sf::Sprite drawPiece();

        void draw(sf::RenderWindow &window);

        void undrawPiece(sf::RenderWindow &window);

        bool isOutOfBounds();
    };

//#endif FIELD
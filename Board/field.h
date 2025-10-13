#include "../Pieces/piece.cpp"
#include <SFML/Graphics.hpp>
#include <iostream>

#ifndef FIELD
#define FIELD

#define squareSize 100

class Field{
    private:
    
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

        std::pair<int,int> getCoordinates();

        bool isNotInitialized();
        
        sf::Sprite drawPiece();

        void draw(sf::RenderWindow &window);

        void undrawPiece(sf::RenderWindow &window);

        bool isOutOfBounds();
    };

#endif FIELD
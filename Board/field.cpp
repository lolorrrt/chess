//#include <bitset>
//#include <cassert>

#include "field.h"

Field::Field() : coordinates({-1,-1}), piece(Piece(UNDEFINED_PIECE, UNDEFINED_COLOR)){}

int coordinateForDrawing(int coord){
    return float(coord) < 3.5 ? coord + 2*(3.5-coord) : coord + 2*(3.5-coord); 
}

Field::Field(std::pair<int,int> initialCoordinates, Piece initialPiece)
: coordinates(initialCoordinates), piece(initialPiece){

    square.setSize(sf::Vector2f(squareSize, squareSize));
    square.setPosition(coordinates.first * squareSize, coordinateForDrawing(coordinates.second) * squareSize);
            
    if ((coordinates.first + coordinates.second) % 2 == 1)
        square.setFillColor(sf::Color::Blue);
    else
        square.setFillColor(sf::Color::Red);
}

Piece Field::getPiece(){
    return piece;
}

sf::RectangleShape Field::getSquare(){
    return square;
}

int Field::getIndex(){
    return coordinates.second * 8 + coordinates.first;
}

std::pair<int,int> Field::getCoordinates(){
    return coordinates;
}

bool Field::isNotInitialized(){
    return coordinates.first == -1;
}

sf::Sprite Field::drawPiece(){
    if (piece.getPieceType() == UNDEFINED_PIECE || piece.getColor() == UNDEFINED_COLOR)
        return sf::Sprite();
                
    pieceTexture.loadFromFile("./images/" + std::to_string(piece.getColor()) + std::to_string(piece.getPieceType()) + ".jpeg");
    sf::Sprite pieceSprite;
    pieceSprite.setTexture(pieceTexture);
    pieceSprite.setScale(0.3f, 0.3f); 
    pieceSprite.setPosition(coordinates.first *100+ 15,coordinateForDrawing(coordinates.second) *100+15);

    return pieceSprite;
}

void Field::draw(sf::RenderWindow &window){
    window.draw(square);
    window.draw(drawPiece());
}

void Field::undrawPiece(sf::RenderWindow &window){
    window.draw(square);
}

bool Field::isOutOfBounds(){
    return coordinates.first < 0 || coordinates.first > 7 || coordinates.second < 0 || coordinates.second > 7;
}

void Field::reset(){
    coordinates = {-1,-1};
}

void Field::print(){
    std::cout << "At Field index: " << getIndex() << " and has PieceType " << getPiece().getPieceType() << std::endl;
}
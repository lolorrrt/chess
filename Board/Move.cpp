#include "Move.h"

Move::Move(){}

Move::Move(Field origin, Field target) : moveOrigin(origin), moveTarget(target){}

bool Move::hasPiece(){
    return moveOrigin.getPiece().getPieceType() != UNDEFINED_PIECE; 
};

bool Move::piecesWithinBoard(){
    return !moveOrigin.isOutOfBounds() && !moveTarget.isOutOfBounds();
};

bool Move::piecesOfDifferentColor(){
    return moveOrigin.getPiece().getColor() != moveTarget.getPiece().getColor();
};

bool Move::isValid(){
    return hasPiece() && piecesWithinBoard() && piecesOfDifferentColor();
};

void Move::drawUpdatedBoard(){

};

void Move::execute(sf::RenderWindow &window, Board chessboard){
    if(!moveOrigin.isNotInitialized() && !moveTarget.isNotInitialized()){
        chessboard.updateBitboards(moveOrigin, moveTarget);
        moveOrigin.undrawPiece(window);
        moveTarget.drawPiece();

        /*Board occupiedChessBoard = chessboard.occupiedPartOfBoard();
        Board unoccupiedChessBoard = chessboard.unoccupiedPartOfBoard();

        std::vector<Field> occupiedFieldList = occupiedChessBoard.drawOccupiedFields(window);
        std::vector<Field> unoccupiedFieldList = unoccupiedChessBoard.drawUnoccupiedFields(window);*/

        window.display();
    }
    
};

void Move::printInformation(){
    std::cout << "Move piece from piecetype " << moveOrigin.getPiece().getPieceType() << " from x: "
    << moveOrigin.getCoordinates().first << " y: " << moveOrigin.getCoordinates().second << std::endl;
    std::cout << "to piece from piecetype " << moveTarget.getPiece().getPieceType() << " to x: "
    << moveTarget.getCoordinates().first << " y: " << moveTarget.getCoordinates().second << std::endl;
}
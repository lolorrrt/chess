#include "bitboard.h"
#include <math.h>

BitBoard::BitBoard() : bits(0), bitboardtype(){}
BitBoard::BitBoard(int64_t initialBits, BitBoardType initialBitBoardType)
: bits(initialBits), bitboardtype(initialBitBoardType) {}

int64_t BitBoard::getBits(){
    return bits;
}

bool BitBoard::checkForMergedBitBoard(){ 
    return bitboardtype.color != UNDEFINED_COLOR && bitboardtype.piecetype != UNDEFINED_PIECE;
};

std::vector<std::pair<int,int>> BitBoard::getCoordinateList(){
    std::vector<std::pair<int, int>> coordinates;
    for (int i = 0; i < 64; i++) {
        if (bits & (1LL << i)) {
            int x = i % 8;
            int y = i / 8;
            coordinates.push_back({x, y});
        }
    }
    return coordinates;
};

std::vector<Field> BitBoard::getFieldListWithPiecesOfBitboard(){
    std::vector<Field> fields;
    std::vector<std::pair<int,int>> coordinates = getCoordinateList();
    for (auto coordinate : coordinates)
        fields.push_back(Field(coordinate, Piece(bitboardtype.piecetype, bitboardtype.color)));

    return fields;
};

std::vector<Field> BitBoard::drawBitBoardPieces(sf::RenderWindow &window){
    std::vector<Field> fieldList = getFieldListWithPiecesOfBitboard();
    for (Field field : fieldList)
        field.draw(window);
    return fieldList;
};

void BitBoard::unSetField(Field field){
    int index = field.getIndex();
    int64_t summand = int64_t (std::pow(2, index));
    bits -=summand;  
}

void BitBoard::setField(Field field){
    int index = field.getIndex();
    int64_t summand = int64_t (std::pow(2, index));
    bits +=summand;  
}

void BitBoard::printBitBoard(){
    std::cout << "bits: " << getBits() << " color: " << bitboardtype.color << " piecetype " << bitboardtype.piecetype << std::endl;
}
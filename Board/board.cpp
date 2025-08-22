#include <bitset>
#include <cassert>
#include <vector>
#include "../Pieces/piece.cpp"

class Field{
    private:
        int coordinates[2];
        Piece piece;

    public:
        Field(int initialCoordinates[2], Piece initialPiece) : piece(initialPiece){
            for (int i = 0; i < 2; i++)
                initialCoordinates[i] = coordinates[i];            
        }
};

enum BitBoardType{
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING,
    WHITE,
    BLACK,
};

class BitBoard{
    private:
       int64_t bits;
       BitBoardType bitboardtype;
    public:

        BitBoard(int64_t initialBits, BitBoardType initialBitBoardType) : bits(initialBits), bitboardtype(initialBitBoardType) {}

        void convertToCoordinates(){};

        void display(){};

};

class Board {
    private:
        std::vector<BitBoard> bitboard;
    public:
    Board(std::vector<BitBoard> initialBitboard) : bitboard(initialBitboard) {
     }
};
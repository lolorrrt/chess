#include "field.cpp"

struct BitBoardType{
    PieceType piecetype;
    Color color;
};

#ifndef BITBOARD
#define BITBOARD

class BitBoard{
    private:
       int64_t bits;

    public:
        int64_t getBits();

        BitBoardType bitboardtype;

        BitBoard();
        BitBoard(int64_t initialBits, BitBoardType initialBitBoardType);

        bool checkForMergedBitBoard();

        std::vector<std::pair<int,int>> getCoordinateList();

        std::vector<Field> getFieldListWithPiecesOfBitboard();

        std::vector<Field> drawBitBoardPieces(sf::RenderWindow &window);

        void printBitBoard();

        void unSetField(Field field);

        void setField(Field field);

};

#endif BITBOARD
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
                coordinates[i] = initialCoordinates[i];            
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
    ALLFIELDS
};

class BitBoard{
    private:
       int64_t bits;

    public:

        int64_t getBits(){
            return bits;
        }

        BitBoardType bitboardtype;

        BitBoard() : bits(0), bitboardtype(ALLFIELDS){}
        BitBoard(int64_t initialBits, BitBoardType initialBitBoardType) : bits(initialBits), bitboardtype(initialBitBoardType) {}

        void convertToCoordinates(){};
        void display(){};
};

class Board {
    private:
        BitBoard bitboards[8];

    public:
        Board(BitBoard initialBitboards[8]) {
            for (int i = 0; i < 8; i++)
                bitboards[i] = initialBitboards[i];    
         }

         bool checkBitBoardType(BitBoard bitboard, enum BitBoardType bitboardType){
            return bitboard.bitboardtype == bitboardType;
         }

         int findBitBoardIndexOfBitBoardType(enum BitBoardType bitboardType){
            int index = 0;
            while (checkBitBoardType(bitboards[index], bitboardType))
                index++;  
            return index;
         }
         
         u_int16_t findBitBoardOfSpecificPiece(enum BitBoardType Piece, enum BitBoardType Color){
            int pieceIndex = findBitBoardIndexOfBitBoardType(Piece);
            int colorIndex = findBitBoardIndexOfBitBoardType(Color);
            return bitboards[pieceIndex].getBits() & bitboards[colorIndex].getBits();
         }

         void listOfBlackPawns(){

         }
};

//BitBoard Klasse muss in karthesische Koordinaten umrechnen
//BitBoard muss Field erstellen
//Field Klasse muss Fields anzeigen können
//gemergede BitBoards -> eigene Klasse; irgendwas überlegen 
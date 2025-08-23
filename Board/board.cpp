#include <bitset>
#include <cassert>
#include "../Pieces/piece.cpp"

class Field{
    private:
        std::pair<int,int> coordinates;
        Piece piece;

    public:
        Field(std::pair<int,int> initialCoordinates, Piece initialPiece)
        : coordinates(initialCoordinates), piece(initialPiece){}
};

class BitBoard{
    private:
       int64_t bits;

    public:
        int64_t getBits(){
            return bits;
        }

        PieceType pieceBitboardtype;
        Color colorBitboardtype;

        BitBoard() : bits(0), pieceBitboardtype(PAWN), colorBitboardtype(ALLFIELDS){}
        BitBoard(int64_t initialBits, PieceType initialPieceBitBoardType, Color initialColorBitboardType)
        : bits(initialBits), pieceBitboardtype(initialPieceBitBoardType), colorBitboardtype(initialColorBitboardType)  {}

        bool checkForMergedBitBoard(){ 
            return colorBitboardtype != ALLFIELDS;
        };

        std::vector<std::pair<int,int>> getCoordinateList(){
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

        std::vector<Field> getFieldList(){
            std::vector<Field> fields;
            std::vector<std::pair<int,int>> coordinates = getCoordinateList();
            for (auto coordinate : coordinates){
                fields.push_back(Field(coordinate, Piece(pieceBitboardtype, colorBitboardtype)));
            }
            return fields;
        };
};

class Board {
    private:
        BitBoard bitboards[8];

    public:
        Board(BitBoard initialBitboards[8]) {
            for (int i = 0; i < 8; i++)
                bitboards[i] = initialBitboards[i];    
         }

         bool checkBitBoardPieceType(BitBoard bitboard, enum PieceType bitboardType){
            return bitboard.pieceBitboardtype == bitboardType;
         }

         bool checkBitBoardColorType(BitBoard bitboard, enum Color color){
            return bitboard.colorBitboardtype == color;
         }

         int findBitBoardIndexOfBitBoardPieceType(enum PieceType bitboardType){
            int index = 0;
            while (!checkBitBoardPieceType(bitboards[index], bitboardType))
                index++;  
            return index;
         }
         
        int findBitBoardIndexOfBitBoardColorType(enum Color color){
            int index = 0;
            while (!checkBitBoardColorType(bitboards[index], color))
                index++;  
            return index;
        }

         BitBoard mergeBitBoard(enum PieceType Piece, enum Color color){
            int pieceIndex = findBitBoardIndexOfBitBoardPieceType(Piece);
            int colorIndex = findBitBoardIndexOfBitBoardColorType(color);

            u_int16_t bits = bitboards[pieceIndex].getBits() & bitboards[colorIndex].getBits();
            return BitBoard(bits, Piece, color);
         }
};

//Field Klasse muss Fields anzeigen können 
#include <bitset>
#include <cassert>
#include "../Pieces/piece.cpp"
#include <SFML/Graphics.hpp>
#include <iostream>

class Field{
    private:
        const float squareSize = 100;
        std::pair<int,int> coordinates;
        Piece piece;
        sf::RectangleShape square;

    public:
        Field(std::pair<int,int> initialCoordinates, Piece initialPiece)
        : coordinates(initialCoordinates), piece(initialPiece){

            square.setSize(sf::Vector2f(squareSize, squareSize));
            square.setPosition(coordinates.first * squareSize, coordinates.second * squareSize);
            
            if ((coordinates.first + coordinates.second) % 2 == 1)
                square.setFillColor(sf::Color::White);
            else
                square.setFillColor(sf::Color::Black);
            }
        Piece getPiece(){
            return piece;
        }

        sf::RectangleShape getSquare(){
            return square;
        }
};

struct BitBoardType{
    PieceType piecetype;
    Color color;
};

class BitBoard{
    private:
       int64_t bits;

    public:
        int64_t getBits(){
            return bits;
        }

        BitBoardType bitboardtype;

        BitBoard() : bits(0), bitboardtype(){}
        BitBoard(int64_t initialBits, BitBoardType initialBitBoardType)
        : bits(initialBits), bitboardtype(initialBitBoardType) {}

        bool checkForMergedBitBoard(){ 
            return bitboardtype.color != UNDEFINED_COLOR && bitboardtype.piecetype != UNDEFINED_PIECE;
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
                coordinate.first = coordinate.first * 100;
                coordinate.second = coordinate.second * 100;
                fields.push_back(Field(coordinate, Piece(bitboardtype.piecetype, bitboardtype.color, coordinate)));
            }
            return fields;
        };

        std::vector<Field> drawBitBoardPieces(sf::RenderWindow &window){
            std::vector<Field> fieldList = getFieldList();
            for (Field field : fieldList)
                window.draw(field.getPiece().draw());
            return fieldList;
        };

        void updateChessBoardFieldList(std::vector<Field> chessboardFields){

        }

};

class Board {
    private:
        std::vector<BitBoard> bitboards;

    public:
        Board(std::vector<BitBoard> initialBitboards) : bitboards(initialBitboards) {
               
         }

         bool checkBitBoardPieceType(BitBoard bitboard, enum PieceType bitboardType){
            return bitboard.bitboardtype.piecetype == bitboardType;
         }

         bool checkBitBoardColorType(BitBoard bitboard, enum Color color){
            return bitboard.bitboardtype.color == color;
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

         BitBoard mergeBitBoard(enum PieceType piece, enum Color color){
            int pieceIndex = findBitBoardIndexOfBitBoardPieceType(piece);
            int colorIndex = findBitBoardIndexOfBitBoardColorType(color);
            int64_t bits = bitboards[pieceIndex].getBits() & bitboards[colorIndex].getBits();
            
            return BitBoard(bits, {piece, color});
         }

         BitBoard updateBitboard(BitBoard bitboard, Move move, Piece movedPiece){
            return bitboard; // To be implemented
         }

         bool isMerged(){
            return bitboards.size() > 8;
         }

         Board mergeChessBoard(){
            BitBoard whitePawns = mergeBitBoard(PAWN, WHITE);
            BitBoard blackPawns = mergeBitBoard(PAWN, BLACK);
            BitBoard whiteKnights = mergeBitBoard(KNIGHT, WHITE);
            BitBoard blackKnights = mergeBitBoard(KNIGHT, BLACK);
            BitBoard whiteBishops = mergeBitBoard(BISHOP, WHITE);
            BitBoard blackBishops = mergeBitBoard(BISHOP, BLACK);
            BitBoard whiteRooks = mergeBitBoard(ROOK, WHITE);
            BitBoard blackRooks = mergeBitBoard(ROOK, BLACK);
            BitBoard whiteQueens = mergeBitBoard(QUEEN, WHITE);
            BitBoard blackQueens = mergeBitBoard(QUEEN, BLACK);
            BitBoard whiteKings = mergeBitBoard(KING, WHITE);
            BitBoard blackKings = mergeBitBoard(KING, BLACK);

            std::vector<BitBoard> initialBitBoards = {whitePawns, blackPawns, whiteKnights, blackKnights, whiteBishops, blackBishops, whiteRooks, blackRooks, whiteQueens, blackQueens, whiteKings, blackKings};
            return Board(initialBitBoards);
         }

         void draw(sf::RenderWindow &window){
            if (isMerged())
                for(auto bitboards : bitboards)
                    bitboards.drawBitBoardPieces(window);
            else 
                std::cout << "Bitboards not merged! Cannot be drawn." << std::endl;
            
         }
};

//Field Klasse muss Fields anzeigen können
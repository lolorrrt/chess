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
        sf::Texture pieceTexture;
    public:
        Field() : coordinates({-1,-1}), piece(Piece(UNDEFINED_PIECE, UNDEFINED_COLOR)){
        }

        Field(std::pair<int,int> initialCoordinates, Piece initialPiece)
        : coordinates(initialCoordinates), piece(initialPiece){

            square.setSize(sf::Vector2f(squareSize, squareSize));
            square.setPosition(coordinates.first * squareSize, coordinates.second * squareSize);
            
            if ((coordinates.first + coordinates.second) % 2 == 1)
                square.setFillColor(sf::Color::Blue);
            else
                square.setFillColor(sf::Color::Red);
            }
        Piece getPiece(){
            return piece;
        }

        sf::RectangleShape getSquare(){
            return square;
        }

        int getIndex(){
            return coordinates.second * 8 + coordinates.first;
        }

        sf::Sprite drawPiece(){
            if (piece.getPieceType() == UNDEFINED_PIECE || piece.getColor() == UNDEFINED_COLOR)
                return sf::Sprite();
                
            pieceTexture.loadFromFile("./images/" + std::to_string(piece.getColor()) + std::to_string(piece.getPieceType()) + ".jpeg");
            sf::Sprite pieceSprite;
            pieceSprite.setTexture(pieceTexture);
            pieceSprite.setScale(0.3f, 0.3f); 
            pieceSprite.setPosition(coordinates.first *100+ 15,coordinates.second *100+15);

            return pieceSprite;
        }

        void draw(sf::RenderWindow &window){
            window.draw(square);
            window.draw(drawPiece());
        }

        void undrawPiece(sf::RenderWindow &window){
            window.draw(square);
        }

        bool isOutOfBounds(){
            return coordinates.first < 0 || coordinates.first > 7 || coordinates.second < 0 || coordinates.second > 7;
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

        std::vector<Field> getFieldListWithPiecesOfBitboard(){
            std::vector<Field> fields;
            std::vector<std::pair<int,int>> coordinates = getCoordinateList();
            for (auto coordinate : coordinates){
                fields.push_back(Field(coordinate, Piece(bitboardtype.piecetype, bitboardtype.color)));
            }
            return fields;
        };

        std::vector<Field> drawBitBoardPieces(sf::RenderWindow &window){
            std::vector<Field> fieldList = getFieldListWithPiecesOfBitboard();
            for (Field field : fieldList)
                field.draw(window);
            return fieldList;
        };
};

class Board {
    private:
        std::vector<BitBoard> bitboards;

    public:
        Field selectedField;

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
            return bitboards.size() > 8 || bitboards.size() == 1;
         }

         Board occupiedPartOfBoard(){
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

         Board unoccupiedPartOfBoard(){
            int blackBitboardIndex = findBitBoardIndexOfBitBoardColorType(BLACK);
            int whiteBitboardIndex = findBitBoardIndexOfBitBoardColorType(WHITE);
            BitBoard unoccupiedBitBoard = BitBoard (~(bitboards[blackBitboardIndex].getBits()) & ~(bitboards[whiteBitboardIndex].getBits()), {UNDEFINED_PIECE, UNDEFINED_COLOR});
            std::vector<BitBoard> initialBitBoards = {unoccupiedBitBoard};
            return Board(initialBitBoards);
         }

         std::vector<Field> getOccupiedFields(){
            std::vector<Field> occupiedFields;
            if (isMerged()){
                for(auto bitboards : bitboards){
                    std::vector<Field> updatedFields = bitboards.getFieldListWithPiecesOfBitboard();
                    for (Field field : updatedFields)
                        occupiedFields.push_back(field);
                }
            }      
            else 
                std::cout << "Bitboards not merged! Cannot get occupied fields." << std::endl;
            return occupiedFields;
         }

         std::vector<Field> getUnoccupiedFields(){
            BitBoard unoccupiedBitBoard = unoccupiedPartOfBoard().bitboards[0];
            return unoccupiedBitBoard.getFieldListWithPiecesOfBitboard();
         }

         std::vector<Field> drawOccupiedFields(sf::RenderWindow &window){
            std::vector<Field> occupiedFields;
            if (isMerged()){
                for(auto bitboards : bitboards){
                    std::vector<Field> updatedFields = bitboards.drawBitBoardPieces(window);
                    for (Field field : updatedFields)
                        occupiedFields.push_back(field);
                }
            }      
            else 
                std::cout << "Bitboards not merged! Cannot be drawn." << std::endl;
            return occupiedFields;
            
         }

         void printOccupiedFields(){
            if (isMerged()){
                for(auto bitboards : bitboards){
                    std::vector<Field> updatedFields = bitboards.getFieldListWithPiecesOfBitboard();
                    for (Field field : updatedFields)
                        std::cout << "Piece: " << field.getPiece().getPieceType() << " Color: " << field.getPiece().getColor() << " at Index: " << field.getIndex() << std::endl;
                }
            }      
            else 
                std::cout << "Bitboards not merged! Cannot be printed." << std::endl;
         }

         std::vector<Field> drawUnoccupiedFields(sf::RenderWindow &window){
            return bitboards[0].drawBitBoardPieces(window);
         }

         void printUnoccupiedFields(){
            int blackBitboardIndex = findBitBoardIndexOfBitBoardColorType(BLACK);
            int whiteBitboardIndex = findBitBoardIndexOfBitBoardColorType(WHITE);
            BitBoard unoccupiedBitBoard = unoccupiedPartOfBoard().bitboards[0];
            std::vector<Field> unoccupiedFields = unoccupiedBitBoard.getFieldListWithPiecesOfBitboard();
            for (Field field : unoccupiedFields)
                std::cout << "Unoccupied Field at Index: " << field.getIndex() << std::endl;
         }  
         
         Field firstTargetField(int x, int y){
            std::vector<Field> occupiedFields = getOccupiedFields();
            for (Field field : occupiedFields){
                if (field.getSquare().getGlobalBounds().contains(x,y)){
                    std::cout << "Selected Field at: x: " << x << " y: " << y << " PieceType: " << field.getPiece().getPieceType() << std::endl;
                    //selectedField = field;
                    return field;
                }
                    
            }
            std::cout << "No field found at these coordinates, or empty field! Try again." << std::endl;
            return Field({-1,-1}, Piece(UNDEFINED_PIECE, UNDEFINED_COLOR));
         }

        std::vector<Field> getAllFields(){
            std::vector<Field> allFields;
            Board occupiedBoard = occupiedPartOfBoard();
            Board unoccupiedBoard = unoccupiedPartOfBoard();
            std::vector<Field> occupiedFields = occupiedBoard.getOccupiedFields();
            std::vector<Field> unoccupiedFields = unoccupiedBoard.getUnoccupiedFields();
            for (Field field : occupiedFields)
                allFields.push_back(field);
            for (Field field : unoccupiedFields)
                allFields.push_back(field);
            return allFields;
         }

         Field secondTargetField(int x, int y){
            std::vector<Field> allFields = getAllFields();
            for (Field field : allFields){
                if (field.getSquare().getGlobalBounds().contains(x,y)){
                    std::cout << "Selected Field at: x: " << x << " y: " << y << " PieceType: " << field.getPiece().getPieceType() << std::endl;
                    return field;
                }
                    
            }
            std::cout << "No field found at these coordinates! Try again." << std::endl;
            return Field({-1,-1}, Piece(UNDEFINED_PIECE, UNDEFINED_COLOR));
         }  
};
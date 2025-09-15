#include "board.h"

Board::Board(std::vector<BitBoard> initialBitboards) : bitboards(initialBitboards) {
               
}

bool Board::checkBitBoardPieceType(BitBoard bitboard, enum PieceType bitboardType){
    return bitboard.bitboardtype.piecetype == bitboardType;
}

bool Board::checkBitBoardColorType(BitBoard bitboard, enum Color color){
    return bitboard.bitboardtype.color == color;
}

int Board::findBitBoardIndexOfBitBoardPieceType(enum PieceType bitboardType){
    int index = 0;
    while (!checkBitBoardPieceType(bitboards[index], bitboardType))
        index++;  
    return index;
}
         
int Board::findBitBoardIndexOfBitBoardColorType(enum Color color){
    int index = 0;
    while (!checkBitBoardColorType(bitboards[index], color))
        index++;  
    return index;
}

BitBoard Board::mergeBitBoard(enum PieceType piece, enum Color color){
    int pieceIndex = findBitBoardIndexOfBitBoardPieceType(piece);
    int colorIndex = findBitBoardIndexOfBitBoardColorType(color);
    int64_t bits = bitboards[pieceIndex].getBits() & bitboards[colorIndex].getBits();
            
    return BitBoard(bits, {piece, color});
}

BitBoard Board::updateBitboard(BitBoard bitboard, Move move, Piece movedPiece){
    return bitboard; // To be implemented
    }

bool Board::isMerged(){
    return bitboards.size() > 8 || bitboards.size() == 1;
}

Board Board::occupiedPartOfBoard(){
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

Board Board::unoccupiedPartOfBoard(){
    int blackBitboardIndex = findBitBoardIndexOfBitBoardColorType(BLACK);
    int whiteBitboardIndex = findBitBoardIndexOfBitBoardColorType(WHITE);
    BitBoard unoccupiedBitBoard = BitBoard (~(bitboards[blackBitboardIndex].getBits()) & ~(bitboards[whiteBitboardIndex].getBits()), {UNDEFINED_PIECE, UNDEFINED_COLOR});
    std::vector<BitBoard> initialBitBoards = {unoccupiedBitBoard};
    return Board(initialBitBoards);
}

std::vector<Field> Board::getOccupiedFields(){
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

std::vector<Field> Board::getUnoccupiedFields(){
    BitBoard unoccupiedBitBoard = unoccupiedPartOfBoard().bitboards[0];
    return unoccupiedBitBoard.getFieldListWithPiecesOfBitboard();
}

std::vector<Field> Board::drawOccupiedFields(sf::RenderWindow &window){
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

void Board::printOccupiedFields(){
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

std::vector<Field> Board::drawUnoccupiedFields(sf::RenderWindow &window){
    return bitboards[0].drawBitBoardPieces(window);
}

void Board::printUnoccupiedFields(){
    int blackBitboardIndex = findBitBoardIndexOfBitBoardColorType(BLACK);
    int whiteBitboardIndex = findBitBoardIndexOfBitBoardColorType(WHITE);
    BitBoard unoccupiedBitBoard = unoccupiedPartOfBoard().bitboards[0];
    std::vector<Field> unoccupiedFields = unoccupiedBitBoard.getFieldListWithPiecesOfBitboard();
    for (Field field : unoccupiedFields)
        std::cout << "Unoccupied Field at Index: " << field.getIndex() << std::endl;
}  
         
Field Board::firstTargetField(int x, int y){
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

std::vector<Field> Board::getAllFields(){
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

Field Board::secondTargetField(int x, int y){
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
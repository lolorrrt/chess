#include <SFML/Window/Event.hpp>
#include <iostream>
#include <functional>
#include "Board/board.cpp"

BitBoard blackBitBoard(0xFFFF000000000000, {UNDEFINEDPIECE, BLACK});
BitBoard whiteBitBoard(0x000000000000FFFF, {UNDEFINEDPIECE, WHITE});
BitBoard pawnBitBoard(0x00FF00000000FF00, {PAWN, UNDEFINEDCOLOR});
BitBoard knightBitBoard(0x4200000000000042, {KNIGHT, UNDEFINEDCOLOR});
BitBoard bishopBitBoard(0x2400000000000024, {BISHOP, UNDEFINEDCOLOR});
BitBoard rookBitBoard(0x8100000000000081, {ROOK, UNDEFINEDCOLOR});
BitBoard queenBitBoard(0x0800000000000008, {QUEEN, UNDEFINEDCOLOR});
BitBoard kingBitBoard(0x1000000000000010, {KING, UNDEFINEDCOLOR});

std::vector<Field> chessboardFields;
std::vector<BitBoard> chessboardBitBoards  = {blackBitBoard, whiteBitBoard, pawnBitBoard, knightBitBoard, bishopBitBoard, rookBitBoard, queenBitBoard, kingBitBoard};

void drawChessboard(sf::RenderWindow &window){
    for (int row = 0; row < 8; row++){
        for (int column = 0; column < 8; column++){
            Field field({row, column}, Piece{UNDEFINEDPIECE, UNDEFINEDCOLOR, {row, column}});
            chessboardFields.push_back(field);
            window.draw(field.getSquare());
        }   
    }
};



void drawPieces(sf::RenderWindow &window){ 
    Board chessboard = Board(chessboardBitBoards);

    BitBoard whitePawns = chessboard.mergeBitBoard(PAWN, WHITE);
    BitBoard blackPawns = chessboard.mergeBitBoard(PAWN, BLACK);
    BitBoard whiteKnights = chessboard.mergeBitBoard(KNIGHT, WHITE);
    BitBoard blackKnights = chessboard.mergeBitBoard(KNIGHT, BLACK);
    BitBoard whiteBishops = chessboard.mergeBitBoard(BISHOP, WHITE);
    BitBoard blackBishops = chessboard.mergeBitBoard(BISHOP, BLACK);
    BitBoard whiteRooks = chessboard.mergeBitBoard(ROOK, WHITE);
    BitBoard blackRooks = chessboard.mergeBitBoard(ROOK, BLACK);
    BitBoard whiteQueens = chessboard.mergeBitBoard(QUEEN, WHITE);
    BitBoard blackQueens = chessboard.mergeBitBoard(QUEEN, BLACK);
    BitBoard whiteKings = chessboard.mergeBitBoard(KING, WHITE);
    BitBoard blackKings = chessboard.mergeBitBoard(KING, BLACK);

    std::vector<Field> whitePawnList = whitePawns.drawBitBoardPieces(window);
    std::vector<Field> blackPawnList = blackPawns.drawBitBoardPieces(window);
    std::vector<Field> whiteKnightList = whiteKnights.drawBitBoardPieces(window);
    std::vector<Field> blackKnightList = blackKnights.drawBitBoardPieces(window);
    std::vector<Field> whiteBishopList = whiteBishops.drawBitBoardPieces(window);
    std::vector<Field> blackBishopList = blackBishops.drawBitBoardPieces(window);
    std::vector<Field> whiteRookList = whiteRooks.drawBitBoardPieces(window);
    std::vector<Field> blackRookList = blackRooks.drawBitBoardPieces(window);
    std::vector<Field> whiteQueenList = whiteQueens.drawBitBoardPieces(window);
    std::vector<Field> blackQueenList = blackQueens.drawBitBoardPieces(window);
    std::vector<Field> whiteKingList = whiteKings.drawBitBoardPieces(window);
    std::vector<Field> blackKingList = blackKings.drawBitBoardPieces(window);

}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "Chess");
    window.clear(sf::Color::White);

    drawChessboard(window);
    drawPieces(window);
    window.display();

    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        
        
    }

    return 0;
}

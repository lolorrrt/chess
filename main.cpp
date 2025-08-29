#include <SFML/Window/Event.hpp>
#include <iostream>
#include <functional>
#include "Board/board.cpp"

std::vector<Field> chessboardFields;

void drawChessboard(sf::RenderWindow &window){
    for (int row = 0; row < 8; row++){
        for (int column = 0; column < 8; column++){
            Field field({row, column}, Piece{NOPIECE, NOCOLOR, {row, column}});
            chessboardFields.push_back(field);
            window.draw(field.getSquare());
        }   
    }
};

BitBoard blackBitBoard(0x000000000000FF00, {PAWN, BLACK});
BitBoard whiteBitBoard(0x00FF000000000000, {PAWN, WHITE});
BitBoard knightBitBoard(0x0000000000000042, {KNIGHT, ALLFIELDS});
BitBoard bishopBitBoard(0x0000000000000024, {BISHOP, ALLFIELDS});
BitBoard rookBitBoard(0x0000000000000081, {ROOK, ALLFIELDS});
BitBoard queenBitBoard(0x0000000000000008, {QUEEN, ALLFIELDS});
BitBoard kingBitBoard(0x0000000000000010, {KING, ALLFIELDS});

void drawPieces(sf::RenderWindow &window){
    // Placeholder for drawing pieces
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "Chessboard");
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

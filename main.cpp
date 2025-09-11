#include <SFML/Window/Event.hpp>
#include <iostream>
#include <functional>
#include "Board/board.cpp"
#include <typeinfo>

BitBoard blackBitBoard(0xFFFF000000000000, {UNDEFINED_PIECE, BLACK});
BitBoard whiteBitBoard(0x000000000000FFFF, {UNDEFINED_PIECE, WHITE});
BitBoard pawnBitBoard(0x00FF00000000FF00, {PAWN, UNDEFINED_COLOR});
BitBoard knightBitBoard(0x4200000000000042, {KNIGHT, UNDEFINED_COLOR});
BitBoard bishopBitBoard(0x2400000000000024, {BISHOP, UNDEFINED_COLOR});
BitBoard rookBitBoard(0x8100000000000081, {ROOK, UNDEFINED_COLOR});
BitBoard queenBitBoard(0x0800000000000008, {QUEEN, UNDEFINED_COLOR});
BitBoard kingBitBoard(0x1000000000000010, {KING, UNDEFINED_COLOR});

void drawTextBox(sf::RenderWindow &window){
    sf::RectangleShape textBox;
    textBox.setSize(sf::Vector2f(200, 200));
    textBox.setPosition(800, 0);
    textBox.setFillColor(sf::Color(200, 200, 200));
    window.draw(textBox);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Chess");
    window.clear(sf::Color::White);

    std::vector<BitBoard> chessboardBitBoards  = {blackBitBoard, whiteBitBoard, pawnBitBoard, knightBitBoard, bishopBitBoard, rookBitBoard, queenBitBoard, kingBitBoard};
    Board chessboard = Board(chessboardBitBoards);

    Board mergedChessBoard = chessboard.mergeChessBoard();
    drawTextBox(window);
    
    std::vector<Field> occupiedFieldList = mergedChessBoard.drawOccupiedFields(window);
    chessboard.drawUnoccupiedFields(window);
    
    //Field field = Field({7,7}, Piece(PAWN, BLACK));
    //field.draw(window);
    window.display();

    sf::Event userInput;
    userInput.type = sf::Event::TextEntered;
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            std::cout << "select Field" << std::endl;
            }if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2 mousePosition = sf::Mouse::getPosition(window);
                //Field selectedField = chessboardFields[0];
                std::cout << mousePosition.x << std::endl;
                std::cout << mousePosition.y << std::endl;
                //Piece selectedPiece = selectedField.getPiece();
                //std::cout << "Selected piece: " << selectedPiece.getPieceType() << "at: " << std::endl;
                //std::cout << selectedPiece.getCurrentPosition().first << std::endl;
                //std::cout << selectedPiece.getCurrentPosition().second << std::endl;
            }
            
            
        }
        
        
    }

    return 0;
}

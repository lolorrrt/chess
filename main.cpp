#include <SFML/Window/Event.hpp>
#include <iostream>
#include <functional>
#include "Board/Move.cpp"
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
    sf::RenderWindow window(sf::VideoMode(800, 800), "Chess");
    window.clear(sf::Color::White);

    std::vector<BitBoard> chessboardBitBoards  = {blackBitBoard, whiteBitBoard, pawnBitBoard, knightBitBoard, bishopBitBoard, rookBitBoard, queenBitBoard, kingBitBoard};
    Board chessboard = Board(chessboardBitBoards);

    Board occupiedChessBoard = chessboard.occupiedPartOfBoard();
    Board unoccupiedChessBoard = chessboard.unoccupiedPartOfBoard();

    std::vector<Field> occupiedFieldList = occupiedChessBoard.drawOccupiedFields(window);
    std::vector<Field> unoccupiedFieldList = unoccupiedChessBoard.drawUnoccupiedFields(window);
    
    window.display();

    Field moveOriginField;
    Field moveTargetField;
    Move testMove;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }if (event.type == sf::Event::MouseButtonPressed)
            {   
                sf::Vector2 mousePosition = sf::Mouse::getPosition(window);
                
                if(moveOriginField.isNotInitialized()){
                    std::cout << "select origin" << std::endl;
                    moveOriginField = occupiedChessBoard.getMoveOrigin(mousePosition.x, mousePosition.y); 
                }   
                else{
                    std::cout << "select target" << std::endl;
                    moveTargetField = chessboard.getMoveTarget(mousePosition.x, mousePosition.y);
                    testMove = Move(moveOriginField, moveTargetField);
                    moveOriginField.reset();
                    moveTargetField.reset();
                    testMove.execute(window, chessboard);

                    window.display();
                }
                
            }      
        }
    }

    return 0;
}

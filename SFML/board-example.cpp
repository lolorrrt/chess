#include <SFML/Graphics.hpp>

int main() {
    // Create a window (800x800 pixels, with a title "Chessboard")
    sf::RenderWindow window(sf::VideoMode(800, 800), "Chessboard");

    // Define the size of the squares (each square is 100x100 pixels)
    int squareSize = 100;

    // Chessboard loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Clear the window with a white color (background)
        window.clear(sf::Color::White);

        // Draw the chessboard (8x8 grid)
        for (int row = 0; row < 8; ++row) {
            for (int col = 0; col < 8; ++col) {
                // Create a rectangle for each square
                sf::RectangleShape square(sf::Vector2f(squareSize, squareSize));

                // Set the position of the square (top-left corner)
                square.setPosition(col * squareSize, row * squareSize);

                // Alternate colors for the squares (black and white)
                if ((row + col) % 2 == 1) {
                    square.setFillColor(sf::Color::White); // White squares
                } else {
                    square.setFillColor(sf::Color::Black); // Black squares
                }

                // Draw the square
                window.draw(square);
            }
        }

        // Display the contents of the window
        window.display();
    }

    return 0;
}

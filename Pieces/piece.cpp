#include <vector>
#include <SFML/Graphics.hpp>
enum PieceType{
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING,
    UNDEFINEDPIECE
};

enum Color{
    WHITE,
    BLACK,
    UNDEFINEDCOLOR
};

class Move{
    private:
        std::pair<int,int> movementVector;

    public:
        Move(std::pair<int,int> initialMovementVector) : movementVector(initialMovementVector) {
        }
    
        int getComponentX(){
            return movementVector.first;
        }

        int getComponentY(){
            return movementVector.second;
        }
};

class Piece{
    private:
        PieceType piecetype;
        Color color;
        std::pair<int,int>position;

        sf::Texture pieceTexture;
        public:
            Piece(PieceType initialPiecetype, Color initialColor, std::pair<int,int>initialPosition)
            : piecetype(initialPiecetype), color(initialColor), position(initialPosition){ 
                if (color == UNDEFINEDCOLOR || piecetype == UNDEFINEDPIECE){
                    return;
                }
                pieceTexture.loadFromFile("./images/" + std::to_string(color) + std::to_string(piecetype) + ".jpeg");
            }

            std::pair<int,int> getCurrentPosition(){
                return position;
            }

            std::pair<int,int> setNewPosition(Move move){
                position.first += move.getComponentX();
                position.second += move.getComponentY();
                return position;
            }

            sf::Sprite draw(){
                sf::Sprite pieceSprite;
                pieceSprite.setTexture(pieceTexture);
                pieceSprite.setScale(0.3f, 0.3f); 
                pieceSprite.setPosition(position.first + 15,position.second +15);

                return pieceSprite;
            }
};
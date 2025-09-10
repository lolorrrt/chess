#include <vector>
#include <SFML/Graphics.hpp>
enum PieceType{
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING,
    UNDEFINED_PIECE
};

enum Color{
    WHITE,
    BLACK,
    UNDEFINED_COLOR
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

        public:
            Piece(PieceType initialPiecetype, Color initialColor)
            : piecetype(initialPiecetype), color(initialColor){ 
            }

            PieceType getPieceType(){
                return piecetype;
            }

            Color getColor(){
                return color;
            }
};
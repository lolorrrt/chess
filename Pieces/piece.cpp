#include <vector>

enum PieceType{
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING,
    NOPIECE
};

enum Color{
    WHITE,
    BLACK,
    NOCOLOR,
    ALLFIELDS
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

        public:
            Piece(PieceType initialPiecetype, Color initialColor, std::pair<int,int>initialPosition)
            : piecetype(initialPiecetype), color(initialColor), position(initialPosition){  
            }

            std::pair<int,int> getCurrentPosition(){
                return position;
            }

            std::pair<int,int> setNewPosition(Move move){
                position.first += move.getComponentX();
                position.second += move.getComponentY();
                return position;
            }
};
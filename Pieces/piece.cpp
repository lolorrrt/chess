#include <vector>

enum PieceType{
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
};

enum Color{
    WHITE,
    BLACK
};

enum CoordinateAxle{
    X,
    Y
};

enum MoveDirection{
    POSITIV = 1,
    NEGATIVE = -1
};

class Move{
    private:
        int absoluteValueMotion[2];
        MoveDirection directions[2];

    public:
        Move(int initialMove[2], MoveDirection initialdirections[2]) {
            for (int i = 0; i < 2; i++) {
                this->absoluteValueMotion[i] = initialMove[i];
                this->directions[i] = initialdirections[i];
            }
        }


};

class Piece{
    private:
        PieceType piecetype;
        Color color;
        int position[2]; 

        public:
            Piece(PieceType initialPiecetype, Color initialColor, int initialPosition[2]) : piecetype(initialPiecetype), color(initialColor){
                for (int i = 0; i < 2; i++)
                position[i] = initialPosition[i];   
            }

            bool checkMove(Move testMove){
                return false;
            }

            void updatePosition(){

            }

            void executeMove(){

            }
          
};
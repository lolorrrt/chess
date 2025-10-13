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
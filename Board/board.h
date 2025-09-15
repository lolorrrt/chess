#include "bitboard.cpp"

class Board {
    private:
        std::vector<BitBoard> bitboards;

    public:
        Field selectedField;

        Board(std::vector<BitBoard> initialBitboards);

        bool checkBitBoardPieceType(BitBoard bitboard, enum PieceType bitboardType);

        bool checkBitBoardColorType(BitBoard bitboard, enum Color color);

        int findBitBoardIndexOfBitBoardPieceType(enum PieceType bitboardType);
         
        int findBitBoardIndexOfBitBoardColorType(enum Color color);

        BitBoard mergeBitBoard(enum PieceType piece, enum Color color);

        BitBoard updateBitboard(BitBoard bitboard, Move move, Piece movedPiece);

        bool isMerged();

        Board occupiedPartOfBoard();

        Board unoccupiedPartOfBoard();

        std::vector<Field> getOccupiedFields();

        std::vector<Field> getUnoccupiedFields();

        std::vector<Field> drawOccupiedFields(sf::RenderWindow &window);

        void printOccupiedFields();

        std::vector<Field> drawUnoccupiedFields(sf::RenderWindow &window);

        void printUnoccupiedFields();
         
        Field firstTargetField(int x, int y);

        std::vector<Field> getAllFields();

        Field secondTargetField(int x, int y);  
};
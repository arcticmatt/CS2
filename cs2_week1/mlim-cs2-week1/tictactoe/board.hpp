/**
 * @brief: A two-dimensional board.
 */

class Board
{
    private:
        const int UNOCCUPIED = 0;
        const int X_OCC = 1;
        const int O_OCC = 2;
        int cols; /** Columns **/
        int rows; /** Rows **/
        int **board;
    public:
        Board();                               // Constructor
        Board(int board_rows, int board_cols); // Constructor
        ~Board();                              // Destructor
        int Query(int row, int col);
        void Place(int row, int col, char type);
        int CheckWin();
        int CheckDraw();
        void Print(int row, int col);
};



/**
 * @brief: A two-dimensional board.
 */
#include <stdio.h>
#include <string.h>
#include "board.hpp"

const int DEFAULT_ROWS = 3;
const int DEFAULT_COLS = 3;

/**
 * @brief: Makes a standard 3x3 tic-tac-toe board
 */
Board::Board()
{
    cols = DEFAULT_COLS;
    rows = DEFAULT_ROWS;

    /* Create a 3 x 3 2d array */
    board = new int*[DEFAULT_ROWS];
    for (int i = 0; i < DEFAULT_ROWS; i++)
    {
        board[i] = new int[DEFAULT_COLS];
    }

    /* Initializes all the spaces as unoccupied */
    for (int i = 0; i < DEFAULT_ROWS; i++)
    {
        for (int j = 0; i < DEFAULT_COLS; i++)
        {
            board[i][j] = UNOCCUPIED;
        }
    }
}

/**
 * @brief: Makes a board of x columns and y rows.
 *
 * @param board_rows: The number of columns.
 * @param board_cols: The number of rows.
 */
Board::Board(int board_rows, int board_cols)
{
    cols = board_rows;
    rows = board_cols;

    /* Creates a rows x cols 2d array */
    board = new int*[rows];
    for (int i = 0; i < rows; i++)
    {
        board[i] = new int[cols];
    }

    /* Initializes all the spaces as unoccupied */
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; i < cols; i++)
        {
            board[i][j] = UNOCCUPIED;
        }
    }
}

/**
 * @brief: Destructor that deletes the two dimensional board array.
 */
Board::~Board()
{
    for (int i = 0; i < 3; i++)
    {
        delete[] board[i];
    }
    delete[] board;
}

/**
 * @brief: Given board coordinates, return a square state.
 *
 * @param row: Row coordinate.
 * @param col: Column coordinate.
 *
 * @return: The state of the board coordinate.
 */
int Board::Query(int row, int col)
{
    return board[row][col];
}

/**
 * @brief: Places a piece of type type on the board.
 * The type must be either "X" or "O". If not, the board
 * remains unchanged.
 *
 * @param row: Row coordinate.
 * @param col: Column coordinate.
 */
void Board::Place(int row, int col, char type)
{
    if (type == 'X')
    {
        board[row][col] = X_OCC;
    }
    else if (type == 'O')
    {
        board[row][col] = O_OCC;
    }
}

/**
 * @brief: Checks whether the board is in a winning state,
 * and returns the player that won (if any). Only works
 * for 3 x 3 boards.
 *
 * @return: The player that won (if any).
 */
int Board::CheckWin()
{
    // States of top row
    int top_left = board[0][0];
    int top_mid = board[0][1];
    int top_right = board[0][2];

    // States of middle row
    int mid_left = board[1][0];
    int mid_mid = board[1][1];
    int mid_right = board[1][2];

    // States of bottom row
    int bottom_left = board[2][0];
    int bottom_mid = board[2][1];
    int bottom_right = board[2][2];

    if ((top_left == X_OCC && top_mid == X_OCC && top_right == X_OCC)
            || (mid_left == X_OCC && mid_mid == X_OCC && mid_right == X_OCC)
            || (bottom_left == X_OCC && bottom_mid == X_OCC
            && bottom_right == X_OCC)
            || (top_left == X_OCC && mid_left == X_OCC && bottom_left == X_OCC)
            || (top_mid == X_OCC && mid_mid == X_OCC && bottom_mid == X_OCC)
            || (top_right == X_OCC && mid_right == X_OCC
            && bottom_right == X_OCC)
            || (top_left == X_OCC && mid_mid == X_OCC && bottom_right == X_OCC)
            || (top_right == X_OCC && mid_mid == X_OCC && bottom_left == X_OCC))
    {
        // Check if player "X" has won
        return 1; // Player 1 is X
    }
    else if ((top_left == O_OCC && top_mid == O_OCC && top_right == O_OCC)
            || (mid_left == O_OCC && mid_mid == O_OCC && mid_right == O_OCC)
            || (bottom_left == O_OCC && bottom_mid == O_OCC
            && bottom_right == O_OCC)
            || (top_left == O_OCC && mid_left == O_OCC && bottom_left == O_OCC)
            || (top_mid == O_OCC && mid_mid == O_OCC && bottom_mid == O_OCC)
            || (top_right == O_OCC && mid_right == O_OCC
            && bottom_right == O_OCC)
            || (top_left == O_OCC && mid_mid == O_OCC && bottom_right == O_OCC)
            || (top_right == O_OCC && mid_mid == O_OCC && bottom_left == O_OCC))
    {
        // Check if player "Y" has won
        return 2; //Player 2 is O
    }
    return 0;     // Nobody has won
}

/**
 * @brief: Checks to see if there is a draw. Does this by checking if the
 * board is fully occupied and there is no winning player.
 *
 * @return: Returns 0 if there is no draw and 1 is there is a draw.
 */
int Board::CheckDraw()
{
    // Check if board is full
    int full_board = 1;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (board[i][j] == UNOCCUPIED)
            {
                full_board = 0;
            }
        }
    }

    if (full_board && !CheckWin())
    {
        return 1;
    }
    return 0;
}

/**
 * @brief: Used for debugging. Prints out the piece at a position
 * of the board.
 *
 * @param row: The row from which we will print.
 * @param col: The column from which we will print.
 */
void Board::Print(int row, int col)
{
    printf("%d\n", board[row][col]);
}


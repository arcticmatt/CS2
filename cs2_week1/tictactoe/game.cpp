/**
 * @brief: Class that holds the game state (the board,
 * whose turn it is, etc.)
 */
#include <stdio.h>
#include "game.hpp"

/**
 * @brief: No need to initalize anything (board already initalized in
 * game.hpp
 */
Game::Game()
{
}

/**
 * @brief: Destructor. Nothing needs to be deleted so this is empty.
 */
Game::~Game()
{
}

/**
 * @brief: Runs the game until someone wins or there is a draw.
 */
void Game::Run()
{
    int row = 0;
    int col = 0;
    int player = 1;
    // Runs the game until someone wins or there is a draw
    while (!(board.CheckWin() || board.CheckDraw()))
    {
        printf("Player %d ~ Enter row (1 - 3): \n", player);
        scanf("%d", &row);
        printf("Player %d ~ Enter column (1 - 3): \n", player);
        scanf("%d", &col);
        if (player == 1)
        {
            board.Place(row - 1, col - 1, 'X');
            player = 2;
        }
        else
        {
            board.Place(row - 1, col - 1, 'O');
            player = 1;
        }
    }

    if (board.CheckDraw())
    {
        printf("Draw. Boring.\n");
    }
    else
    {
        printf("Player %d has won!\n", board.CheckWin());
    }
}



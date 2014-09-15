/**
 * @brief: Class that holds the game state (the board,
 * whose turn it is, etc.)
 */
#include "board.hpp"

class Game
{
    private:
        Board board;
    public:
        Game();  // Constructor
        ~Game(); // Destructor
        void Run();
};


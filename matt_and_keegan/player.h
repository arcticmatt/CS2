#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.h"
#include "board.h"
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();

    Move *doMoveHeuristic(Move *opponentsMove, int msLeft);
    Move *doMove(Move *opponentsMove, int msLeft);
    Move *doAIMove();
    Move *doStupidAIMove();
    Move * AIMove(Move * opponentsMove, int msLeft);
    int score(Board * b, Side side);
    int stupidScore(Board * b, Side side);
    Side p_side;
    Side o_side;

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
    Board *board;
};

#endif

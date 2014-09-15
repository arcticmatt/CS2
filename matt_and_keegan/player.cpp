#include "player.h"

/* Vals array is from the paper A genetic algorithm to improve an Othello
 * program by Jean-Marc Alliot, Nicolas Durand
 * URL: http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.16.1218&rep=rep1&type=pdf
 * */
    int vals[8][8] = { {500 , -150 , 30 , 10 , 10 , 30 , -150 , 500},
    {-150 , -250 , 0 , 0 , 0 , 0 , -250 , -150},
    {30 , 0 , 1 , 2 , 2 , 1 , 0 , 30},
    {10 , 0 , 2 , 16 , 16 , 2 , 0 , 10},
    {10 , 0 , 2 , 16 , 16 , 2 , 0 , 10},
    {30 , 0 , 1 , 2 , 2 , 1 , 0 , 30},
    {-150 , -250 , 0 , 0 , 0 , 0 , -250 , -150},
    {500 , -150 , 30 , 10 , 10 , 30 , -150 , 500} };

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    p_side = side;
    if (side == WHITE)
        o_side = BLACK;
    else
        o_side = WHITE;
    board = new Board();
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}


/*
 * Calculate the score of the board for a side, taking into account
 * the heuristic values of the board.
 */
int Player::score(Board * b, Side side)
{
    int sum = 0;
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(b->occupied(i, j))
            {
                if(b->get(side, i, j))
                    sum += vals[i][j];
                else
                    sum -= vals[i][j];
            }
        }
    }
    return sum;
}

/*
 * Do Minimax move (either 2 depth or depth 5, depending on whether
 * testingMinMax is true or false.
 */
Move * Player::doMove(Move * opponentsMove, int msLeft)
{
    board->doMove(opponentsMove, o_side);
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            vals[i][j]++;
    int score0  = -100000;
    int s0 = 0;
    int final_i = -1;
    int final_j = -1;
    bool level6 = false;
    Move *return_m = NULL;
    for (int i0 = 0; i0 < 8; i0++)
    {
        for (int j0 = 0; j0 < 8; j0++)
        {
            Move *m0 = new Move(i0, j0);
            if (board->checkMove(m0, p_side))
            {
                Board *b = board->copy();
                b->doMove(m0, p_side);
                int score = -100000;
                int s = 0;
                for(int i = 0; i < 8; i++)
                {
                    for(int j = 0; j < 8; j++)
                    {
                        Move *m =  new Move(i,j);
                        if(b->checkMove(m, o_side))
                        {
                            Board *b1 = b->copy();
                            b1->doMove(m, o_side);
                            int score1  = -100000;
                            int s1 = 0;
                            for(int i1 = 0; i1 < 8; i1++)
                            {
                                for(int j1 = 0; j1 < 8; j1++)
                                {
                                    Move *m1 =  new Move(i1, j1);
                                    if(b1->checkMove(m1, p_side))
                                    {
                                        Board *b2 = b1->copy();
                                        b2->doMove(m1, p_side);
                                        int score2  = -100000;
                                        int s2 = 0;
                                        for(int i2 = 0; i2 < 8; i2++)
                                        {
                                            for(int j2 = 0; j2 < 8; j2++)
                                            {
                                                Move *m2 =  new Move(i2, j2);
                                                if(b2->checkMove(m2, o_side))
                                                {
                                                    Board *b3 = b2->copy();
                                                    b3->doMove(m2, o_side);
                                                    int score3  = -100000;
                                                    int s3 = 0;
                                                    for(int i3 = 0; i3 < 8; i3++)
                                                    {
                                                        for(int j3 = 0; j3 < 8; j3++)
                                                        {
                                                            Move *m3 =  new Move(i3, j3);
                                                            if(b3->checkMove(m3, p_side))
                                                            {
                                                                Board *b4 = b3->copy();
                                                                b4->doMove(m3, p_side);
                                                                int score4 = -100000;
                                                                int s4 = 0;
                                                                for(int i4 = 0; i4 < 8; i4++)
                                                                {
                                                                    for(int j4 = 0; j4 < 8; j4++)
                                                                    {
                                                                        Move *m4 = new Move(i4, j4);
                                                                        if(b4->checkMove(m4, o_side))
                                                                        {
                                                                            Board *b5 = b4->copy();
                                                                            b5->doMove(m4, o_side);
                                                                            if(level6)
                                                                            {
                                                                                int score5 = -100000;
                                                                                int s5 = 0;
                                                                                for(int i5 = 0; i5 < 8; i5++)
                                                                                {
                                                                                    for(int j5 = 0; j5 < 8; j5++)
                                                                                    {
                                                                                        Move *m5 = new Move(i5, j5);
                                                                                        if(b5->checkMove(m5, p_side))
                                                                                        {
                                                                                            Board *b6 = b5->copy();
                                                                                            b6->doMove(m5, p_side);
                                                                                            s5 = this->score(b6, p_side);
                                                                                            if(s5 > score5)
                                                                                            {
                                                                                                score5 = s5;
                                                                                            }
                                                                                            delete b6;
                                                                                        }
                                                                                        delete m5;
                                                                                    }
                                                                                }
                                                                                s4 = -score5;
                                                                                if(s5 > score5)
                                                                                {
                                                                                    s4 = 10000 + this->score(b5, o_side);
                                                                                }
                                                                            }
                                                                            else
                                                                            {
                                                                                s4 = this->score(b5, o_side);
                                                                            }
                                                                            if(s4 > score4)
                                                                            {
                                                                                score4 = s4;
                                                                            }
                                                                            delete b5;
                                                                        }
                                                                        delete m4;
                                                                    }
                                                                }
                                                                s3 = -score4;
                                                                if(s4 > score4)
                                                                {
                                                                    s3 = 10000 + this->score(b4, p_side);
                                                                }
                                                                if (s3 > score3)
                                                                {
                                                                    score3 = s3;
                                                                }
                                                                delete b4;
                                                            }
                                                            delete m3;
                                                        }
                                                    }
                                                    s2 = -score3;
                                                    if(s3 > score3)
                                                    {
                                                        s2 = 10000 + this->score(b3, o_side);
                                                    }
                                                    if (s2 > score2)
                                                    {
                                                        score2 = s2;
                                                    }
                                                    delete b3;
                                                }
                                                delete m2;
                                            }
                                        }
                                        s1 = -score2;
                                        if(s2 > score2)
                                        {
                                            s1 = 10000 + this->score(b2, p_side);
                                        }
                                        if (s1 > score1)
                                        {
                                            score1 = s1;
                                        }
                                        delete b2;
                                    }
                                    delete m1;
                                }
                            }
                            s = -score1;
                            if(s1 > score1)
                            {
                                s = 10000 + this->score(b1, o_side);
                            }
                            if (s > score)
                            {
                                score = s;
                            }
                            delete b1;
                        }
                        delete m;
                    }
                }
                s0 = -score;
                if(s > score)
                {
                    s0 = 10000 + this->score(b, p_side);
                }
                if (s0 > score0)
                {
                    score0 = s0;
                    final_i = i0;
                    final_j = j0;
                }
                delete b;
            }
            delete m0;
        }
    }
    if (final_i != -1 && final_j != -1)
        return_m = new Move(final_i, final_j);
    board->doMove(return_m, p_side);
    return return_m;
}


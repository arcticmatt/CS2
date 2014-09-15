#ifndef __BOARD_H__
#define __BOARD_H__

#include <bitset>
#include "common.h"
using namespace std;

class Board {

private:
    bitset<64> black;
    bitset<64> taken;

    public:
    Board();
    ~Board();
    Board *copy();

    bool isDone();
    bool hasMoves(Side side);
    bool checkMove(Move *m, Side side);
    void doMove(Move *m, Side side);
    int count(Side side);
    int count();
    int countBlack();
    int countWhite();
    bool occupied(int x, int y);
    bool get(Side side, int x, int y);
    void set(Side side, int x, int y);
    bool onBoard(int x, int y);
    void setBoard(char data[]);
};

#endif

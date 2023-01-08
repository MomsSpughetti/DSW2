#ifndef _PX
#define _PX

#include "../wet2util.h"

//should not be named permutation (it has also gamesPlayed!)
//but there is no time

class PlayerExtra
{

public:
    PlayerExtra() : permutation(permutation_t::neutral()), gamesPlayed(0) {}
    PlayerExtra(const permutation_t& permutation) : permutation(permutation), gamesPlayed(0){}
    PlayerExtra(const permutation_t& permutation, int gamesPlayed) : permutation(permutation), gamesPlayed(gamesPlayed) {}
    friend PlayerExtra operator+(const PlayerExtra& obj1, const PlayerExtra& obj2);
    PlayerExtra& operator+=(const PlayerExtra& obj);
    friend PlayerExtra operator-(const PlayerExtra& obj1, const PlayerExtra& obj2);
    PlayerExtra& operator-=(const PlayerExtra& obj);
    void extraCalc(PlayerExtra& permutation);
    void increaseGamesPlayed(int val);

    permutation_t permutation;
    int gamesPlayed;

};


#endif
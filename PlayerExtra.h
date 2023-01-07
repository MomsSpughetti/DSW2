#include "wet2util.h"

//should not be names permutation (it has also gamesPlayed!)
//but there is no time

class PlayerExtra
{

public:
    PlayerExtra() : permutation(permutation_t::neutral()) {}
    PlayerExtra(const permutation_t& permutation) : permutation(permutation), gamesPlayed(0){}
    PlayerExtra(const permutation_t& permutation, int gamesPlayed) : permutation(permutation), gamesPlayed(gamesPlayed) {}
    friend PlayerExtra operator+(const PlayerExtra& obj1, const PlayerExtra& obj2);
    PlayerExtra& operator+=(const PlayerExtra& obj);
    friend PlayerExtra operator-(const PlayerExtra& obj1, const PlayerExtra& obj2);
    PlayerExtra& operator-=(const PlayerExtra& obj);
    void extraCalc(PlayerExtra&& permutation);
    void increaseGamesPlayed(int val);

    permutation_t permutation;
    int gamesPlayed;

};


PlayerExtra& PlayerExtra::operator+=(const PlayerExtra& obj)
{
    this->permutation = this->permutation * obj.permutation;
    this->gamesPlayed = this->gamesPlayed + obj.gamesPlayed;
    return *this;
}

PlayerExtra operator+(const PlayerExtra& obj1, const PlayerExtra& obj2)
{
    PlayerExtra temp;
    temp += obj1;
    temp += obj2;
    return temp;
}

PlayerExtra& PlayerExtra::operator-=(const PlayerExtra& obj)
{
    this->permutation = obj.permutation.inv() * this->permutation;
    this->gamesPlayed = this->gamesPlayed - obj.gamesPlayed;
    return *this;

}

PlayerExtra operator-(const PlayerExtra& obj1, const PlayerExtra& obj2)
{
    PlayerExtra temp;
    temp -= obj1;
    temp -= obj2;
    return temp;
}

void PlayerExtra::extraCalc(PlayerExtra&& permutation)
{
    this->gamesPlayed -= permutation.gamesPlayed;
}

void PlayerExtra::increaseGamesPlayed(int val)
{
    this->gamesPlayed += val;
}


#include "PlayerExtra.h"

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
    temp += obj1;
    temp -= obj2;
    return temp;
}

void PlayerExtra::extraCalc(PlayerExtra& permutation_)
{
    this->gamesPlayed -= permutation_.gamesPlayed;
    if(permutation_.player_)
    this->permutation = this->permutation * permutation_.permutation.inv();
}

PlayerExtra PlayerExtra::operator% (PlayerExtra& permutation_)
{
    PlayerExtra temp = *this;
    temp.permutation = temp.permutation * permutation_.permutation.inv();
    temp.gamesPlayed -= permutation_.gamesPlayed;
    return temp;
}
void PlayerExtra::increaseGamesPlayed(int val)
{
    this->gamesPlayed += val;
}

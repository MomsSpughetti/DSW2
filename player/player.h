#ifndef _player
#define _player


#include<RankedAvlTree.h>
#include<wet2util.h>
#include<team.h>

class player
{

private:
    int Id;
    int Cards;
    int GamesPlayed;
    int teamPlayedGamesCount;
    int Ability;
    bool GK;
    permutation_t Spirit;

public:
    player(int playerId, int teamId, const permutation_t &spirit, int gamesPlayed,int ability, int cards, bool goalKeeper):
    Id(playerId),Cards(cards),GamesPlayed(gamesPlayed),GK(goalKeeper),Ability(ability),
    Spirit(spirit),teamPlayedGamesCount(0){}
    ~player() = default;

    player(const player& ob)=default;
    void addcards(int x); 
    int getid();
    int getcards();
    int getgamesplayed();
    int getability();
    permutation_t getspirit();
    void setcards(int x);
    void setability(int x);

};


#endif
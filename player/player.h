#ifndef _player
#define _player


#include "../Structures/RankedAVLTree.h"
#include "../wet2util.h"
#include "../team/team.h"

class player
{

private:
    int Id;
    int Cards;
    int GamesPlayed;
    bool GK;
    int Ability;
    permutation_t Spirit;
    int teamPlayedGamesCount;
    int gamesforteams;


    team* team_;

public:
    player(int playerId, int teamId, const permutation_t &spirit, int gamesPlayed,int ability, int cards, bool goalKeeper):
    Id(playerId),
    Cards(cards),
    GamesPlayed(gamesPlayed),
    GK(goalKeeper),
    Ability(ability),
    Spirit(spirit),
    teamPlayedGamesCount(0){}
    ~player() = default;

    player(const player& ob)=default;
    void addcards(int x); 
    int getid();
    int getcards();
    int getgamesplayed();
    int getability();
    bool get_goalKeeper() const;
    permutation_t getspirit();
    void setcards(int x);
    void setability(int x);
    int getgamesforteams();


    team* get_team() const;
    void set_team(team* val);

};


#endif
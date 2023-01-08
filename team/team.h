#include <iostream>
#include <stdlib.h>
#include "wet2util.h"

class team
{
private:
    int teamId;
    bool eliminated;
    bool goalKeeper;
    int points;
    int abilities;
    int num_played_games;
    int IdOfLastPlayer;
    
    permutation_t spirit;


public:
    explicit team(int id) : 
    teamId(id), 
    eliminated(false), 
    goalKeeper(false), 
    points(0), 
    abilities(0), 
    num_played_games(0),
    IdOfLastPlayer(0),
    spirit(permutation_t::neutral()) {};
    
    ~team() = default;

    //gets a & sets

    int get_teamId() const;
    bool get_eleminated() const;
    bool get_goalKeeper() const;
    int get_points() const;
    int get_abilities() const;
    int get_num_played_games() const;
    int get_IdOfLastPlayer() const;
    permutation_t& get_permutation();

    void set_teamId(int val);
    void set_eleminated(bool val);
    void set_goalKeeper(bool val);
    void set_points(int val);
    void set_abilities(int val);
    void set_num_played_games(int val);
    void set_IdOfLastPlayer(int val);
    void set_permutation(const permutation_t&);

    //operators
    bool operator<(const team& obj) const;
    bool operator>(const team& obj) const;
    bool operator==(const team& obj) const;

    //Abo Ghanem additions

    void set_winpoints();

    void increasebyone();

    void increasegamesplayed();

    int get_permstrength() const;
};


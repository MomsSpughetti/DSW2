#include "player.h"


    int player::getid()
        {
            return this->Id;
        }
    int player::getability()
        {
            return this->Ability;
        }
    int player::getgamesplayed()
        {
            return this->GamesPlayed;
        } 
    int player::getcards()
        {
            return this->Cards;
        }          
    permutation_t player::getspirit()
        {
            return this->Spirit;
        }
    void player::addcards(int cards)
    {
        this->Cards+=cards;
    }  

    void player::setability(int ab)
    {
        this->Ability=ab;
    }

    void player::setcards(int cards)
    {
        this->Cards=cards;
    }
    int player::getgamesforteams()
    {
        return gamesforteams;
    }

    team* player::get_team() const
    {
        return this->team_;
    }
    void player::set_team(team* val)
    {
        this->team_ = val;
    }

    bool player::get_goalKeeper() const
    {
        return this->GK;
    }
    #include "team.h"

    int team::get_teamId() const
    {
        return this->teamId;
    }
    bool team::get_eleminated() const
    {
        return this->eliminated;
    }
    bool team::get_goalKeeper() const
    {
        return this->goalKeeper;
    }
    int team::get_points() const
    {
        return this->points;
    }
    int team::get_abilities() const
    {
        return this->abilities;
    }
    int team::get_num_played_games() const
    {
        return this->num_played_games;
    }
    permutation_t& team::get_permutation()
    {
        return this->permutation;
    }

    void team::set_teamId(int val)
    {
        this->teamId = val;
    }
    void team::set_winpoints()
    {
        this->points +=3;
    }
    int team::get_permstrength()const
    {
      return this->permutation.strength();
    }
    void team::increasebyone()
    {
        this->points+=1;
    }
    void team::increasegamesplayed()
    {
        this->num_played_games+=1;
    }
    void team::set_eleminated(bool val)
    {
        this->eliminated = val;
    }
    void team::set_goalKeeper(bool val)
    {
        this->goalKeeper = val;
    }
    void team::set_points(int val)
    {
        this->points = val;
    }
    void team::set_abilities(int val)
    {
        this->abilities = val;
    }
    void team::set_num_played_games(int val)
    {
        this->num_played_games = val;
    }
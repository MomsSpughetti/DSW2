#include <stdlib.h>
#include <iostream>
#include "wet2util.h"
#include "team/team.h"

#ifndef _p
#define _p

class player
{
    public:
    team* get_team() const;
    void set_team(team* val);
    private:
    team* team;
};

#endif
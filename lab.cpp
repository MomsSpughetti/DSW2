#include "worldcup23a2.h"

void readP(const char a[5], permutation_t& per)
{
    for (int i = 0; i < 5; i++)
    {
        per.read(&a[i]);
    }
}

int Nmain()
{
    world_cup_t WWE;

    //add teams
    WWE.add_team(1);
    WWE.add_team(2);
    WWE.add_team(3);

    //remove team
    WWE.remove_team(3);

    permutation_t per1;
    char a0[5] = {'2', '3', '4', '5', '1'};
    readP(a0 , per1);
    
    WWE.add_player(1001, 1, per1, 0, 15 , 2, true);

    permutation_t per2;
    char a[5] = {'4', '3', '5', '2', '1'};
    readP(a , per2);
    
    WWE.add_player(2001, 1, per2, 0, 15 , 2, true);

    WWE.play_match(1, 2);

    int n = WWE.num_played_games_for_player(1001).ans();
    
    WWE.add_player_cards(2001, 2);

    int n1 = WWE.get_player_cards(2001).ans();

    int n3 = WWE.get_team_points(1).ans();

    int n4 = WWE.get_ith_pointless_ability(0).ans();

    permutation_t per3 = WWE.get_partial_spirit(1001).ans();

    per3.strength();

    std::cout << n << n1 << n3 << n4;
    WWE.buy_team(1, 2);

    return 0;
}
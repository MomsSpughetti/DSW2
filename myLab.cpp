#include <iostream>
//using namespace std;
#include <stdlib.h>
#include "wet2util.h"
#include "worldcup23a2.h"


int main()
{
    world_cup_t wc;
    wc.add_team(1);
    wc.add_team(2);
    wc.add_team(3);

    
    wc.add_player(11, 1,permutation_t::read("3,4,5,1,2"), 0, 0, 0, true);
    wc.add_player(12, 1,permutation_t::read("4,5,3,1,2"), 0, 0, 0, true);
    //team 1 spirit: 1 2 5 3 4

    wc.add_player(21, 2,permutation_t::read("3,2,1,5,4"), 0, 0, 0, true);
    wc.add_player(22, 2,permutation_t::read("5,2,3,1,4"), 0, 0, 0, true);
    //team 2 spirit: 4 2 1 3 5

    wc.add_player(31, 3,permutation_t::read("1,4,3,5,2"), 0, 0, 0, true);
    wc.add_player(32, 3,permutation_t::read("2,4,3,5,1"), 0, 0, 0, true);
    //team 3 spirit: 4,5,3,2,1

    wc.add_team(4);
    //team 4 spirit: 1 2 3 4 5

    wc.buy_team(1,2);
    // team 1 spirit: 3 2 1 5 4

    permutation_t p1 = wc.get_partial_spirit(22).ans(); // 3 2 1 5 4

    wc.buy_team(4,1);
    //team 4 spirit: //3 2 1 5 4

    permutation_t p2 = wc.get_partial_spirit(22).ans(); // 3 2 1 5 4

    wc.buy_team(3,4);
    //team 4 spirit: 3 5 4 1 2

    permutation_t p3 = wc.get_partial_spirit(22).ans(); // 3 5 4 1 2

    return 0;
}
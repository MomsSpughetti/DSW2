#include "worldcup23a2.h"

world_cup_t::world_cup_t()
{
	// TODO: Your code goes here
}

world_cup_t::~world_cup_t()
{
	// TODO: Your code goes here
}

StatusType world_cup_t::add_team(int teamId)
{
	
	//invalid inputs
	if(teamId <= 0)
	{
		return StatusType::INVALID_INPUT;
	}
     // try to add the team
	try
	{ 
		if(Teams.checkifexist(teamId))
		{ 
			return StatusType::FAILURE;
		}
		team *newteam=new team(teamId);

		Teams.Insert(teamId, newteam);
		Teamsbyability.Insert(teamId,newteam);
	}
	//bad_alloc
	catch(const std::bad_alloc& e)
	{
	return StatusType::ALLOCATION_ERROR;
	}
	//other exceptions
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	return StatusType::SUCCESS;
}


StatusType world_cup_t::remove_team(int teamId)
{
	
	return StatusType::FAILURE;
}

StatusType world_cup_t::add_player(int playerId, int teamId,
                                   const permutation_t &spirit, int gamesPlayed,
                                   int ability, int cards, bool goalKeeper)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::play_match(int teamId1, int teamId2)
{
	if (teamId1<=0||teamId2<=0||teamId1==teamId2)
	{
	  output_t<int> x(StatusType::INVALID_INPUT);
	  return x;
	}
	try
	{

	team **team1 = this->Teams.Find(teamId1); 
	team **team2 = this->Teams.Find(teamId2);
	
	if((*team1)==nullptr||(*team2)==nullptr||(*team1)->get_teamId()!=teamId1||(*team2)->get_teamId()!=teamId2)
	{
	  output_t<int> x(StatusType::INVALID_INPUT);
	   return x;
	}
	int resultforteam1=(*team1)->get_points()+(*team1)->get_abilities();
	int resultforteam2=(*team2)->get_points()+(*team2)->get_abilities();
	// pay attention that we increase the gamesplayed before comparing the strength and spirit
	(*team1)->increasegamesplayed();
	(*team2)->increasegamesplayed();
	if (resultforteam1<resultforteam2)
	{
		(*team2)->set_winpoints();
		output_t<int> x(3);
	  return x;
		
	}
	if (resultforteam1>resultforteam2)
	{
		(*team1)->set_winpoints();
		output_t<int> x(1);
	     return x;
		
	}
	// if the the teams are equal in strength 
	if (resultforteam1==resultforteam2)
	{
     resultforteam1=(*team1)->get_permstrength();
     resultforteam2=(*team2)->get_permstrength();
	 if (resultforteam1<resultforteam2)
	{
		(*team2)->set_winpoints();
		output_t<int> x(4);
	  return x;
		
	}
	if (resultforteam1>resultforteam2)
	{
		(*team1)->set_winpoints();
		output_t<int> x(2);
	     return x;
		
	}

	}
	// if the teams are equal in spirits and strength

    (*team1)->increasebyone();
	(*team2)->increasebyone();
	output_t<int> x(0);
	return x;

	}
	catch(const std::bad_alloc& b)
	{
		output_t<int> x(StatusType::ALLOCATION_ERROR);
	   return x;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		throw;
	}


}

output_t<int> world_cup_t::num_played_games_for_player(int playerId)
{
	if(playerId<=0)
	{
	output_t<int> x(StatusType::INVALID_INPUT);
	  return x;
	}
	try
	{

		
		
	}
	catch(const std::bad_alloc& e)
	{
		output_t<int> x(StatusType::ALLOCATION_ERROR);
	   return x;
	}
	
	return 22;
}

StatusType world_cup_t::add_player_cards(int playerId, int cards)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_player_cards(int playerId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
	// TODO: Your code goes here
	return 30003;
}

output_t<int> world_cup_t::get_ith_pointless_ability(int i)
{
	// TODO: Your code goes here
	return 12345;
}

output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId)
{
	// TODO: Your code goes here
	return permutation_t();
}

StatusType world_cup_t::buy_team(int teamId1, int teamId2)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

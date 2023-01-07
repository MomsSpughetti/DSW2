#include "worldcup23a2.h"

world_cup_t::world_cup_t() = default;

world_cup_t::~world_cup_t()
{
	Node<int, team*>** QTeams = this->QualifiedTeams.TreeNodesToArray();
	player*** players = ZoomInTeams.get_all_data();

	//delete players
	for (int i = 0; i < ZoomInTeams.used_size(); i++)
	{
		delete *players[i];
	}
	
	//delete qualified teams
	for(int i = 0; i < this->QualifiedTeams.get_size(); i++)
	{
		delete QTeams[i]->data;
	}

	//delete eleminated teams
	SimpleNode<team*>* temp = EliminatedTeams->getFirstNode();
	while (!temp)
	{
		delete temp->data;
	}
	

	//delete arrays
	delete [] QTeams;
	delete [] players;
}

StatusType world_cup_t::add_team(int teamId)
{
	// TODO: Your code goes here
	
	//invalid inputs
	if(teamId <= 0)
	{
		return StatusType::INVALID_INPUT;
	}
     // try to add the team
	try
	{ 
		if(!QualifiedTeams.Find(teamId))
		{ 
			return StatusType::FAILURE;
		}
		team *newteam = new team(teamId);

		QualifiedTeams.Insert(teamId, newteam);
		TeamsByAbility.Insert(teamId,newteam);
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
	// TODO: Your code goes here
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

	team **team1 = this->QualifiedTeams.Find(teamId1); 
	team **team2 = this->QualifiedTeams.Find(teamId2);
	
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
		//get the root of the tree and the player node
     NodeExtra<int,player*,permutation_modified>* playernode=ZoomInTeams.Find(playerId);	
     NodeExtra<int,player*,permutation_modified>* rootnode=ZoomInTeams.Find(playerId);
	 if (playernode==nullptr)
	 {
	  output_t<int> x(StatusType::FAILURE);
	  return x;
	 }
	 // calculate the real gamesplayedgames
	 int gamesplayed=(playernode->data->getgamesplayed()) - (playernode->data->getgamesforteams()) + 
	 (rootnode->data->get_team()->get_num_played_games());

    output_t<int> x(gamesplayed);
	return x;
	}
	catch(const std::bad_alloc& e)
	{
	   output_t<int> x(StatusType::ALLOCATION_ERROR);
	   return x;
	}
     output_t<int> x(StatusType::FAILURE);
	 return x;
}

StatusType world_cup_t::add_player_cards(int playerId, int cards)
{
    if (playerId<=0||cards<0)
	{
		return StatusType::INVALID_INPUT;
	}
    try
	{
	 NodeExtra<int,player*,permutation_modified>* playernode=ZoomInTeams.Find(playerId);
	 if (playernode==nullptr)
	 {
	   return StatusType::FAILURE;
	 }	 	
     NodeExtra<int,player*,permutation_modified>* rootnode=ZoomInTeams.Find(playerId);
	 if (rootnode==nullptr||rootnode->data->get_team()==nullptr||rootnode->data->get_team()->get_eleminated()==true)
	 {
		return StatusType::FAILURE;
	 }
	 playernode->data->addcards(cards);
	 
	}
	catch(const std::bad_alloc& e)
	{
	   StatusType::ALLOCATION_ERROR;  
	}

	 
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_player_cards(int playerId)
{
	if (playerId<=0)
	{
	 output_t<int> x(StatusType::INVALID_INPUT);
	 return x;
	}
	try
	{
	NodeExtra<int,player*,permutation_modified>* playernode=ZoomInTeams.Find(playerId);
	if (playernode==nullptr)
	 {
	  output_t<int> x(StatusType::FAILURE);
	  return x;
	 }
	 int cards=playernode->data->getcards();
	 output_t<int> x(cards);
	  return x;
		
	}
	catch(const std::exception& e)
	{
	   output_t<int> x(StatusType::ALLOCATION_ERROR);
	   return x;
	}
	output_t<int> x(StatusType::FAILURE);
	return x;
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

StatusType world_cup_t::buy_team(int teamId1, int teamId2) //cannot buy eliminated team!
{
	//check inputs
	if(teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2)
		return StatusType::INVALID_INPUT;

	//get teams and check if valid
	team** team1 = QualifiedTeams.Find(teamId1);
	team** team2 = QualifiedTeams.Find(teamId2);

	if(!team1 || !team2)
		return StatusType::FAILURE;
	
	//team1 buys team2

	//get the root player of team1 tree
	int playerInTeam1Id = (*team1)->get_IdOfLastPlayer();
	int playerInTeam2Id = (*team2)->get_IdOfLastPlayer();

	NodeExtra<int, player*, permutation_modified>* root1 = ZoomInTeams.Find(playerInTeam1Id);
	NodeExtra<int, player*, permutation_modified>* root2 = ZoomInTeams.Find(playerInTeam2Id);

	//case 1: team1 and team 2 do not have players
	if(!playerInTeam1Id && !playerInTeam2Id)
	{
		//remove team 2
			//removed later
	}

	//case 2: team 1 has players but team 2 doesn't
	if(playerInTeam1Id && !playerInTeam2Id)
	{
		//remove team2
			//removed later
	}

	//case 3: team 2 has players but team 1 doesn't
	if(!playerInTeam1Id && playerInTeam2Id)
	{
		//simply:
			//make the root2 player points to team1
			//update IdOfLastPlayer in team1
		root2->data->set_team(*team1);
		(*team1)->set_IdOfLastPlayer((*team2)->get_IdOfLastPlayer());

		//remove team2
			//removed later
	}

	//case 4: both has players
	if(playerInTeam1Id && playerInTeam2Id)
	{
		//merge team 2 into team 1
		ZoomInTeams.Union(playerInTeam1Id, playerInTeam2Id);
	}

	//remove team2
	QualifiedTeams.Remove(teamId2);
	return StatusType::SUCCESS;
}
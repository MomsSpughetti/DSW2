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
		if(QualifiedTeams.Find(teamId))
		{ 
			return StatusType::FAILURE;
		}
		team *newteam = new team(teamId);

		QualifiedTeams.Insert(teamId, newteam);
		TeamsByAbility.Insert(*newteam, newteam);
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
	//check inputs
	if(teamId <= 0)
	{
		return StatusType::INVALID_INPUT;
	}

	//get team
	team** TeamToRemove = QualifiedTeams.Find(teamId);
	if (!TeamToRemove)
	{
		//Not found
		return StatusType::FAILURE;
	}
	
	//Remove from QualifiedTeams Tree
	QualifiedTeams.Remove(teamId);

	//set eliminated to True
	(*TeamToRemove)->set_eleminated(true);

	//add to Eliminated Tree
	EliminatedTeams->push_back(*TeamToRemove);

	//Exit
	return StatusType::FAILURE;
}

StatusType world_cup_t::add_player(int playerId, int teamId,
                                   const permutation_t &spirit, int gamesPlayed,
                                   int ability, int cards, bool goalKeeper)
{
	// TODO: Your code goes here
	//check inputs
if(playerId <= 0 ||
	teamId <= 0 ||
	!spirit.isvalid() ||
	gamesPlayed < 0 ||
	cards <0){
		return StatusType::INVALID_INPUT;
	}

	//check team
	team** team_ = QualifiedTeams.Find(teamId);
	team& TeamKey = TeamsByAbility.getIdByReference(**team_);

	if(!team_){
		//team not found
		return StatusType::FAILURE;
	}

	//put player in UF
	team *ptrToTeam = (*team_);
	player* newPLayer = new player(playerId, teamId, spirit, gamesPlayed, ability, cards, goalKeeper);
	newPLayer->set_team(ptrToTeam);
	ZoomInTeams.Insert(playerId, newPLayer, PlayerExtra(spirit));


	//union on them

		//get an id of last added player in team
	int lastPlayerId = (*ptrToTeam).get_IdOfLastPlayer();
	
	//union call
	//nothing happens if this is the first player added
	ZoomInTeams.Union(lastPlayerId, playerId);

	//update team values
		//save a copy of the team before the changes
	team OutDatedCopy = *ptrToTeam;
		//a player id
	ptrToTeam->set_IdOfLastPlayer(playerId);
		//abilitiy
	ptrToTeam->set_abilities((*team_)->get_abilities() + newPLayer->getability());
		//spirit
	ptrToTeam->set_permutation(ptrToTeam->get_permutation() * newPLayer->getspirit());

	//update in Ability tree
	TeamsByAbility.update(OutDatedCopy, *ptrToTeam, ptrToTeam);

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

	//needs some changes, but they don't affect a thing
	//this is enouph:

	increaseGamesPlayedForGivenTeamsBy(1, team1, team2);
	//end of enough

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
     NodeExtra<int,player*,PlayerExtra>* playernode=ZoomInTeams.Find(playerId);	

	 if (playernode==nullptr)
	 {
	  output_t<int> x(StatusType::FAILURE);
	  return x;
	 }
	 // calculate the real gamesplayedgames
	 int gamesPlayed = ZoomInTeams.get_validExtra(playerId).gamesPlayed;

    output_t<int> x(gamesPlayed);
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
	 NodeExtra<int,player*,PlayerExtra>* playernode = ZoomInTeams.getNode(playerId);

	 if (playernode==nullptr)
	 {
	   return StatusType::FAILURE;
	 }	 	
     NodeExtra<int,player*,PlayerExtra>* rootnode = ZoomInTeams.Find(playerId);
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
	NodeExtra<int,player*,PlayerExtra>* playernode=ZoomInTeams.Find(playerId);
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
	//inputs check
	if(teamId <= 0)
	{
		return StatusType::INVALID_INPUT;
	}

	//getv team
	team** team_ = QualifiedTeams.Find(teamId);
	if(!team_)
	{
		return StatusType::FAILURE;
	}

	return (*team_)->get_points();
}

output_t<int> world_cup_t::get_ith_pointless_ability(int i)
{
	//simply get the ith
	Node<team, team*>* team = TeamsByAbility.FindByRank(i);

	//checkk if team exists
	if(!team) {return output_t<int>(StatusType::FAILURE);}

	return team->data->get_teamId();
}

output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId)
{
	//inputs check
	if(playerId <= 0)
	{
		return StatusType::INVALID_INPUT;
	}

	//get the root node of that team
    NodeExtra<int, player* ,PlayerExtra>* playernode = ZoomInTeams.Find(playerId);	
	 
	if (playernode == nullptr || playernode->data->get_team()->get_eleminated() == true)
	{
	  	return StatusType::FAILURE;
	}

	 //calculate the partial permutation
	permutation_t permutation_ = ZoomInTeams.get_validExtra(playerId).permutation;

	return permutation_;
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

	NodeExtra<int, player*, PlayerExtra>* root1 = ZoomInTeams.Find(playerInTeam1Id);
	NodeExtra<int, player*, PlayerExtra>* root2 = ZoomInTeams.Find(playerInTeam2Id);

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

	

	//update the root node
		//get it
	NodeExtra<int, player*, PlayerExtra>* playerInRoot = ZoomInTeams.getNode((*team1)->get_IdOfLastPlayer()); //or any other id in that team

		//make sure the root points to the buyer team
	playerInRoot->data->set_team(*team1);

	return StatusType::SUCCESS;
}

//My Functions

void world_cup_t::increaseGamesPlayedForGivenTeamsBy(int val, team** team1, team** team2)
{
	//increase gamesPlayed extra by one in root for both teams
		//get it
	int Team1_lastPlayerId = (*team1)->get_IdOfLastPlayer();
	NodeExtra<int, player*, PlayerExtra>* playerInRoot1 = ZoomInTeams.getNode(Team1_lastPlayerId); //or any other id in that team

	int Team2_lastPlayerId = (*team2)->get_IdOfLastPlayer();
	NodeExtra<int, player*, PlayerExtra>* playerInRoot2 = ZoomInTeams.getNode(Team2_lastPlayerId); //or any other id in that team

		//update extra in root
	playerInRoot1->extra.increaseGamesPlayed(val);
	playerInRoot2->extra.increaseGamesPlayed(val);
}

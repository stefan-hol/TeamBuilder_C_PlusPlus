#pragma once
#include <vector>
#include "Player.h"
#include "Team.h"
class FootballFrontierInternational
{
private:
	std::vector<Team*> teams;
	std::vector<Player*> overig;

public:
	FootballFrontierInternational();
	~FootballFrontierInternational();
	void MakeTeam(std::string _name);
	void DeleteTeam(Team* team);
	Team* GetTeam(bool _choose = true, int i = 0);  // skip team choosing
	Team* GetTeam(int i = 0, bool _choose = true);  // check for players in the teams
	void MakePlayer(std::string _name, int _age, std::string _position, bool _choose = true);
	void TeamIndexCounter();
};


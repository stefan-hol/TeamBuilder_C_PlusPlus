#include "Handler.h"
Handler::Handler() {
	FFI = new FootballFrontierInternational();
	FFI->MakeTeam("Zeus");
	FFI->MakeTeam("Ocult");
	FFI->MakeTeam("Wild");
	FFI->MakePlayer("pieter", 20, "GK", false);
	FFI->MakePlayer("bob", 20, "DF", false);
}
Handler::~Handler() {
}


#pragma region Losse functions
Player* Handler::SelectPlayer(Team* team) {
	system("CLS");
	std::cout << team->GetName() << ":\n";
	Player* play = team->GetTeamMember(true);
	system("CLS");
	return play;
} 
void Handler::WrongInput(bool inputCheck) {
	system("CLS");
	if (std::cin.fail()) 
	{
		run = true;
		std::cout << "wrong input, type an int to go on.\n";
		int ind;
		while (run) {
			run = false;
			std::cin >> ind;
			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore();
				run = true;
			}
		}
		run = true;
		return;
	}
	if (inputCheck == false) {
		std::cout << "wrong input try again.\n";
		system("pause");
	}
}
FootballFrontierInternational* Handler::GetFFI() {
	return FFI;
}
#pragma endregion

#pragma region Create
void Handler::Create(FootballFrontierInternational* FFI)
{
	currentState2 = MenuStates::MAINMENU;
	while (run)
	{
		system("CLS");
		std::cout << "What do you want to create? player(1), team(2), stop(3)\n";
		std::cin >> i;
		if (i == 1)
		{
			currentState2 = MenuStates::PLAYER;
		}
		if (i == 2)
		{
			currentState2 = MenuStates::TEAM;
		}
		if (i == 3) 
		{
			run = false;
		}
		if (i != 1 && i != 2 && i != 3 && std::cin.fail())
		{
			WrongInput();
		}
		switch (currentState2)
		{
			case MenuStates::PLAYER:
			{
				MakePlayerIndex(FFI);
				break;
			}
			case MenuStates::TEAM:
			{
				MakeTeamIndex(FFI);
				break;
			}
		}
	}
}

void Handler::MakePlayerIndex(FootballFrontierInternational* FFI) 
{
	std::string naam, positie;
	system("CLS");
	std::cout << "Naam , leeftijd(tussen 9 en 40) en positie(GK,DF,MF,AT)\n";
	std::cin >> naam >> i >> positie;
	if (std::cin.fail()) {
		WrongInput(false);
		return MakePlayerIndex(FFI);
	}
	FFI->MakePlayer(naam, i, positie);
	system("CLS");
	std::cout << "Want to make another player(1), or go back to main(2)?\n";
	std::cin >> i;
	if (i == 1) {
		return MakePlayerIndex(FFI);
	}
	run = false;
}

void Handler::MakeTeamIndex(FootballFrontierInternational* FFI) 
{
	std::string naam;
	system("CLS");
	std::cout << "naam van team\n";
	std::cin >> naam;
	FFI->MakeTeam(naam);
	system("CLS");
	std::cout << "Want to make another team(1), or go back to main(2)?\n";
	std::cin >> i;
	if (i == 1) {
		return MakeTeamIndex(FFI);
	}
	run = false;
}
#pragma endregion

#pragma region Change
void Handler::Change(FootballFrontierInternational* FFI) {

	currentState2 = MenuStates::MAINMENU;
	while (run)
	{
		system("CLS");
		std::cout << "you want to change(1), delete(2) or quit(3)?\n";
		std::cin >> i;
		switch (i)
		{
			case 1:
			{
				ChangeItem(FFI);
				break;
			}
			case 2:
			{
				std::cout << "want to delete a player(1), a team(2) or go back(3)?\n";
				std::cin >> i;
				switch (i) {
					case 1:
					{
						DeletePlayer(FFI);
						break;
					}
					case 2:
					{
						DeleteTeam(FFI);
						break;
					}
					case 3:
					{
						run = false;
						break;
					}
					default: 
					{
						WrongInput();
					}
				}
				break;
			}
			case 3:
			{
				run = false;
				break;
			}
			default: 
			{
				WrongInput();
			}
		}
	}
}

void Handler::ChangeItem(FootballFrontierInternational* FFI) {
	system("CLS");
	std::cout << "choose a team and then a player.\n";
	Team* team = FFI->GetTeam(i, stats = false);
	Player* play = SelectPlayer(team);
	system("CLS");
	std::cout << "choose a team to switch to.\n";
	Team* team2 = FFI->GetTeam(i, stats = true);
	team2->AddPlayer(play);
	team->DeletePlayer(play);
	system("CLS");
	std::cout << "want to go back(1)or make more changes?(2)?\n";
	std::cin >> i;
	if (i == 1) {
		run = false;
	}
};

void Handler::DeletePlayer(FootballFrontierInternational* FFI) {
	system("CLS");
	Team* team = FFI->GetTeam(i, stats = false);
	Player* play = SelectPlayer(team);
	team->DeletePlayer(play,death = true);
	system("CLS");
	std::cout << "want to go back(1)or make more changes?(2)?\n";
	std::cin >> i;
	if (i == 1) {
		run = false;
	}
}

void Handler::DeleteTeam(FootballFrontierInternational* FFI) {
	system("CLS");
	Team* team = FFI->GetTeam(death = true, i);
	if (team == FFI->GetTeam(death = false, i))
	{
		std::cout << "cant delete overig\n";
		system("pause");
		return;
	}
	FFI->DeleteTeam(team);
	system("CLS");
	std::cout << "want to go back(1)or make more changes?(2)?\n";
	std::cin >> i;
	if (i == 1) {
		run = false;
	}
}
#pragma endregion

#pragma region View
void Handler::View(FootballFrontierInternational* FFI) {
	while (run) {
		system("CLS");
		std::cout << "you want the players(1) or a player his stats(2)\n";
		std::cin >> i;
		Team* team = FFI->GetTeam(i, stats = false);
		switch (i)
		{
		case 1: {
			std::cout << team->GetName() << ":\n";
			Player* play = team->GetTeamMember(stats = false);
			system("pause");
			run = false;
			break;
		}
		case 2: {

			while (run) {
				system("CLS");
				Player* play = SelectPlayer(team);
				play->GetStats();
				std::cout << "if you are done press (1). if you want to see some more(2)\n";
				std::cin >> i;
				if (i == 1) {
					run = false;
				}
			}
			break;

		}
		default:
			WrongInput();
		}
	}
}
#pragma endregion



#include "GameManager.hpp"

GameManager::GameManager(void* ptr) : playerMin(0), playerMax(0), enemyMin(0), enemyMax(0), money(100), bet(20), playerCardCount(-1), enemyCardCount(-1), IsGameStarted(false), dealer(nullptr),playerBustFlag(false),playerStayFlag(false),gameEndFlag(false),enemyBustFlag(false)
{
	this->gameObjectPtr = ptr;
	//cardsIntArray[12] = {2,3,4,5,6,7,8,9,10,10,10,11};
	for (size_t i = 0; i < 5; i++)
	{
		playerCards[i] = nullptr;
		enemyCards[i] = nullptr;
	}
	for (size_t i = 0; i < 2; i++)
	{
		buttons[i] = nullptr;
	}
}
void GameManager::Update() {
	if (!dealer->IsBusy())
	{
		
		if (!IsGameStarted) //check if no game is played
		{
			BeginRound();
		}
		else if (IsGameStarted && gameEndFlag) { //decides winner.
			
			if (playerMax > enemyMax) {
				Win();
			}
			else if (playerMax == enemyMax) {
				//draw the game.
			}
			else {
				Lose();
			}
		}
		else if (playerStayFlag || playerMin > 21) //check if player's turn ended or busted
		{
			EndRound();
		}
		else if (playerHitFlag) {
			playerHitFlag = false;
			Hit(PlayerName::Player);
		}
		//else if (playerBustFlag || playerStayFlag) //check if player's turn ended.
		//{
		//	EndRound();
		//}

	}
}
void GameManager::Start() {

}
void GameManager::BeginRound() {
	for (int i = 0; i < 3; i++)
	{
		if (i == 2) Hit(PlayerName::Computer);
		else
		{
			Hit(PlayerName::Player);
		}
	}
	IsGameStarted = true;
}
/*
Animation method that invokes ending animation and data.
*/
void GameManager::EndRound() {
	while (enemyMax < 17)
	{
		Hit(PlayerName::Computer);
	}
	gameEndFlag = true;

}
void GameManager::Hit(PlayerName hitter) {
	SetActiveOfButtons(false);
	int rand = std::rand() % 48;
	int randVal;
	if (rand < 36) //Value Cards
	{
		randVal = rand / 4 + 2;
	}
	else if (rand < 44) //Kings and Queens
	{
		randVal = 10;
	}
	else //Aces
	{
		randVal = 11;
	}

	if (hitter == PlayerName::Player)
	{

		playerCardCount++;
		playerCards[playerCardCount]->setTexture(*playingCards[rand]);
		playerMin += randVal != 11 ? randVal : 1;
		if (randVal == 11 && playerMax + randVal > 21) playerMax++;
		else
		{
			playerMax += randVal;
		}
		if (playerMin > 21) playerBustFlag = true; //bust check
		dealer->AddQueue((CardController*)playerCards[playerCardCount]->scripts[0]);
	}
	else if (hitter == PlayerName::Computer)
	{
		enemyCardCount++;
		enemyCards[enemyCardCount]->setTexture(*playingCards[rand]);
		enemyMin += randVal != 11 ? randVal : 1;
		if (randVal == 11 && enemyMax + randVal > 21) enemyMax++;
		else
		{
			enemyMax += randVal;
		}
		if (enemyMin > 21) enemyBustFlag = true;
		dealer->AddQueue((CardController*)enemyCards[enemyCardCount]->scripts[0]);
	}
}
void GameManager::SetActiveOfButtons(bool val) {
	for (GameObject<sf::Sprite>* i : buttons)
	{
		if (i) i->isActive = val;
	}
}
void GameManager::Stay(){}
void GameManager::Win(){}
void GameManager::Lose(){}
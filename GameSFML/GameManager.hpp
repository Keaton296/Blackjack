#pragma once
#include "MonoBehaviour.hpp"
#include "GameObject.hpp"
#include "CardDealer.hpp"
extern sf::Texture* playingCards[49];
enum PlayerName {
	Player,
	Computer
};
class GameManager : public MonoBehaviour {
private:
	int cardsIntArray[12] = { 2,3,4,5,6,7,8,9,10,10,10,11 };
	int playerCardCount;
	int enemyCardCount;
	int playerMin;
	int playerMax;
	int enemyMin;
	int enemyMax;
	int money;
	int bet;
	bool playerBustFlag;
	bool gameEndFlag;
	bool IsGameStarted;
public:
	static GameManager* instance;
	bool playerHitFlag;
	bool playerStayFlag;
	bool enemyBustFlag;
	CardDealer* dealer;
	GameObject<sf::Sprite>* playerCards[5];
	GameObject<sf::Sprite>* enemyCards[5];
	GameObject<sf::Sprite>* buttons[2];
	//cardcontroller pointer
	GameManager(void* ptr);
	void Update();
	void Start();
	void BeginRound();
	void EndRound();
	void Hit(PlayerName hitter);
	void Stay();
	void Win();
	void Lose();
	void SetActiveOfButtons(bool val);
};
enum GameState {
	End
};
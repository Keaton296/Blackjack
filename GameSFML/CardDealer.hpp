#pragma once
#include "MonoBehaviour.hpp"
#include "GameObject.hpp"
#include "CardController.hpp"
#include <queue>
class GameManager;
/*
 A class responsible for animating card gameobjects co-ordinately that implement sf::Sprite.
*/
class CardDealer : public MonoBehaviour {
private:
	std::queue<CardController*> animQueue;
public:
	GameManager* managerPtr;
	CardDealer(void* objRef);
	CardDealer();
	void Start();
	void Update();
	void AddQueue(CardController* controllerPtr);
	bool IsBusy();
};
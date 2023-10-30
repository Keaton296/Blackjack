#include "GameScene.hpp"
#include "SFML/Audio.hpp"
#include "CardController.hpp"
#include "GameObject.hpp"
#include "SpriteButton.hpp"
#include <math.h>
#include "CardDealer.hpp"
#include "GameManager.hpp"

//EXTERNAL GLOBAL VARIABLES
extern sf::Texture hitButtonTex;
extern sf::Texture stayButtonTex;
extern sf::Texture backButtonTex;
extern sf::Font* titleFont;
extern sf::Texture* backgroundTexture;
extern sf::Texture* playingCards[49];
extern Scene* currentScene;
extern sf::RenderWindow* WINDOWPTR;
extern sf::Event windowEvent;
extern enum SceneName;
extern SceneName queuedSceneName;
extern sf::SoundBuffer* cardShuffleBuffer;
extern sf::SoundBuffer* cardPickBuffer;
extern sf::Sound soundPlayer;
void PlayerHitFunc();

GameManager* GameManager::instance;

GameScene::GameScene()
{
	for (int i = 0; i < 20; i++) 
	{
		textGameObjects[i] = nullptr;
		spriteGameObjects[i] = nullptr;
	}

	soundPlayer.setBuffer(*cardShuffleBuffer);
	soundPlayer.play();

	//gamemanager
	textGameObjects[1] = new GameObject<sf::Text>();
	textGameObjects[1]->CreateMonoBehaviourOfType<GameManager>();
	GameManager* gameManagerTextPtr = (GameManager*)textGameObjects[1]->scripts[0];
	GameManager::instance = gameManagerTextPtr;
	
	//carddealer
	textGameObjects[0] = new GameObject<sf::Text>();
	textGameObjects[0]->CreateMonoBehaviourOfType<CardDealer>();
	CardDealer* cardDealerTextPtr = (CardDealer*)textGameObjects[0]->scripts[0];
	gameManagerTextPtr->dealer = cardDealerTextPtr;
	cardDealerTextPtr->managerPtr = gameManagerTextPtr;

	//background
	spriteGameObjects[0] = new GameObject<sf::Sprite>();
	spriteGameObjects[0]->setTexture(*backgroundTexture);
	spriteGameObjects[0]->setScale(2, 2);

	//playercard0
	spriteGameObjects[1] = new GameObject<sf::Sprite>();
	spriteGameObjects[1]->setScale(.3f, .3f);
	spriteGameObjects[1]->CreateMonoBehaviourOfType<CardController>();
	spriteGameObjects[1]->setTexture(*playingCards[4]);
	spriteGameObjects[1]->isActive = false;
	CardController* cardControllerSpritePtr = (CardController*) spriteGameObjects[1]->scripts[0];
	sf::Vector2f card0start(60, 400);
	sf::Vector2f card0end(60, 300);
	cardControllerSpritePtr->SetStartPos(card0start);
	cardControllerSpritePtr->SetEndPos(card0end);


	//playercard1
	spriteGameObjects[2] = new GameObject<sf::Sprite>();
	spriteGameObjects[2]->setScale(.3f, .3f);
	spriteGameObjects[2]->CreateMonoBehaviourOfType<CardController>();
	cardControllerSpritePtr = (CardController*) spriteGameObjects[2]->scripts[0];
	spriteGameObjects[2]->isActive = false;
	sf::Vector2f card1start(100, 400);
	sf::Vector2f card1end(100, 300);
	cardControllerSpritePtr->SetStartPos(card1start);
	cardControllerSpritePtr->SetEndPos(card1end);

	//playercard2
	spriteGameObjects[8] = new GameObject<sf::Sprite>();
	spriteGameObjects[8]->setScale(.3f, .3f);
	spriteGameObjects[8]->CreateMonoBehaviourOfType<CardController>();
	cardControllerSpritePtr = (CardController*)spriteGameObjects[8]->scripts[0];
	spriteGameObjects[8]->isActive = false;
	sf::Vector2f card2start(140, 400);
	sf::Vector2f card2end(140, 300);
	cardControllerSpritePtr->SetStartPos(card2start);
	cardControllerSpritePtr->SetEndPos(card2end);


	//enemycard0
	spriteGameObjects[3] = new GameObject<sf::Sprite>();
	spriteGameObjects[3]->setScale(.3f, .3f);
	spriteGameObjects[3]->CreateMonoBehaviourOfType<CardController>();
	spriteGameObjects[3]->isActive = false;
	cardControllerSpritePtr = (CardController*) spriteGameObjects[3]->scripts[0];
	sf::Vector2f enemycard0start(60, -100);
	sf::Vector2f enemycard0end(60, 10);
	cardControllerSpritePtr->SetStartPos(enemycard0start);
	cardControllerSpritePtr->SetEndPos(enemycard0end);

	//enemycard1
	spriteGameObjects[4] = new GameObject<sf::Sprite>();
	spriteGameObjects[4]->setScale(.3f, .3f);
	spriteGameObjects[4]->CreateMonoBehaviourOfType<CardController>();
	spriteGameObjects[4]->isActive = false;
	cardControllerSpritePtr = (CardController*) spriteGameObjects[4]->scripts[0];
	sf::Vector2f enemycard1start(100, -100);
	sf::Vector2f enemycard1end(100, 10);
	cardControllerSpritePtr->SetStartPos(enemycard1start);
	cardControllerSpritePtr->SetEndPos(enemycard1end);


	//hitbutton
	spriteGameObjects[5] = new GameObject<sf::Sprite>();
	spriteGameObjects[5]->setTexture(hitButtonTex);
	spriteGameObjects[5]->setOrigin(spriteGameObjects[5]->getGlobalBounds().getSize() / 2.f);
	spriteGameObjects[5]->setScale(.25f, .25f);
	spriteGameObjects[5]->CreateMonoBehaviourOfType<SpriteButton>();
	SpriteButton* hitButtonScript = (SpriteButton*)spriteGameObjects[5]->scripts[0];
	hitButtonScript->OnClickAction = PlayerHitFunc;
	spriteGameObjects[5]->setPosition(650, 400);

	//staybutton
	spriteGameObjects[6] = new GameObject<sf::Sprite>();
	spriteGameObjects[6]->setTexture(stayButtonTex);
	spriteGameObjects[6]->setOrigin(spriteGameObjects[6]->getGlobalBounds().getSize() / 2.f);
	spriteGameObjects[6]->setScale(.25f, .25f);
	spriteGameObjects[6]->CreateMonoBehaviourOfType<SpriteButton>();
	spriteGameObjects[6]->setPosition(650, 480);

	//exitbutton
	spriteGameObjects[7] = new GameObject<sf::Sprite>();
	spriteGameObjects[7]->CreateMonoBehaviourOfType<SpriteButton>();
	SpriteButton* spritebuttonptr = (SpriteButton*)spriteGameObjects[7]->scripts[0];
	spritebuttonptr->OnClickAction = []() {queuedSceneName = (SceneName)1; };
	spritebuttonptr->SetNormalScale(.25f);
	spritebuttonptr->SetLargeScale(.3f);
	spriteGameObjects[7]->setTexture(backButtonTex);
	spriteGameObjects[7]->setOrigin(spriteGameObjects[7]->getGlobalBounds().width, 0);
	spriteGameObjects[7]->setPosition(800, 0);

	//gamamanager init
	gameManagerTextPtr->enemyCards[0] = spriteGameObjects[3];
	gameManagerTextPtr->enemyCards[1] = spriteGameObjects[4];
	gameManagerTextPtr->playerCards[0] = spriteGameObjects[1];
	gameManagerTextPtr->playerCards[1] = spriteGameObjects[2];
	gameManagerTextPtr->playerCards[2] = spriteGameObjects[8];
	gameManagerTextPtr->buttons[0] = spriteGameObjects[5];
	gameManagerTextPtr->buttons[1] = spriteGameObjects[6];
		
}
GameScene::~GameScene() 
{
	for (auto i : textGameObjects) {
		delete i;
	}
	for (auto i : spriteGameObjects) {
		delete i;
	}
}
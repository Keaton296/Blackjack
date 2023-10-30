#include "MenuScene.hpp"
#include "GameObject.hpp"
#include "GameScene.hpp"
#include "SpriteButton.hpp"
#include "TextButton.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Main.hpp"
#include "MonoBehaviour.hpp"

//EXTERNAL VALUES

extern sf::RenderWindow* WINDOWPTR;
extern sf::Font* titleFont;
extern sf::Texture* backgroundTexture;
extern sf::Texture* playingCards[48];
extern Scene* currentScene;
extern sf::Event windowEvent;
extern enum SceneName;
extern SceneName queuedSceneName;

MenuScene::MenuScene() 
{
	for (int i = 0; i < 20; i++) {
		textGameObjects[i] = nullptr;
		spriteGameObjects[i] = nullptr;
	}
	//gametitle
	textGameObjects[0] = new GameObject<sf::Text>();
	textGameObjects[0]->setFont(*titleFont);
	textGameObjects[0]->setCharacterSize(100);
	textGameObjects[0]->setFillColor(sf::Color::White);
	textGameObjects[0]->setOutlineThickness(5);
	textGameObjects[0]->setOutlineColor(sf::Color::Black);
	textGameObjects[0]->setString(sf::String("Blackjack"));
	textGameObjects[0]->setOrigin(textGameObjects[0]->getGlobalBounds().getSize() / 2.f);
	textGameObjects[0]->setPosition(400, 50);
	//playbutton
	textGameObjects[1] = new GameObject<sf::Text>();
	textGameObjects[1]->CreateMonoBehaviourOfType<TextButton>();
	TextButton* textButtonPtr = (TextButton*)textGameObjects[1]->scripts[0];
	textButtonPtr->OnClickAction = []() {queuedSceneName = (SceneName)2; };
	textGameObjects[1]->setFont(*titleFont);
	textGameObjects[1]->setCharacterSize(60);
	textGameObjects[1]->setFillColor(sf::Color::White);
	textGameObjects[1]->setOutlineThickness(3);
	textGameObjects[1]->setOutlineColor(sf::Color::Black);
	textGameObjects[1]->setString(sf::String("Play"));
	textGameObjects[1]->setOrigin(textGameObjects[1]->getGlobalBounds().getSize() / 2.f);
	textGameObjects[1]->setPosition(400, 200);
	//exitbutton
	textGameObjects[2] = new GameObject<sf::Text>();
	textGameObjects[2]->setFont(*titleFont);
	textGameObjects[2]->setCharacterSize(60);
	textGameObjects[2]->setFillColor(sf::Color::White);
	textGameObjects[2]->setOutlineThickness(3);
	textGameObjects[2]->setOutlineColor(sf::Color::Black);
	textGameObjects[2]->setString(sf::String("Exit"));
	textGameObjects[2]->setOrigin(textGameObjects[2]->getGlobalBounds().getSize() / 2.f);
	textGameObjects[2]->CreateMonoBehaviourOfType<TextButton>();
	textButtonPtr = (TextButton*)textGameObjects[2]->scripts[0];
	textButtonPtr->OnClickAction = []() {WINDOWPTR->close(); };
	textGameObjects[2]->setPosition(400, 300);
	//authortext
	textGameObjects[3] = new GameObject<sf::Text>();
	textGameObjects[3]->setFont(*titleFont);
	textGameObjects[3]->setCharacterSize(30);
	textGameObjects[3]->setFillColor(sf::Color::White);
	textGameObjects[3]->setOutlineThickness(3);
	textGameObjects[3]->setOutlineColor(sf::Color::Black);
	textGameObjects[3]->setString(sf::String("Kaan Dalkiran"));
	textGameObjects[3]->setPosition(800 - textGameObjects[3]->getGlobalBounds().width, 550);
	//background
	spriteGameObjects[0] = new GameObject<sf::Sprite>();
	spriteGameObjects[0]->setTexture(*backgroundTexture);
	spriteGameObjects[0]->setScale(2, 2);
	//background card 0
	spriteGameObjects[1] = new GameObject<sf::Sprite>();
	spriteGameObjects[1]->setTexture(*playingCards[0]);
	spriteGameObjects[1]->setScale(.3f, .3f);
	spriteGameObjects[1]->setRotation(25);
	spriteGameObjects[1]->setPosition(30, 500);
	//background card 1
	spriteGameObjects[2] = new GameObject<sf::Sprite>();
	spriteGameObjects[2]->setTexture(*playingCards[42]);
	spriteGameObjects[2]->setScale(.3f, .3f);
	spriteGameObjects[2]->setRotation(10);
	spriteGameObjects[2]->setPosition(-60, 200);
	//background card 1
	spriteGameObjects[3] = new GameObject<sf::Sprite>();
	spriteGameObjects[3]->setTexture(*playingCards[35]);
	spriteGameObjects[3]->setScale(.3f, .3f);
	spriteGameObjects[3]->setRotation(-10);
	spriteGameObjects[3]->setPosition(700, 200);
}
MenuScene::~MenuScene() {
	for (GameObject<sf::Sprite>* i : spriteGameObjects) {
		delete i;
	}
	for (GameObject<sf::Text>* i : textGameObjects) {
		delete i;
	}
}
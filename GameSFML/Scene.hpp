#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Main.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "GameObject.hpp"
/*
Abstract class header for all scenes made in the game.
*/
class Scene {
public:
	GameObject<sf::Sprite>* spriteGameObjects [20];
	GameObject<sf::Text>* textGameObjects [20];
	void update();
	void render();
};
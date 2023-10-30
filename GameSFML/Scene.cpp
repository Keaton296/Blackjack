#include "Scene.hpp"
extern sf::RenderWindow* WINDOWPTR;
void Scene::update()
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (textGameObjects[i] != nullptr && textGameObjects[i]->scripts[j] != nullptr) textGameObjects[i]->scripts[j]->Update();
			if (spriteGameObjects[i] != nullptr && spriteGameObjects[i]->scripts[j] != nullptr) spriteGameObjects[i]->scripts[j]->Update();

		}
	}
}
void Scene::render()
{
	WINDOWPTR->clear(sf::Color::Green);

	for (GameObject<sf::Sprite>* i : spriteGameObjects) 
	{
		if (i != nullptr && i->isActive) WINDOWPTR->draw(*i);
	}
	for (GameObject<sf::Text>* i : textGameObjects) 
	{
		if (i != nullptr && i->isActive) WINDOWPTR->draw(*i);
	}
	WINDOWPTR->display();
}

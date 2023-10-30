#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Main.hpp"
#include "MonoBehaviour.hpp"

/*
 a GameObject can represent any class that inherits sf::Drawable and sf::Transformable, otherwise it may not make sense to create GameObjects.
 It could represent any object in the game and has a MonoBehaviour array which should be executed from any object inherited from the Scene class.
*/
template <typename T>
class GameObject: public T {
private:
	int scriptCount;
public:
	MonoBehaviour* scripts[3];
	bool isActive;
	template<typename A>
	bool CreateMonoBehaviourOfType() 
	{
		if (scriptCount < 2) 
		{
			scripts[scriptCount] = new A(this);
			scriptCount++;
			return true;
		}
		return false;
	}


	~GameObject()
	{
		for (int i = 0; i < scriptCount; i++) 
		{
			delete scripts[i];
		}
	}
	GameObject() : scriptCount(0),isActive(true) 
	{
		scripts[0] = nullptr;
		scripts[1] = nullptr;
		scripts[2] = nullptr;
	}
};
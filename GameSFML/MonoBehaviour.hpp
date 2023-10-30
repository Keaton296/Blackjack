#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Main.hpp"
/*
	Abstract class that represents scripts in a typical game engine.
	Derive from it when creating customized scripts.
*/
class MonoBehaviour {
public:
	/*
	Points to the GameObject the MonoBehaviour has its control on.
	*/
	void* gameObjectPtr;
	/*
	Use this constructor to initialize its pointer to MonoBehaviour's assigned GameObject.
	*/
	MonoBehaviour(void* objPtr);
	/*
	Usage of MonoBehaviour(sf::Transformable* obj) is recommended.
	*/
	MonoBehaviour();
	/*
	Code that's executed when MonoBehaviour is made.
	*/
	virtual void Start() = 0;
	/*
	Code that's executed every game loop.
	*/
	virtual void Update() = 0;
};
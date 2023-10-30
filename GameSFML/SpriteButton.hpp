#pragma once
#include "MonoBehaviour.hpp"
#include "GameObject.hpp"
#include "SFML/Main.hpp"
#include "SFML/System.hpp"

extern sf::Vector2i mousePosition;
extern bool Mouse0Pressed;
extern enum SceneName;
extern SceneName queuedSceneName;

class SpriteButton : public MonoBehaviour {
protected:
	float largeScale;
	float normalScale;
	bool enlargened;
	bool previousMouse0Pressed;
	GameObject<sf::Sprite>* castedGameObjectPtr;
public:
	void (*OnClickAction)();
	void (*OnStartAction)();
	SpriteButton(void* objRef);
	SpriteButton();
	void Start();
	void SetLargeScale(float x);
	void SetNormalScale(float x);
	void Update();
};
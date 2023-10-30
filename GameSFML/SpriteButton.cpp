#include "SpriteButton.hpp"
#include "GameManager.hpp"
SpriteButton::SpriteButton(void* objRef) : OnStartAction(nullptr),OnClickAction(nullptr), previousMouse0Pressed(false), enlargened(false), largeScale(1.5f), normalScale(1)
{
	this->gameObjectPtr = objRef;
	castedGameObjectPtr = (GameObject<sf::Sprite>*) objRef;
	normalScale = castedGameObjectPtr->getScale().x;
	largeScale = normalScale * 1.3f;
}
SpriteButton::SpriteButton() : OnStartAction(nullptr), OnClickAction(nullptr), previousMouse0Pressed(false), enlargened(false), largeScale(1.5f), normalScale(1)
{
	this->gameObjectPtr = nullptr;
	castedGameObjectPtr = nullptr;
}
void SpriteButton::Start()
{

}

void SpriteButton::SetLargeScale(float x)
{
	largeScale = x;
}
void SpriteButton::SetNormalScale(float x)
{
	normalScale = x;
}

void SpriteButton::Update()
{
	
		if (castedGameObjectPtr->getGlobalBounds().contains((sf::Vector2f)mousePosition)) {
			castedGameObjectPtr->setScale(largeScale, largeScale);
		}
		else
		{
			castedGameObjectPtr->setScale(normalScale, normalScale);
		}
		if (!previousMouse0Pressed && Mouse0Pressed) {
			if (castedGameObjectPtr->getGlobalBounds().contains((sf::Vector2f)mousePosition)) {
				if (OnClickAction) OnClickAction();
			}
		}
		previousMouse0Pressed = Mouse0Pressed;
	
}
void PlayerHitFunc() {

	if(GameManager::instance) GameManager::instance->playerHitFlag = true;
}

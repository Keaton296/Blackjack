#include "TextButton.hpp"

TextButton::TextButton(void* objRef) : OnStartAction(nullptr), OnClickAction(nullptr), previousMouse0Pressed(false), enlargened(false), largeScale(1.5f), normalScale(1)
{
	this->gameObjectPtr = objRef;
	castedGameObjectPtr = (GameObject<sf::Text>*) objRef;
}
TextButton::TextButton() : OnStartAction(nullptr), OnClickAction(nullptr), previousMouse0Pressed(false), enlargened(false), largeScale(1.5f), normalScale(1)
{
	this->gameObjectPtr = nullptr;
	castedGameObjectPtr = nullptr;
}
void TextButton::Start()
{

}

void TextButton::SetLargeScale(float x)
{
	largeScale = x;
}
void TextButton::SetNormalScale(float x)
{
	normalScale = x;
}

void TextButton::Update()
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

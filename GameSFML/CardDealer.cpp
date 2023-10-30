#include "CardDealer.hpp"
#include "GameManager.hpp"

CardDealer::CardDealer(void* objRef) : managerPtr(nullptr)
{
	this->gameObjectPtr = &objRef;
}
CardDealer::CardDealer() : managerPtr(nullptr)
{
	gameObjectPtr = nullptr;
}
void CardDealer::Start() {

}
void CardDealer::Update()
{
	if (!animQueue.empty())
	{

		if (animQueue.front()->isAnimating())
		{
			return;
		}
		else
		{
			if (animQueue.front()->isAnimationEnded())
			{
				animQueue.pop();
				if (managerPtr && animQueue.empty()) managerPtr->SetActiveOfButtons(true);
			}
			else
			{
				animQueue.front()->StartAnim(1);
				((GameObject<sf::Sprite>&)animQueue.front()->gameObjectPtr).isActive = true;

			}
		}
	}
	else
	{

	}
}
void CardDealer::AddQueue(CardController* controllerPtr)
{
	if (controllerPtr) animQueue.push(controllerPtr);
	if (managerPtr) managerPtr->SetActiveOfButtons(false);
}
bool CardDealer::IsBusy()
{
	return !animQueue.empty();
}
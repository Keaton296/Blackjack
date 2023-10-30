#pragma once
#include "MonoBehaviour.hpp"
extern sf::Texture* playingCards[49];
/*
FPS Dependent GameObject position animator.
*/
class CardController : public MonoBehaviour{
private:
	sf::Vector2f endPos;
	sf::Vector2f startPos;
	bool m_isAnimating;
	bool m_animEnded;
	GameObject<sf::Sprite>* transformableOfObject;
public:
	float unitsPerFrame;
	CardController(void* objRef, sf::Vector2f start, sf::Vector2f end) : m_isAnimating(false), unitsPerFrame(4.f),m_animEnded(false)
	{
		this->gameObjectPtr = objRef;
		this->startPos = start;
		this->endPos = end;
		transformableOfObject = (GameObject<sf::Sprite>*)this->gameObjectPtr;
		transformableOfObject->setPosition(startPos);
	}
	CardController(void* objRef) : startPos(sf::Vector2f()),endPos(sf::Vector2f()), m_isAnimating(false), unitsPerFrame(4.f), m_animEnded(false)
	{
		this->gameObjectPtr = objRef;
		transformableOfObject = (GameObject<sf::Sprite>*)this->gameObjectPtr;
	}
	bool isAnimating()
	{
		return m_isAnimating;
	}
	bool isAnimationEnded()
	{
		return m_animEnded;
	}
	void Update()
	{
		if (m_isAnimating) {
			sf::Vector2f dir = this->endPos - transformableOfObject->getPosition();
			float ratio = sqrt(pow(dir.x, 2) + pow(dir.y, 2));
			if (ratio < unitsPerFrame) StopAnim();
			else {
				ratio = 1 / ratio;
				dir *= ratio * unitsPerFrame;
				transformableOfObject->move(dir);
			}
		}
	}
	void Start()
	{
	}
	void StartAnim(int texIndex)
	{
		transformableOfObject->isActive = true;
		this->m_animEnded = false;
		transformableOfObject->setTexture(*playingCards[std::rand() % 49]);
		transformableOfObject->setPosition(startPos);
		this->m_isAnimating = true;
	}
	void StopAnim() {
		GameObject<sf::Sprite>* ptr = (GameObject<sf::Sprite>*) this->gameObjectPtr;
		ptr->setPosition(endPos);
		this-> m_isAnimating = false;
		this-> m_animEnded = true;
	}
	void SetStartPos(sf::Vector2f& pos) {
		this->startPos = pos;
	}
	void SetEndPos(sf::Vector2f& pos) {
		this->endPos = pos;
	}

};
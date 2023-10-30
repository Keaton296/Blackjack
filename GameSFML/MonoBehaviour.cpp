#include "MonoBehaviour.hpp"

MonoBehaviour::MonoBehaviour(void* objPtr) {
	gameObjectPtr = objPtr;
}

MonoBehaviour::MonoBehaviour() : gameObjectPtr(nullptr) {

}


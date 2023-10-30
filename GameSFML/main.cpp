#include "Scene.hpp"
#include "MenuScene.hpp"
#include "GameScene.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Main.hpp"
#include <Windows.h>
/*
Enum that is used for changing scenes.
Used from inside of scene objects to queue in what scene should be loaded in the next game loop.
*/
enum SceneName {
    Null,
    Menu,
    Game
};

/*
GLOBAL VARIABLES
These variables are usually accessed from scene objects.
*/
Scene* currentScene;
SceneName currentSceneName;
SceneName queuedSceneName;
sf::RenderWindow* WINDOWPTR;
sf::VideoMode VIDEOMODE;
sf::Event windowEvent;
sf::Font* titleFont;
//INPUT
sf::Vector2i mousePosition;
bool mouseButtonHold;
bool Mouse0Pressed;
bool Mouse1Pressed;
// TEXTURES
sf::Texture* backgroundTexture;
sf::Texture* playingCards[49];
sf::Texture hitButtonTex;
sf::Texture stayButtonTex;
sf::Texture backButtonTex;
//AUDIO
sf::SoundBuffer* cardShuffleBuffer;
sf::SoundBuffer* cardPickBuffer;
sf::Sound soundPlayer;

void InitGlobalVariables() {
    queuedSceneName = SceneName::Null;
    soundPlayer = sf::Sound();
    cardShuffleBuffer = new sf::SoundBuffer;
    cardPickBuffer = new sf::SoundBuffer;
    cardPickBuffer->loadFromFile("sounds/cardpick0.wav");
    cardShuffleBuffer->loadFromFile("sounds/cardshuffle.wav");
    hitButtonTex.loadFromFile("buttons/hitbutton.png");
    stayButtonTex.loadFromFile("buttons/staybutton.png");
    backButtonTex.loadFromFile("buttons/backbutton.png");
    backgroundTexture = new sf::Texture();
    titleFont = new sf::Font();
    for (int i = 0; i < 49; i++) {
        playingCards[i]= new sf::Texture();
        playingCards[i]->loadFromFile("cards/"+std::to_string(i)+".png");
    }
    titleFont->loadFromFile("Albertson.ttf");
    backgroundTexture->loadFromFile("pokertable.jpg");
    VIDEOMODE.height = 600;
    VIDEOMODE.width = 800;
    WINDOWPTR = new sf::RenderWindow(VIDEOMODE, "Blackjack", sf::Style::Titlebar | sf::Style::Close);
    WINDOWPTR->setFramerateLimit(60);
}
/* SceneChangeCallHandler 
Checks if currentScene variables has declared any queuedSceneName.
If so, changes currentScene to queuedSceneName before the next game loop.
Usage of templates is avoided.
*/
void SceneChangeCallHandler() {
    if (currentSceneName != queuedSceneName) {
        delete currentScene;
        switch (queuedSceneName)
        {
        case SceneName::Game:
            currentScene = (Scene*)new GameScene();
            break;
        case SceneName::Menu:
            currentScene = (Scene*)new MenuScene();
        default:
            break;
        }
        queuedSceneName = SceneName::Null;
    }
}
void ProgramEnd() {
    delete currentScene;
    delete backgroundTexture;
    for (auto i : playingCards) {
        delete i;
    }
    delete cardShuffleBuffer;
}
void GlobalInputUpdate() {
    mousePosition = sf::Mouse::getPosition(*WINDOWPTR);
    Mouse0Pressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
    Mouse1Pressed = sf::Mouse::isButtonPressed(sf::Mouse::Right);
    while (WINDOWPTR->pollEvent(windowEvent)) {
        switch (windowEvent.type) {
        case sf::Event::Closed:
            WINDOWPTR->close();
            break;
        }
    }
}
//START OF PROGRAM
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow) {

    InitGlobalVariables();
    currentScene = (Scene*)new MenuScene();

    while (WINDOWPTR->isOpen())
    {
        GlobalInputUpdate();
        
        currentScene->update();
        currentScene->render();

        SceneChangeCallHandler(); 
    }
    ProgramEnd();
    return 0;
}
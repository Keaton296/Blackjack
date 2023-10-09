#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <thread>
using namespace std::chrono_literals;
using namespace sf;
Texture cards[12];
Texture acesOfHearts;
Font albertson;
Texture tableTex;
Text title;
Text quitText;
Text author;
RectangleShape card;
RectangleShape background;
bool mouseButtonHeld = false;
class Button : public RectangleShape {
    
};
void PrepareScene() {
    acesOfHearts.loadFromFile("acesofhearts.png");
    tableTex.loadFromFile("pokertable.jpg");
    albertson.loadFromFile("Albertson.ttf");
    background = RectangleShape(Vector2f(800, 600));
    background.setTexture(&tableTex, false);
    card = RectangleShape(Vector2f(256, 356));
    title.setFont(albertson);
    title.setString("Blackjack");
    title.setFillColor(Color::White);
    title.setOutlineColor(Color::Black);
    title.setOutlineThickness(5);
    title.setCharacterSize(100);
    title.setOrigin(200, 50);
    title.setPosition(400, 100);
    card.setFillColor(Color::White);
    author.setFont(albertson);
    author.setString("Kaan Dalkiran");
    author.setFillColor(Color::White);
    author.setOutlineColor(Color::Black);
    author.setOutlineThickness(2);
    author.setCharacterSize(30);
    author.setPosition(Vector2f(600, 560));
    quitText.setFont(albertson);
    quitText.setString("Quit");
    quitText.setFillColor(Color::White);
    quitText.setOutlineColor(Color::Black);
    quitText.setOutlineThickness(2);
    quitText.setCharacterSize(30);
    quitText.setPosition(Vector2f(350, 350));
    card.setOrigin(32, 44.5f);
    card.setTexture(&acesOfHearts, false);
    card.setPosition(100, 450);
    card.setRotation(25);
}
int main() {
	RenderWindow a(sf::VideoMode(800,600),"Blackjack");
    PrepareScene();
    while (a.isOpen())
    {
        Event event;
        while (a.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                a.close();
                return 0;
            }
        }
        a.clear(sf::Color::Black); //16711935
        a.draw(background);
        a.draw(card);
        a.draw(title);
        a.draw(author);
        a.draw(quitText);
        if (!mouseButtonHeld && Mouse::isButtonPressed(Mouse::Button::Left)) {
            mouseButtonHeld = true;
            if (quitText.getGlobalBounds().contains((Vector2f)sf::Mouse::getPosition(a))) {
                a.close();
                return 0;
            }
        }
        mouseButtonHeld = Mouse::isButtonPressed(Mouse::Button::Left);
        a.display();
        std::this_thread::sleep_for(16ms);
    }
    return 0;
}
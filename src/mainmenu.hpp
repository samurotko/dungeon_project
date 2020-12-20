#pragma once

#include "gamestate.hpp"
#include "button.hpp"

class MainMenu : public State
{
public:
    MainMenu(sf::RenderWindow *window, std::stack<State *> *states);
    virtual ~MainMenu();
    void update(const float &dt);
    void updateButtons();
    void renderButtons(sf::RenderTarget *target = nullptr);
    void render(sf::RenderTarget *target = nullptr);

    void createButtons();

private:
    sf::Sprite background;
    sf::Texture texture;
    sf::Font font;
    sf::Text text;
    sf::Music music;

    std::map<std::string, Button *> buttons;
};
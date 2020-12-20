#pragma once
#include "button.hpp"
class PauseMenu
{
public:
    PauseMenu(sf::RenderWindow &window, sf::Font &font);
    virtual ~PauseMenu();

    //get funktiot
    std::map<std::string, Button *> &GetButtons();

    //funktiot
    void addButton();
    const bool isButtonPressed(const std::string key);
    void update(const sf::Vector2f &mousePos);
    void render(sf::RenderTarget &target);

private:
    sf::RectangleShape background;
    sf::RectangleShape container;

    sf::Font &font;
    sf::Text pausemenu_text;

    std::map<std::string, Button *> buttons;
};
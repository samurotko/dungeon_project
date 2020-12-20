#include "pausemenu.hpp"

PauseMenu::PauseMenu(sf::RenderWindow &window, sf::Font &font)
    : font(font)
{
    //init font
    if (!this->font.loadFromFile("../Resources/fonts/PixellettersFull.ttf"))
        std::cout << "Could not load font." << std::endl;

    //init background
    this->background.setSize(
        sf::Vector2f(
            static_cast<float>(window.getSize().x),
            static_cast<float>(window.getSize().y)));

    this->background.setFillColor(sf::Color(20, 20, 20, 100));

    //init container
    this->container.setSize(
        sf::Vector2f(
            static_cast<float>(window.getSize().x) / 3.f,
            static_cast<float>(window.getSize().y)));

    this->container.setFillColor(sf::Color(20, 20, 20, 200));
    this->container.setPosition(static_cast<float>(window.getSize().x) / 2.f - this->container.getSize().x / 2.f, 0.f);

    //init text
    this->pausemenu_text.setFont(font);
    this->pausemenu_text.setFillColor(sf::Color(255, 255, 255, 200));
    this->pausemenu_text.setCharacterSize(80);
    this->pausemenu_text.setString("PAUSED");
    this->pausemenu_text.setPosition(
        this->container.getPosition().x + this->container.getSize().x / 2.f - this->pausemenu_text.getGlobalBounds().width / 2.f,
        this->container.getPosition().y + 40.f);
}

PauseMenu::~PauseMenu()
{
    auto it = this->buttons.begin();
    while (it != this->buttons.end())
    {
        delete it->second;
        it++;
    }
}

std::map<std::string, Button *> &PauseMenu::GetButtons()
{
    return this->buttons;
}

void PauseMenu::addButton()
{
    float x_coord = this->container.getPosition().x + this->container.getSize().x / 2.f - 125.f; // 125.f = width / 2

    this->buttons["CONTINUE"] = new Button(
        x_coord, 250.f, 250.f, 50.f, &this->font, "Continue",
        sf::Color(80, 80, 80, 200),
        sf::Color(100, 100, 100, 250),
        sf::Color(30, 30, 30, 200));

    this->buttons["QUIT"] = new Button(
        x_coord, 350.f, 250.f, 50.f, &this->font, "Quit",
        sf::Color(80, 80, 80, 200),
        sf::Color(100, 100, 100, 250),
        sf::Color(30, 30, 30, 200));
}

//funktiot
const bool PauseMenu::isButtonPressed(const std::string key)
{
    return this->buttons[key]->isPressed();
}

void PauseMenu::update(const sf::Vector2f &mousePos)
{
    for (auto &it : this->buttons)
    {
        it.second->update(mousePos);
    }
}

void PauseMenu::render(sf::RenderTarget &target)
{
    target.draw(background);
    target.draw(container);
    target.draw(pausemenu_text);

    for (auto &it : this->buttons)
    {
        it.second->render(&target);
    }
}
#include "mainmenu.hpp"
#include <SFML/Audio.hpp>

MainMenu::MainMenu(sf::RenderWindow *window, std::stack<State *> *states)
    : State(window, states)
{
    if (!this->font.loadFromFile("../Resources/fonts/PixellettersFull.ttf"))
        std::cout << "Could not load font." << std::endl;
    this->texture.loadFromFile("../Resources/textures/bg.jpg");
    this->background.setTexture(texture);
    if (MUSIC_ON)
    {
        this->music.openFromFile("../Resources/sounds/DarkWinds.OGG");
        music.play();
        music.setLoop(true);
    }

    this->createButtons();
    std::string title = "Dungeon Crawler";
    text.setFont(font);
    text.setFillColor(sf::Color::Yellow);
    text.setCharacterSize(200);
    text.setStyle(sf::Text::Style::Bold);
    text.setString(title);
    text.setPosition(WINDOW_WIDTH / 2 - text.getGlobalBounds().width / 2, 30);
}

MainMenu::~MainMenu()
{
    auto it = this->buttons.begin();
    while (it != this->buttons.end())
    {
        delete it->second;
        it++;
    }
}

void MainMenu::update(const float &dt)
{

    this->updateMousePos();

    this->updateButtons();
}

//p�ivitt�� buttonit ja niiden toiminnot
void MainMenu::updateButtons()
{
    auto it = this->buttons.begin();
    while (it != this->buttons.end())
    {
        it->second->update(this->mousePosView);
        it++;
    }

    //ty�nt�� gamestaten stackin p��llimm�iseksi(!)
    if (this->buttons["play"]->isPressed())
        this->states->push(new GameState(this->window, this->states));

    // Pause music
    if (MUSIC_ON)
    {
        if (this->buttons["play"]->isPressed())
            music.pause();
    }

    //this->exit();
    if (this->buttons["quit"]->isPressed())
        this->exit();
}

void MainMenu::renderButtons(sf::RenderTarget *target)
{
    auto it = this->buttons.begin();
    while (it != this->buttons.end())
    {
        it->second->render(target);
        it++;
    }
}

void MainMenu::render(sf::RenderTarget *target)
{
    if (!target)
        target = this->window;
    target->draw(this->background);
    target->draw(this->text);
    this->renderButtons(target);
    if (MUSIC_ON)
    {
        if (music.getStatus() == music.Paused)
            music.play();
    }
}

void MainMenu::createButtons()
{
    this->buttons["play"] = new Button(WINDOW_WIDTH / 2 - 75, 400, 150, 50, &this->font, "Play",
                                       sf::Color(80, 80, 80, 200),
                                       sf::Color(100, 100, 100, 250),
                                       sf::Color(30, 30, 30, 200));

    this->buttons["quit"] = new Button(WINDOW_WIDTH / 2 - 75, 700, 150, 50, &this->font, "Quit",
                                       sf::Color(80, 80, 80, 200),
                                       sf::Color(140, 100, 100, 250),
                                       sf::Color(30, 30, 30, 200));
}

#include "game.hpp"

Game::Game()
{
    this->initWindow();
    this->initStates();
}

Game::~Game()
{
    delete this->window;
    while (!this->states.empty())
    {
        delete this->states.top();
        this->states.pop();
    }
}

void Game::updateSFML()
{
    while (this->window->pollEvent(this->event))
    {
        if (this->event.type == sf::Event::Closed)
            this->window->close();
    }
}

void Game::updateDt()
{
    this->dt = this->dtClock.restart().asSeconds();
}

void Game::update()
{
    this->updateSFML();
    if (!this->states.empty())
    {
        if (this->window->hasFocus())
        {
            this->states.top()->update(this->dt);
            if (this->states.top()->hasQuit())
            {
                this->states.top()->exit();
                delete this->states.top();
                this->states.pop();
            }
        }
    }
    else
    {
        this->window->close();
    }
}

void Game::render()
{
    this->window->clear();
    if (!this->states.empty())
        this->states.top()->render(this->window);

    this->window->display();
}

void Game::run()
{
    while (this->window->isOpen())
    {
        this->updateDt();
        this->update();
        this->render();
    }
}

void Game::initWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Slapper Dungeon Crawler", WINDOW_STYLE);
}

void Game::initStates()
{
    this->states.push(new MainMenu(this->window, &this->states));
}
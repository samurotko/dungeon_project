#pragma once

#include "mainmenu.hpp"

class Game
{
public:
    Game();
    virtual ~Game();

    void updateSFML();
    void updateDt();
    void update();
    void render();
    void run();

private:
    sf::RenderWindow *window;
    sf::Event event;

    /* DeltaTime should be used, when you want movement or any other constant variable change,
    to be the same speed, no matter the framerate.
    DeltaTime is the time between the last and current frame. */
    sf::Clock dtClock;
    float dt;

    // Stack of states, Main menu adds new gamestate on top
    std::stack<State *> states;

    // Initialisoi näytettävän ikkunan ja game statet
    void initWindow();
    void initStates();
};
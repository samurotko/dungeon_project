#pragma once

#include "player.hpp"

/* Game State, adventure view, combat screen etc. */
class State
{
public:
    State(sf::RenderWindow *window, std::stack<State *> *states);
    virtual ~State();
    const bool &hasQuit() const;

    void exit();
    virtual void update(const float &dt) = 0;
    virtual void updateMousePos();
    virtual void render(sf::RenderTarget *target = nullptr) = 0;

    virtual void updatekeytime(const float &dt);
    void pauseState();
    void unpauseState();

    const bool getKeytime();

protected:
    //pointteri game.hpp:n state stackkiin, tapa muokata stateja muista stateista, ks. esim.
    //mainmenu -> updateButtons -> play, joka ty�nt�� peli-ikkunan p��llimm�iseksi
    std::stack<State *> *states;
    sf::RenderWindow *window;
    std::map<std::string, sf::Texture> textures;
    bool quit;
    sf::View view;

    bool paused;
    float Keytime;
    float KeytimeMax;

    //hiiren sijainti
    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

private:
};
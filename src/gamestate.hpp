#pragma once

#include "state.hpp"
#include "pausemenu.hpp"

class GameState : public State
{
public:
    GameState(sf::RenderWindow *window, std::stack<State *> *states);
    virtual ~GameState();

    void UpdatePaused(const float &dt);
    void UpdatePauseMenuButtons();
    void updateDt();
    void updatePlayer(const float &dt);
    void updateEnemies(const float &dt);
    //void updateCollision(const float& dt);
    void update(const float &dt);
    void render(sf::RenderTarget *target = nullptr);

protected:
    void initFonts();
    void InitPauseMenu();
    
    std::list<Enemy *> enemies;
    std::list<Item *> mapitems;
    Player player;
    TileMap tilemap;
    TextureMap texturemap;
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;
    float timer = 2;

    PauseMenu *pausemenu;
    sf::Clock dtClock;
    float dt;

    sf::Font font;
    sf::Text winText;
    sf::Text hpText;
    sf::Text potText;

    sf::SoundBuffer buffer;
    sf::Sound sound;

private:
    void initRenderTexture();
    void initView();
    void initText();
};

#pragma once

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <stack>
#include <ctime>
#include <cmath>
#include <list>
#include <iterator>

#include "common.hpp"
#include "hitbox.hpp"
#include "move.hpp"
#include "animation.hpp"
#include "sword.hpp"
#include "armor.hpp"
#include "tilemap.hpp"
#include "texturemap.hpp"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

//class TileMap;

class Entity
{
public:
    Entity();
    virtual ~Entity();

    // Getters
    bool isAlive();

    //sf::FloatRect getNextPosBounds(const float& dt);
    sf::Vector2f getPosition();
    float getHp();
    int getKnockBack();
    int getFacing();
    //Hitbox getHitbox();

    // Setters
    int tileIndex(sf::Vector2f pos);
    sf::Vector2f getCoords(sf::Vector2f pos);
    void decreaseHp();
    void decreaseHp(float mod);
    void setKnockBack(int dir);
    void setPos(const float x, const float y);

    virtual void move(const float &dt, const float x, const float y) = 0;
    virtual void updateCollision(TileMap &tilemap, const float &dt) = 0;
    virtual void update(const float &dt) = 0;
    virtual void render(sf::RenderTarget *target) = 0;

protected:
    sf::RectangleShape shape;
    float movementSpeed;
    sf::Sprite sprite;
    sf::Texture texture;
    //Hitbox *hitbox;
    Move *movement;

    int walkingdir;
    int facing;
    int knockBack;

    // STATS
    float maxHP;
    float hitpoints;

private:
};
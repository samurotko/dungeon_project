#include "entity.hpp"
#include <cmath>

Entity::Entity()
{
}

Entity::~Entity()
{
}

// Getters

bool Entity::isAlive()
{
    if (this->getHp() > 0)
        return true;
    else
        return false;
}

sf::Vector2f Entity::getPosition()
{
    return this->sprite.getPosition();
}

float Entity::getHp()
{
    return this->hitpoints;
}

int Entity::getKnockBack()
{
    return this->knockBack;
}

int Entity::getFacing()
{
    return this->facing;
}

// Functions

//tilen sijainti lukuna vasemmasta yl�kulmasta
int Entity::tileIndex(sf::Vector2f pos)
{

    int x = floor(pos.x / TILE_SIZE);
    int y = floor(pos.y / TILE_SIZE);

    int index = MAP_WIDTH * (y - 1) + x - 1;
    /*if ((x < MAP_WIDTH && x >= 0) &&
        (y < MAP_HEIGHT && y >= 0))*/
    return MAP_WIDTH * (y - 1) + x;
}
//muuttaa sijainnin tile sijainniksi
sf::Vector2f Entity::getCoords(sf::Vector2f pos)
{
    float x = this->tileIndex(pos) % MAP_WIDTH;
    float y = (this->tileIndex(pos) - this->tileIndex(pos) % MAP_WIDTH) / MAP_HEIGHT;
    return sf::Vector2f(this->tileIndex(pos) % MAP_WIDTH,
                        ((this->tileIndex(pos) - (this->tileIndex(pos) % MAP_WIDTH)) / MAP_WIDTH) + 1);
}

void Entity::decreaseHp()
{
    if (this->getHp() - 1 > 0)
        this->hitpoints = this->hitpoints - 1;
    else
        this->hitpoints = 0;
}

void Entity::setKnockBack(int dir)
{
    this->knockBack = dir;
}

void Entity::decreaseHp(float mod)
{
    if (this->getHp() - mod > 0)
        this->hitpoints = this->hitpoints - mod;
    else
        this->hitpoints = 0;
}

void Entity::setPos(const float x, const float y)
{
    this->sprite.setPosition(sf::Vector2f(x, y));
}

void Entity::move(const float &dt, const float dir_x, const float dir_y)
{
}

void Entity::updateCollision(TileMap &tilemap, const float &dt)
{
}

void Entity::update(const float &dt)
{
}

void Entity::render(sf::RenderTarget *target)
{
}
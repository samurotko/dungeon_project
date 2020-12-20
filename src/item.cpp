#include "item.hpp"
Item::Item(std::string type, const float x, const float y) : type_(type)
{
    setPos(x * TILE_SIZE, y * TILE_SIZE);
    if (type_ == "potion")
    {
        this->texture.loadFromFile("../Resources/textures/potion.png");
        this->sprite.setTexture(texture);
    }
}
Item::Item() {}
Item::~Item()
{
}

sf::Sprite Item::getSprite()
{
    return this->sprite;
}

sf::Vector2f Item::getPosition()
{
    return this->sprite.getPosition();
}

void Item::setPos(const float x, const float y)
{
    this->sprite.setPosition(sf::Vector2f(x, y));
}

void Item::update(const float &dt)
{
}

void Item::render(sf::RenderTarget *target)
{
}

std::string Item::getType() const
{
    return type_;
}
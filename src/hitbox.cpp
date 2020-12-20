#include "hitbox.hpp"

Hitbox::Hitbox(sf::Sprite &sprite, float offset_x, float offset_y, float width, float height)
    : sprite(sprite), offset_x(offset_x), offset_y(offset_y)
{
    //this->sprite = sprite;
    this->offset_X = offset_x;
    this->offset_Y = offset_y;
    this->hitbox.setPosition(this->sprite.getPosition().x + offset_x, this->sprite.getPosition().y + offset_y);
    this->hitbox.setSize(sf::Vector2f(width, height));
    this->hitbox.setFillColor(sf::Color::Transparent);
    this->hitbox.setOutlineColor(sf::Color::Cyan);
    this->hitbox.setOutlineThickness(-1.f);

    this->nextPos.left = 0.f;
    this->nextPos.top = 0.f;
    this->nextPos.width = width;
    this->nextPos.height = height;
}

Hitbox::~Hitbox()
{
}
void Hitbox::update()
{
    this->hitbox.setPosition(this->sprite.getPosition().x + offset_X, this->sprite.getPosition().y + offset_Y);
}
void Hitbox::render(sf::RenderTarget &target)
{
    // target.draw(this->hitbox);
}
bool Hitbox::checkIntersect(const sf::FloatRect &frect)
{
    return this->hitbox.getGlobalBounds().intersects(frect);
}

sf::FloatRect Hitbox::getGlobalBounds()
{
    return this->hitbox.getGlobalBounds();
}

sf::Vector2f Hitbox::getPosition()
{
    return this->hitbox.getPosition();
}

sf::FloatRect &Hitbox::getNextPosition(const sf::Vector2f &velocity)
{
    this->nextPos.top = this->hitbox.getPosition().y + velocity.y;
    this->nextPos.left = this->hitbox.getPosition().x + velocity.x;
    return this->nextPos;
}

void Hitbox::setPos(sf::Vector2f position)
{
    this->hitbox.setPosition(position);
    this->sprite.setPosition(this->hitbox.getPosition().x - offset_x, this->hitbox.getPosition().y - offset_y);
}

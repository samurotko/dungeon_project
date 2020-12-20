#include "sword.hpp"

Sword::Sword(/* const float x, const float y */)
{
    this->texture.loadFromFile("../Resources/textures/sword.png");
    this->sprite.setTexture(texture);
    this->sprite.setTextureRect(sf::IntRect(0, 192, 192, 192)); // 1152x768
    this->setPos(15 * TILE_SIZE, 3 * TILE_SIZE);
    this->first = Animation(0, 348, 192, 192, 1);
    this->stillUp = Animation(0, 0, 192, 192, 1);
    this->stillLeft = Animation(0, 192, 192, 192, 1);
    this->stillDown = Animation(0, 384, 192, 192, 1);
    this->stillRight = Animation(0, 576, 192, 192, 1);
    this->hitUp = Animation(0, 0, 192, 192, 6);
    this->hitLeft = Animation(0, 192, 192, 192, 6);
    this->hitDown = Animation(0, 384, 192, 192, 6);
    this->hitRight = Animation(0, 576, 192, 192, 6);
    this->range = 64;
    this->damage = 2;
}

Sword::~Sword()
{
}

void Sword::update(const float &dt)
{
    curAnimation.Update(dt);
    curAnimation.ApplyToSprite(sprite);
}
void Sword::render(sf::RenderTarget *target)
{
    target->draw(this->sprite);
}

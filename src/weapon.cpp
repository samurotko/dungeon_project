#include "weapon.hpp"

Weapon::Weapon()
{
}
Weapon::~Weapon()
{
}
void Weapon::update(const float &dt)
{
}
void Weapon::render(sf::RenderTarget *target)
{
}
void Weapon::setCurAnimation(std::string animationName)
{
    if (animationName == "stillUp")
        this->curAnimation = stillUp;
    if (animationName == "stillLeft")
        this->curAnimation = stillLeft;
    if (animationName == "stillDown")
        this->curAnimation = stillDown;
    if (animationName == "stillRight")
        this->curAnimation = stillRight;
    if (animationName == "hitUp")
        this->curAnimation = hitUp;
    if (animationName == "hitLeft")
        this->curAnimation = hitLeft;
    if (animationName == "hitDown")
        this->curAnimation = hitDown;
    if (animationName == "hitRight")
        this->curAnimation = hitRight;
}

int Weapon::getRange()
{
    return this->range;
}

int Weapon::getDamage()
{
    return this->damage;
}
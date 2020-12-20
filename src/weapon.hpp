#pragma once
#include "item.hpp"

class Weapon : public Item
{
public:
    Weapon();
    virtual ~Weapon();
    virtual void update(const float &dt);
    virtual void render(sf::RenderTarget *target);
    void setCurAnimation(std::string animationName);
    int getRange();
    int getDamage();

protected:
    Animation first, stillUp, stillRight, stillLeft, stillDown, hitUp, hitRight, hitLeft, hitDown;
    Animation &curAnimation = first;
    int range, damage;
};
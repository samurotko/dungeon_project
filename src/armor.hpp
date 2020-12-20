#pragma once
#include "item.hpp"

class Armor : public Item
{
public:
    Armor(std::string type);
    virtual ~Armor();
    virtual void update(const float &dt);
    virtual void render(sf::RenderTarget *target);
    void setCurAnimation(std::string animationName);
    int getProtection();
    void changeTexture(std::string type);

private:
    Animation upWalk, leftWalk, downWalk, rightWalk, firstAnimation, hitUp,
        hitDown, hitLeft, hitRight, stillLeft, stillRight, stillDown, stillUp, dead;
    Animation &curAnimation = firstAnimation;
    int protection = 0;
};
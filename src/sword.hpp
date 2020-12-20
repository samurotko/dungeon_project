#pragma once
#include "weapon.hpp"

//Keskeneräinen
class Sword : public Weapon
{
public:
    Sword();
    virtual ~Sword();
    virtual void update(const float &dt);
    virtual void render(sf::RenderTarget *target);

protected:
};
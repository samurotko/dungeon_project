#pragma once

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <stack>
#include <ctime>
#include "animation.hpp"

#include "common.hpp"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

//Swordia varten nopeasti luotu. Saa muokkailla tarvittaessa
class Item
{
public:
    Item(std::string type, const float x, const float y);
    Item();
    virtual ~Item();

    sf::Sprite getSprite();
    sf::Vector2f getPosition();
    void setPos(const float x, const float y);
    virtual void update(const float &dt);
    virtual void render(sf::RenderTarget *target);
    std::string getType() const;

protected:
    sf::RectangleShape shape;
    sf::Sprite sprite;
    sf::Texture texture;
    std::string type_;
};
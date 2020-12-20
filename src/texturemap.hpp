#pragma once
#include "entity.hpp"
class TextureMap
{
public:
    TextureMap();
    virtual ~TextureMap();
    void render(sf::RenderTarget *target);

private:
    sf::Vector2i map[100][100];
    sf::Vector2i loadCounter;
    sf::Sprite sprites;
    sf::Texture tileTextures;
};

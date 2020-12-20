#pragma once
#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include "tile.hpp"

//#include "entity.hpp"

class TileMap
{
public:
    TileMap();
    virtual ~TileMap();

    std::map<int, Tile *> getTiles();
    void render(sf::RenderTarget *target);
    void createTiles();
    int tileIndex(sf::Vector2f pos);

private:
    sf::Vector2i map[100][100];
    sf::Vector2i loadCounter;
    sf::Sprite sprites;
    sf::Texture tileTextures;

    unsigned fromX;
    unsigned toX;
    unsigned fromY;
    unsigned toY;

    std::map<int, Tile *> tiles; //int on tileposition vasemmasta yl�kulmasta
    sf::RectangleShape collision;
};

#endif // !TILEMAP_HPP
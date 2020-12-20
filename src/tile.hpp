#pragma once
#ifndef TILE_HPP
#define TILE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

#include "common.hpp"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

//#include "entity.hpp"

/* 
kertoo tilen positionin pikselein� ja canWalk -arvon
*/
class Tile
{
public:
	Tile(int x, int y, bool canWalk, sf::Sprite sprite);

	Tile(int x, int y, bool canWalk);

	~Tile();

	bool getCanWalk();

	const bool intesect(const sf::FloatRect bounds) const;

	sf::Vector2f &getPos();

	sf::Sprite getSprite();
	sf::FloatRect getBounds();

protected:
	bool canWalk;
	sf::Vector2f position;
	sf::RectangleShape bounds;
	sf::Sprite sprite;

private:
};

#endif
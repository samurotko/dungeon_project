#include "tile.hpp"

Tile::Tile(int x, int y, bool canWalk, sf::Sprite sprite)
{
	this->canWalk = canWalk;
	this->position = sf::Vector2f(x, y);
	this->bounds = sf::RectangleShape(this->position);
	this->sprite = sprite;

	/*if (y >= 6 && y <= 8) {
		
		this->canWalk=false;
	}
	else {
		this->canWalk=true;
	}*/
}

Tile::Tile(int x, int y, bool canWalk)
{
	this->canWalk = canWalk;
	this->position = sf::Vector2f(x, y);
	this->bounds = sf::RectangleShape(this->position);
}

Tile::~Tile()
{
}

sf::Vector2f &Tile::getPos()
{
	return this->position;
}

sf::Sprite Tile::getSprite()
{
	return this->sprite;
}

sf::FloatRect Tile::getBounds()
{
	return this->sprite.getGlobalBounds();
}

bool Tile::getCanWalk()
{

	return this->canWalk;
}

const bool Tile::intesect(const sf::FloatRect bounds) const
{
	return this->sprite.getGlobalBounds().intersects(bounds);
	/*sf::FloatRect rect = this->sprite.getGlobalBounds();
	bool topRight = rect.contains(bounds.left + bounds.width, bounds.top);
	bool topLeft = rect.contains(bounds.left, bounds.top);
	bool bottomRight = rect.contains(bounds.left + bounds.width, bounds.top + bounds.height);
	bool bottomLeft = rect.contains(bounds.left, bounds.top + bounds.height);
	bool intersects;
	sf::Vector2f tilepos = this->position;

	if (topLeft + topRight + bottomLeft + bottomRight>0)
		intersects = true;
	else
		intersects = false;

	return intersects;*/
}

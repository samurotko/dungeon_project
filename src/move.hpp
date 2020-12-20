#pragma once
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <stack>
#include <ctime>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

class Move
{
public:
	Move(sf::Sprite &sprite, float maxVelocity, float acceleration, float deceleration);

	~Move();

	const sf::Vector2f &getVelocity() const;

	void stop();
	void stopX();
	void stopY();

	void update(const float &dt);
	void move(const float dir_x, const float dir_y, const float &dt);

private:
	float maxVelocity;
	float acceleration;
	float deceleration;

	sf::Sprite &sprite;
	sf::Vector2f velocity;
};

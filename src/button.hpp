#pragma once
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <ctime>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

// Button States
enum states
{
	idle = 0,
	hover,
	pressed
};

class Button
{

public:
	Button(float x, float y, float width, float height, sf::Font *font, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);

	~Button();

	const bool isPressed() const;

	const bool isHover() const;

	void render(sf::RenderTarget *t);

	void update(const sf::Vector2f mousePos);

private:
	int state; //enum states type
	sf::RectangleShape shape;
	sf::Font *font;
	sf::Text text;
	sf::Color activeColor;
	sf::Color hoverColor;
	sf::Color idleColor;
};
#pragma once

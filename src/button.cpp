#include "button.hpp"

//x, y, leveys, korkeus, fontti, teksti, idlecolor, hovercolor, activecolor
Button::Button(float x, float y, float width, float height, sf::Font *font, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{

	this->state = idle;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::Yellow);
	this->text.setCharacterSize(50);
	//sijoittaa tekstin keskelle buttonia
	this->text.setPosition(this->shape.getPosition().x + this->shape.getGlobalBounds().width / 2.f - this->text.getGlobalBounds().width / 2.f,
						   this->shape.getPosition().y - this->shape.getGlobalBounds().height / 2.f + this->text.getGlobalBounds().height / 2.f);

	this->idleColor = idleColor;
	this->activeColor = hoverColor;
	this->activeColor = activeColor;
	this->shape.setFillColor(this->idleColor);
}

Button::~Button()
{
}

const bool Button::isPressed() const
{
	if (this->state == pressed)
		return true;
	return false;
}

const bool Button::isHover() const
{
	if (this->state == hover)
		return true;
	return false;
}

void Button::render(sf::RenderTarget *t)
{
	t->draw(this->shape);
	t->draw(this->text);
}

void Button::update(const sf::Vector2f mousePos)
{
	this->state = idle;

	// mouse over
	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		this->state = hover;

		//jos klikattu
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->state = pressed;
		}
	}

	switch (this->state)
	{
	case idle:
		this->shape.setFillColor(this->idleColor);
		break;

	case hover:
		this->shape.setFillColor(this->hoverColor);
		break;

	case pressed:
		this->shape.setFillColor(this->activeColor);
		break;
	default:
		this->shape.setFillColor(sf::Color::Red);
		break;
	}
}

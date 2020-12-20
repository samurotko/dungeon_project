#include "move.hpp"

Move::Move(sf::Sprite &sprite, float maxVelocity, float acceleration, float deceleration) : sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{
}

Move::~Move()
{
}

const sf::Vector2f &Move::getVelocity() const
{
	return this->velocity;
}

void Move::stop()
{
	this->velocity.x = 0.f;
	this->velocity.y = 0.f;
}

void Move::stopX()
{
	this->velocity.x = 0.f;
}

void Move::stopY()
{
	this->velocity.y = 0.f;
}

void Move::update(const float &dt)
{
	//kiihtyvyydet
	if (this->velocity.x > 0.f)
	{

		if (this->velocity.x > this->maxVelocity)
			this->velocity.x = maxVelocity;

		this->velocity.x -= deceleration;
		if (this->velocity.x < 0.f)
			this->velocity.x = 0.f;
	}
	else if (this->velocity.x < 0.f)
	{

		if (this->velocity.x < -this->maxVelocity)
			this->velocity.x = -maxVelocity;

		this->velocity.x += deceleration;
		if (this->velocity.x > 0.f)
			this->velocity.x = 0.f;
	}

	if (this->velocity.y > 0.f)
	{

		if (this->velocity.y > this->maxVelocity)
			this->velocity.y = maxVelocity;

		this->velocity.y -= deceleration;
		if (this->velocity.y < 0.f)
			this->velocity.y = 0.f;
	}
	else if (this->velocity.y < 0.f)
	{

		if (this->velocity.y < -this->maxVelocity)
			this->velocity.y = -maxVelocity;

		this->velocity.y += deceleration;
		if (this->velocity.y > 0.f)
			this->velocity.y = 0.f;
	}

	//liikuttaminen
	this->sprite.move(this->velocity * dt);
}

void Move::move(const float dir_x, const float dir_y, const float &dt)
{
	this->velocity.x += dir_x * acceleration;

	this->velocity.y += dir_y * acceleration;
}

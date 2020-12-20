#include "animation.hpp"

Animation::Animation(int x, int y, int width, int height, int numOfFrames)
{
    this->numOfFrames = numOfFrames;
    this->y = y;
    for (int i = 0; i < numOfFrames; i++)
    {
        sf::IntRect newFrame = sf::IntRect{x + i * width, y, width, height};
        frames.push_back(newFrame);
    }
}

Animation::~Animation()
{
}

void Animation::ApplyToSprite(sf::Sprite &s)
{
    s.setTextureRect(frames[curFrame]);
}

void Animation::Update(float dt)
{
    wholeTime += dt;
    time += dt;
    while (time >= holdTime)
    {
        time -= holdTime;
        Advance();
    }
}

void Animation::Advance()
{
    if (++curFrame >= numOfFrames)
    {
        curFrame = 0;
    }
}

float Animation::getWholeTime()
{
    return this->wholeTime;
}
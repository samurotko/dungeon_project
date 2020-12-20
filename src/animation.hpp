#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Animation
{
public:
    Animation() = default;
    Animation(int x, int y, int width, int height, int numOfFrames);
    ~Animation();

    void ApplyToSprite(sf::Sprite &s);
    void Update(float dt);
    float getWholeTime();
    int y;

private:
    void Advance();

private:
    float wholeTime = 0.0f;
    float time = 0.0f;
    int numOfFrames;
    std::vector<sf::IntRect> frames;
    int curFrame = 0;
    float holdTime = 0.1f;
};
#include "armor.hpp"

Armor::Armor(std::string type)
{
    if (type == "plate")
    {
        this->texture.loadFromFile("../Resources/textures/half_plate.png");
        protection = 5;
    }
    else if (type == "leather")
    {
        this->texture.loadFromFile("../Resources/textures/leather.png");
        protection = 3;
    }
    else if (type == "cloth")
    {
        this->texture.loadFromFile("../Resources/textures/cloth.png");
        protection = 1;
    }
    else if (type == "robes")
    {
        this->texture.loadFromFile("../Resources/textures/gray_robes.png");
        protection = 3;
        this->sprite.setColor(sf::Color(0, 0, 0, 200));
    }
    else if (type == "chain")
    {
        this->texture.loadFromFile("../Resources/textures/chain.png");
        protection = 5;
        this->sprite.setColor(sf::Color(20, 20, 50, 230));
    }
    else
        std::cout << "/n wrong armor type   " << type << std::endl;

    this->sprite.setTexture(texture);
    this->sprite.setTextureRect(sf::IntRect(0, 128, 64, 64));
    this->upWalk = Animation(64, 512, 64, 64, 8);
    this->leftWalk = Animation(64, 576, 64, 64, 8);
    this->downWalk = Animation(64, 640, 64, 64, 8);
    this->rightWalk = Animation(64, 704, 64, 64, 8);
    this->firstAnimation = Animation(0, 640, 64, 64, 1);
    this->hitUp = Animation(0, 768, 64, 64, 6);
    this->hitRight = Animation(0, 960, 64, 64, 6);
    this->hitDown = Animation(0, 896, 64, 64, 6);
    this->hitLeft = Animation(0, 832, 64, 64, 6);
    this->stillUp = Animation(0, 512, 64, 64, 1);
    this->stillLeft = Animation(0, 576, 64, 64, 1);
    this->stillDown = Animation(0, 640, 64, 64, 1);
    this->stillRight = Animation(0, 704, 64, 64, 1);
    this->dead = Animation(5 * 64, 20 * 64, 64, 64, 1);
}
Armor::~Armor() {}
void Armor::update(const float &dt)
{
    curAnimation.Update(dt);
    curAnimation.ApplyToSprite(sprite);
}
void Armor::render(sf::RenderTarget *target)
{
    target->draw(this->sprite);
}

void Armor::setCurAnimation(std::string AnimationName)
{
    if (AnimationName == "upWalk")
        this->curAnimation = upWalk;
    else if (AnimationName == "downWalk")
        this->curAnimation = downWalk;
    else if (AnimationName == "leftWalk")
        this->curAnimation = leftWalk;
    else if (AnimationName == "rightWalk")
        this->curAnimation = rightWalk;
    else if (AnimationName == "hitUp")
        this->curAnimation = hitUp;
    else if (AnimationName == "hitLeft")
        this->curAnimation = hitLeft;
    else if (AnimationName == "hitRight")
        this->curAnimation = hitRight;
    else if (AnimationName == "hitDown")
        this->curAnimation = hitDown;
    else if (AnimationName == "stillUp")
        this->curAnimation = stillUp;
    else if (AnimationName == "stillDown")
        this->curAnimation = stillDown;
    else if (AnimationName == "stillLeft")
        this->curAnimation = stillLeft;
    else if (AnimationName == "stillRight")
        this->curAnimation = stillRight;
    else if (AnimationName == "dead")
        this->curAnimation = dead;

    else
        std::cout << "/n wrong animation name:   " << AnimationName << std::endl;
}

int Armor::getProtection()
{
    return this->protection;
}

void Armor::changeTexture(std::string type)
{
    if (type == "plate")
    {
        this->texture.loadFromFile("../Resources/textures/half_plate.png");
        protection = 5;
    }
    else if (type == "leather")
    {
        this->texture.loadFromFile("../Resources/textures/leather.png");
        protection = 3;
    }
    else if (type == "cloth")
    {
        this->texture.loadFromFile("../Resources/textures/cloth.png");
        protection = 1;
    }
    else if (type == "robes")
    {
        this->texture.loadFromFile("../Resources/textures/gray_robes.png");
        protection = 3;
        this->sprite.setColor(sf::Color(0, 0, 0, 200));
    }
    else if (type == "chain")
    {
        this->texture.loadFromFile("../Resources/textures/chain.png");
        protection = 5;
        this->sprite.setColor(sf::Color(20, 20, 50, 230));
    }
    else
        std::cout << "/n wrong armor type   " << type << std::endl;
    this->sprite.setTexture(texture);
}

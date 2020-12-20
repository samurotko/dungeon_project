#include <SFML/Graphics.hpp>

//keskeneräinen versio
class Hitbox
{
public:
    Hitbox(sf::Sprite &sprite, float offset_x, float offset_y, float width, float height);
    ~Hitbox();
    sf::FloatRect getGlobalBounds();
    sf::Vector2f getPosition();
    sf::FloatRect &getNextPosition(const sf::Vector2f &velocity);

    void setPos(sf::Vector2f position);

    void update();
    void render(sf::RenderTarget &target);
    bool checkIntersect(const sf::FloatRect &frect);

private:
    float offset_x;
    float offset_y;
    sf::RectangleShape hitbox;
    sf::FloatRect nextPos;
    sf::Sprite &sprite;
    float offset_X, offset_Y;
};
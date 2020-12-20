#pragma once
#include "entity.hpp"

class Player;

class Enemy : public Entity
{
public:
    Enemy(int x, int y, std::string armor, std::string weapon, int hp);
    Enemy(int x, int y, std::string armor, std::string weapon, int hp, int facingdir);
    virtual ~Enemy();

    // Getters
    float getAnimationTime();
    int getFacing();
    int getAttackRange();
    bool isIdle();
    bool isCollision();
    bool isAttacking();
    bool canAttack();
    bool isInRange(Player *pl, int dir, int range);
    sf::FloatRect getNextPosBounds(const float &dt);
    Hitbox *getHitbox();

    // Functions
    void setWalkingDir(int dir);
    void setIdle(int i);
    virtual void move(const float &dt, const float x, const float y);
    void stopVelocity();
    void stopVelocityX();
    void stopVelocityY();

    void setAnimation(int facing);
    void stop();
    void getHit(float amount, int dir);
    void attack(Player *player);
    void hitPlayer();
    virtual void updateCollision(TileMap &tilemap, const float &dt);
    virtual void update(const float &dt);
    virtual void render(sf::RenderTarget *target);

protected:
    bool collision;
    bool idle = true;

    // Animation components
    Animation upWalk, leftWalk, downWalk, rightWalk, still, firstAnimation;
    Animation &curAnimation = firstAnimation;

    Player *aPlayer;
    Hitbox *hitbox;

    // Millä etäisyyydellä pelaajasta vihollinen hyökkää
    int attackRange;

    // Enemy inventory
    Weapon *curWeapon = nullptr;
    Armor *curArmor = nullptr;

private:
    void initEnemy();
    void initTextures();
    void initAnimation();

    void setMovement(const float maxSpeed, const float acceleration, const float deceleration);
};
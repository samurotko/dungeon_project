#pragma once
#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "entity.hpp"
#include "enemy.hpp"

class Player : public Entity
{
public:
    Player();
    virtual ~Player();

    void getXp();
    void setPos(const float x, const float y);

    virtual void updateCollision(TileMap &tilemap, const float &dt);

    sf::Sprite getSprite();
    Hitbox *getHitbox();
    sf::FloatRect getNextPosBounds(const float &dt);
    sf::Vector2f getVelocity();
    std::vector<Item *> getInventory();
    bool isIdle();
    bool isCollision();
    bool canAttack();
    bool isAttacking();
    bool isInRange(Enemy *en, int dir, int range);

    // Functions
    void storeItem(Item *item);
    void usePotion();
    virtual void move(const float &dt, const float x, const float y);

    void updateHPBar();
    virtual void update(const float &dt);
    virtual void render(sf::RenderTarget *target);

    void setAnimation(int facing);
    void setWalkingDir(int dir);
    void setMovement(const float maxSpeed, const float acceleration, const float deceleration);
    void stop();
    void attack();
    void hitEnemy(std::list<Enemy *> enemies);
    void stopVelocity();
    void stopVelocityX();
    void stopVelocityY();
    void getHit(float amount, int dir);

protected:
    bool isHitting = false;

    // Animation components
    Animation upWalk, leftWalk, downWalk, rightWalk, still, firstAnimation;
    Animation &curAnimation = firstAnimation;
    Hitbox *hitbox;
    Move *movement;

    //TileMap map;

    sf::FloatRect nextTile;
    bool collision;

    sf::RectangleShape collisionBox; // tarpeellinen jos entityll� on hitbox?

    // Player inventory
    std::vector<Item *> items;
    Weapon *curWeapon = nullptr;
    Armor *curArmor = nullptr;
    int xp = 0;

    //HPbar
    float maxSizeHPBar;
    sf::Font font;
    sf::RectangleShape hpBarBack;
    sf::RectangleShape hpBarInside;

    //sound
    sf::SoundBuffer buffer;
    sf::Sound sound;
    sf::SoundBuffer hitbuffer;
    sf::Sound hitsound;
    sf::SoundBuffer damagebuffer;
    sf::Sound damagesound;

private:
    void initPlayer();
    void initTextures();
    void initAnimation();
    void initHPBar();
};
#endif
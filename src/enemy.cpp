#include "enemy.hpp"
#include "player.hpp"

Enemy::Enemy(int x, int y, std::string armor, std::string weapon, int hp)
{
    this->hitbox = new Hitbox(this->sprite, 15.f, 15.f, 34.f, 47.f);
    initTextures();
    initEnemy();
    this->setPos(x * TILE_SIZE, y * TILE_SIZE);
    initAnimation();
    this->setMovement(100.f, 15.f, 12.f);
    this->hitpoints = hp;

    if (armor == "chain" || armor == "leather" || armor == "robes")
        this->curArmor = new Armor(armor);
    if (weapon == "sword")
        this->curWeapon = new Sword();
    this->sprite.setColor(sf::Color(0, 125, 0, 150));
}
Enemy::Enemy(int x, int y, std::string armor, std::string weapon, int hp, int facingdir)
{
    this->hitbox = new Hitbox(this->sprite, 15.f, 15.f, 34.f, 47.f);
    initTextures();
    initEnemy();
    this->setPos(x * TILE_SIZE, y * TILE_SIZE);
    initAnimation();
    this->setMovement(100.f, 15.f, 12.f);
    this->hitpoints = hp;
    this->facing = facingdir;

    if (armor == "chain" || armor == "leather" || armor == "robes")
        this->curArmor = new Armor(armor);
    if (weapon == "sword")
        this->curWeapon = new Sword();
}

Enemy::~Enemy()
{
    delete this->hitbox;
    delete this->curWeapon;
    delete this->curArmor;
    delete this->movement;
}

// Inits

// Sets position hp etc.
void Enemy::initEnemy()
{
    this->facing = 3;
    // this->movementSpeed = 150.f;
    this->collision = false;
    this->attackRange = 64;
}

void Enemy::initTextures()
{
    this->texture.loadFromFile("../Resources/textures/npc.png");
    this->sprite.setTexture(texture);
    this->sprite.setTextureRect(sf::IntRect(0, 128, 64, 64)); // 832x1344
    this->sprite.setColor(sf::Color(0, 125, 0, 150));
}

void Enemy::initAnimation()
{
    this->upWalk = Animation(64, 0, 64, 64, 8);
    this->leftWalk = Animation(64, 64, 64, 64, 8);
    this->downWalk = Animation(64, 128, 64, 64, 8);
    this->rightWalk = Animation(64, 192, 64, 64, 8);
    this->still = Animation(0, 640, 64, 64, 1);
    this->firstAnimation = Animation(0, 640, 64, 64, 1);
}

void Enemy::setMovement(const float maxSpeed, const float acceleration, const float deceleration)
{
    this->movement = new Move(this->sprite, maxSpeed, acceleration, deceleration);
}

void Enemy::getHit(float amount, int dir)
{
    if (this->curArmor != nullptr)
        amount = amount / this->curArmor->getProtection();
    this->decreaseHp(amount);
    this->setKnockBack(dir);
    if (this->isAlive())
    {
    }
    else
    {
        this->curAnimation = Animation(320, 768, 64, 64, 1);
        if (curArmor != nullptr)
            this->curArmor->setCurAnimation("dead");
    }
}

float Enemy::getAnimationTime()
{
    return curAnimation.getWholeTime();
}

int Enemy::getFacing()
{
    return this->facing;
}
Hitbox *Enemy::getHitbox()
{
    return this->hitbox;
}

int Enemy::getAttackRange()
{
    return this->attackRange;
}

bool Enemy::isCollision()
{
    if (this->collision)
        return true;
    return false;
}

bool Enemy::isIdle()
{
    return this->idle;
}

void Enemy::move(const float &dt, const float dir_x, const float dir_y)
{
    if (this->movement)
        this->movement->move(dir_x, dir_y, dt);
}

void Enemy::stopVelocity()
{
    if (this->movement)
        this->movement->stop();
}

void Enemy::stopVelocityX()
{
    if (this->movement)
        this->movement->stopX();
}

void Enemy::stopVelocityY()
{
    if (this->movement)
        this->movement->stopY();
}

sf::FloatRect Enemy::getNextPosBounds(const float &dt)
{
    if (this->hitbox && this->movement)
        return this->hitbox->getNextPosition(this->movement->getVelocity() * dt);
    return sf::FloatRect();
}

void Enemy::updateCollision(TileMap &tilemap, const float &dt)
{
}

void Enemy::attack(Player *pl)
{
    aPlayer = pl;
    switch (facing)
    {
    case 1: // N E S W
        curAnimation = Animation(0, 256, 64, 64, 6);
        curAnimation.y = 1;
        if (this->curWeapon != nullptr)
            this->curWeapon->setCurAnimation("hitUp");
        if (this->curArmor != nullptr)
            this->curArmor->setCurAnimation("hitUp");
        break;
    case 2:
        curAnimation = Animation(0, 448, 64, 64, 6);
        curAnimation.y = 1;
        if (this->curWeapon != nullptr)
            this->curWeapon->setCurAnimation("hitRight");
        if (this->curArmor != nullptr)
            this->curArmor->setCurAnimation("hitRight");
        break;
    case 3:
        curAnimation = Animation(0, 384, 64, 64, 6);
        curAnimation.y = 1;
        if (this->curWeapon != nullptr)
            this->curWeapon->setCurAnimation("hitDown");
        if (this->curArmor != nullptr)
            this->curArmor->setCurAnimation("hitDown");
        break;
    case 4:
        curAnimation = Animation(0, 320, 64, 64, 6);
        curAnimation.y = 1;
        if (this->curWeapon != nullptr)
            this->curWeapon->setCurAnimation("hitLeft");
        if (this->curArmor != nullptr)
            this->curArmor->setCurAnimation("hitLeft");
        break;
    default:
        break;
    }
}

// tarkistaa onko vihollinen johon hyökättävää vihollista ja onko se tarpeaksi lähellä
// Jos on, se tekee osuman viholliseen
void Enemy::hitPlayer()
{
    if (aPlayer != nullptr)
    {

        int range = 40;
        if (this->curWeapon != nullptr)
            range = curWeapon->getRange();
        int damage = 1;
        if (this->curWeapon != nullptr)
            damage = curWeapon->getDamage();

        if (this->isInRange(aPlayer, facing, range))
            aPlayer->getHit(damage, facing);
        aPlayer = nullptr;
    }
}

bool Enemy::isInRange(Player *pl, int dir, int range)
{

    float ex = this->getPosition().x + 32.f; // getPos yläkulmassa -> keskikohta = (x+32, y-32)
    float ey = this->getPosition().y - 32.f;
    float px = pl->getPosition().x + 32.f;
    float py = pl->getPosition().y - 32.f;

    switch (dir)
    {
    //N E S W
    case 1:
        if (py < ey && sqrt(pow(px - ex, 2) + pow(py - ey, 2)) < range) // Onko vihollinen pelaajan edessä
            return true;                                                // && onko etäisyys tarpeeksi pieni(Pythagoraan lause)
        else
            return false;
        break;

    case 2:
        if (px > ex && sqrt(pow(px - ex, 2) + pow(py - ey, 2)) < range)
            return true;
        else
            return false;
        break;

    case 3:
        if (py > ey && sqrt(pow(px - ex, 2) + pow(py - ey, 2)) < range)
            return true;
        else
            return false;
        break;

    case 4:
        if (px < ex && sqrt(pow(px - ex, 2) + pow(py - ey, 2)) < range)
            return true;
        else
            return false;
        break;
    // 5: Kaikki suunnat
    case 5:
        if (sqrt(pow(px - ex, 2) + pow(py - ey, 2)) < range)
            return true;
        else
            return false;
        break;
    default:
        break;
    }
    return false;
}

bool Enemy::isAttacking()
{
    return (this->curAnimation.y == 1 && this->curAnimation.getWholeTime() < 0.6f); //animaatioon menee 0.6f aikaa ja attack animaation y = 1
}
bool Enemy::canAttack()
{
    return (this->curAnimation.y == 1 && this->curAnimation.getWholeTime() > 0.5f);
}
void Enemy::stop()
{
    curAnimation = still;
}

void Enemy::setAnimation(int facing)
{
    switch (facing)
    {
    case 1: // N E S W
        curAnimation = Animation(0, 0, 64, 64, 1);
        curAnimation.y = 0;
        if (this->curWeapon != nullptr)
            this->curWeapon->setCurAnimation("stillUp");
        if (this->curArmor != nullptr)
            this->curArmor->setCurAnimation("stillUp");
        break;
    case 2:
        curAnimation = Animation(0, 192, 64, 64, 1);
        curAnimation.y = 0;
        if (this->curWeapon != nullptr)
            this->curWeapon->setCurAnimation("stillRight");
        if (this->curArmor != nullptr)
            this->curArmor->setCurAnimation("stillRight");
        break;
    case 3:
        curAnimation = Animation(0, 128, 64, 64, 1);
        curAnimation.y = 0;
        if (this->curWeapon != nullptr)
            this->curWeapon->setCurAnimation("stillDown");
        if (this->curArmor != nullptr)
            this->curArmor->setCurAnimation("stillDown");
        break;
    case 4:
        curAnimation = Animation(0, 64, 64, 64, 1);
        curAnimation.y = 0;
        if (this->curWeapon != nullptr)
            this->curWeapon->setCurAnimation("stillLeft");
        if (this->curArmor != nullptr)
            this->curArmor->setCurAnimation("stillLeft");
        break;
    }
}

void Enemy::setIdle(int i)
{
    if (i == 1)
        this->idle = true;
    else
        this->idle = false;
}
void Enemy::setWalkingDir(int dir)
{
    this->facing = dir;
    this->walkingdir = dir;
}

void Enemy::update(const float &dt)
{

    if (!this->isAlive())
        ;
    else if (this->isAttacking())
        ;
    else if (this->movement->getVelocity().x == 0 && this->movement->getVelocity().y == 0)
    {
        this->setAnimation(this->facing);
    }
    else if (walkingdir == 4 && curAnimation.y != leftWalk.y)
    {
        curAnimation = leftWalk;
        if (curWeapon != nullptr)
            curWeapon->setCurAnimation("stillLeft");
        if (curArmor != nullptr)
            curArmor->setCurAnimation("leftWalk");
        this->facing = 4; //
    }
    else if (walkingdir == 2 && curAnimation.y != rightWalk.y)
    {
        curAnimation = rightWalk;
        if (curWeapon != nullptr)
            curWeapon->setCurAnimation("stillRight");
        if (curArmor != nullptr)
            curArmor->setCurAnimation("rightWalk");
        this->facing = 2; // east
    }
    else if (walkingdir == 1 && curAnimation.y != upWalk.y)
    {
        curAnimation = upWalk;
        if (curWeapon != nullptr)
            curWeapon->setCurAnimation("stillUp");
        if (curArmor != nullptr)
            curArmor->setCurAnimation("upWalk");
        this->facing = 1; // north
    }
    else if (walkingdir == 3 && curAnimation.y != downWalk.y)
    {
        curAnimation = downWalk;
        if (curWeapon != nullptr)
            curWeapon->setCurAnimation("stillDown");
        if (curArmor != nullptr)
            curArmor->setCurAnimation("downWalk");
        this->facing = 3; // south
    }
    curAnimation.Update(dt);
    curAnimation.ApplyToSprite(sprite);
    this->hitbox->update();

    //weapon update
    if (curWeapon != nullptr)
    {
        curWeapon->setPos(this->getPosition().x - 64.f, this->getPosition().y - 64.f);
        this->curWeapon->update(dt);
    }
    if (!this->isAlive())
        curWeapon = nullptr;

    //armor update
    if (curArmor != nullptr)
    {
        curArmor->setPos(this->getPosition().x, this->getPosition().y);
        this->curArmor->update(dt);
    }
    //attack range
    if (curWeapon == nullptr)
        attackRange = 40;
    else
        attackRange = curWeapon->getRange();

    if (this->movement)
        this->movement->update(dt);
}

void Enemy::render(sf::RenderTarget *target)
{
    target->draw(this->sprite);
    if (curArmor != nullptr)
        this->curArmor->render(target);
    hitbox->render(*target);
    if (this->curWeapon != nullptr)
        this->curWeapon->render(target);
}
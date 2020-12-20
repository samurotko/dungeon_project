#include "player.hpp"

Player::Player()
{

    this->hitbox = new Hitbox(this->sprite, 15.f, 15.f, 34.f, 47.f);
    initTextures();
    initPlayer();
    initAnimation();
    this->initHPBar();

    //this->curWeapon = new Sword();
    this->curArmor = new Armor("cloth");
    // this->hitpoints += curArmor->getProtection();
    if (MUSIC_ON)
    {
        this->hitbuffer.loadFromFile("../Resources/sounds/swing.wav");
        this->hitsound.setBuffer(hitbuffer);
        this->buffer.loadFromFile("../Resources/sounds/slurp.wav");
        this->sound.setBuffer(buffer);
        this->damagebuffer.loadFromFile("../Resources/sounds/hit.wav");
        this->damagesound.setBuffer(damagebuffer);
    }
}

Player::~Player()
{
    delete this->movement;
    delete this->hitbox;
    delete this->curWeapon;
    delete this->curArmor;
}

// Inits

// Sets position hp etc.
void Player::initPlayer()
{
    this->setPos(15 * TILE_SIZE, 3 * TILE_SIZE);
    this->facing = 3;

    this->collision = false;
    this->hitpoints = 5;
    this->maxHP = 5;

    this->setMovement(200.f, 15.f, 12.f);
}

void Player::initTextures()
{
    this->texture.loadFromFile("../Resources/textures/human.png");
    this->sprite.setTexture(texture);
    this->sprite.setTextureRect(sf::IntRect(0, 128, 64, 64)); // 832x1344
}

void Player::initAnimation()
{

    this->upWalk = Animation(64, 512, 64, 64, 8);
    this->leftWalk = Animation(64, 576, 64, 64, 8);
    this->downWalk = Animation(64, 640, 64, 64, 8);
    this->rightWalk = Animation(64, 704, 64, 64, 8);
    this->still = Animation(0, 640, 64, 64, 1);
    this->firstAnimation = Animation(0, 640, 64, 64, 1);
}

void Player::initHPBar()
{
    float width = 80.f;
    float height = 10.f;
    float x = 20.f;
    float y = 20.f;
    this->maxSizeHPBar = width;

    this->hpBarBack.setSize(sf::Vector2f(width, height));
    this->hpBarBack.setFillColor(sf::Color(50, 50, 50, 200));
    this->hpBarBack.setPosition(x, y);

    this->hpBarInside.setSize(sf::Vector2f(width, height));
    this->hpBarInside.setFillColor(sf::Color(250, 20, 20, 100));
    this->hpBarInside.setPosition(this->hpBarBack.getPosition());
}

void Player::setMovement(const float maxSpeed, const float acceleration, const float deceleration)
{
    this->movement = new Move(this->sprite, maxSpeed, acceleration, deceleration);
}

// Getters

sf::Sprite Player::getSprite()
{
    return this->sprite;
}

Hitbox *Player::getHitbox()
{
    //if (this->hitbox)
    return this->hitbox;
}

sf::FloatRect Player::getNextPosBounds(const float &dt)
{
    if (this->hitbox && this->movement)
        return this->hitbox->getNextPosition(this->movement->getVelocity() * dt);
    return sf::FloatRect();
}

bool Player::isCollision()
{
    if (this->collision)
        return true;
    return false;
}

bool Player::isIdle()
{
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
        !sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
        !sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
        !sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        return true;
    else
        return false;
}

std::vector<Item *> Player::getInventory()
{
    return this->items;
}

// // Functions

void Player::storeItem(Item *item)
{
    items.push_back(item);
}

void Player::usePotion()
{
    if (!items.empty())
    {
        std::vector<Item *>::iterator it = std::find_if(
            items.begin(), items.end(),
            [](const Item *i) {
                return i->getType() == "potion";
            });
        if (it != items.end())
        {
            if (this->getHp() != this->maxHP)
            {
                if (this->getHp() + 1 > this->maxHP)
                {
                    if (MUSIC_ON)
                        sound.play();
                    items.erase(it);
                    this->hitpoints = this->maxHP;
                }
                else
                {
                    if (MUSIC_ON)
                        sound.play();
                    items.erase(it);
                    this->hitpoints++;
                }
            }
        }
    }
}

void Player::move(const float &dt, const float dir_x, const float dir_y)
{
    if (this->movement)
        this->movement->move(dir_x, dir_y, dt);
}

void Player::stopVelocity()
{
    if (this->movement)
        this->movement->stop();
}

void Player::stopVelocityX()
{
    if (this->movement)
        this->movement->stopX();
}

void Player::stopVelocityY()
{
    if (this->movement)
        this->movement->stopY();
}

void Player::updateHPBar()
{
    float prosentage = (this->getHp() / this->maxHP);
    this->hpBarInside.setSize(sf::Vector2f(
        (this->maxSizeHPBar * prosentage),
        this->hpBarInside.getSize().y));

    this->hpBarBack.setPosition(sf::Vector2f(this->getPosition().x - 10, this->getPosition().y - 30));
    this->hpBarInside.setPosition(sf::Vector2f(this->getPosition().x - 10, this->getPosition().y - 30));
}

sf::Vector2f Player::getVelocity()
{
    return this->movement->getVelocity();
}

void Player::getXp()
{
    this->xp += 10;
    if (this->xp >= 80)
    {
    }
    else if (this->xp == 70)
    {
        this->curArmor->changeTexture("plate");
    }
    else if (this->xp == 30)
    {
        this->curArmor->changeTexture("leather");
    }
    else if (this->xp == 10)
    {
        this->curWeapon = new Sword();
    }
}

void Player::attack()
{
    isHitting = true;
    switch (facing)
    {
    case 1: // N E S W
        curAnimation = Animation(0, 768, 64, 64, 6);
        curAnimation.y = 1;
        if (curWeapon != nullptr)
            this->curWeapon->setCurAnimation("hitUp");
        if (this->curArmor != nullptr)
            this->curArmor->setCurAnimation("hitUp");
        break;
    case 2:
        curAnimation = Animation(0, 960, 64, 64, 6);
        curAnimation.y = 1;
        if (curWeapon != nullptr)
            this->curWeapon->setCurAnimation("hitRight");
        if (this->curArmor != nullptr)
            this->curArmor->setCurAnimation("hitRight");
        break;
    case 3:
        curAnimation = Animation(0, 896, 64, 64, 6);
        curAnimation.y = 1;
        if (curWeapon != nullptr)
            this->curWeapon->setCurAnimation("hitDown");
        if (this->curArmor != nullptr)
            this->curArmor->setCurAnimation("hitDown");
        break;
    case 4:
        curAnimation = Animation(0, 832, 64, 64, 6);
        curAnimation.y = 1;
        if (curWeapon != nullptr)
            this->curWeapon->setCurAnimation("hitLeft");
        if (this->curArmor != nullptr)
            this->curArmor->setCurAnimation("hitLeft");
        break;
    default:
        break;
    }
}

// tarkistaa onko hyökättävää vihollista ja onko se tarpeeksi lähellä
// Jos on, se tekee osuman viholliseen
void Player::hitEnemy(std::list<Enemy *> enemyList)
{

    if (isHitting)
    {

        int range = 40;
        if (this->curWeapon != nullptr)
            range = curWeapon->getRange();

        for (std::list<Enemy *>::const_iterator it = enemyList.begin(); it != enemyList.end(); it++)
        {
            if (this->isInRange(*it, facing, range))
            {
                int damage = 1;
                if (this->curWeapon != nullptr)
                    damage = this->curWeapon->getDamage();
                (*it)->getHit(damage, facing);
                if (MUSIC_ON)
                    hitsound.play();
            }
        }
    }
    isHitting = false;
}

bool Player::isInRange(Enemy *en, int dir, int range)
{

    float ex = en->getPosition().x + 32.f; // getPos yläkulmassa -> keskikohta = (x+32, y-32)
    float ey = en->getPosition().y - 32.f;
    float px = this->getPosition().x + 32.f;
    float py = this->getPosition().y - 32.f;

    switch (dir)
    {
    //N E S W
    case 1:
        if (py > ey && sqrt(pow(px - ex, 2) + pow(py - ey, 2)) < range) // Onko vihollinen pelaajan edessä
            return true;                                                // && onko etäisyys tarpeeksi pieni(pythagoraan lause)
        else
            return false;
        break;

    case 2:
        if (px < ex && sqrt(pow(px - ex, 2) + pow(py - ey, 2)) < range)
            return true;
        else
            return false;
        break;

    case 3:
        if (py < ey && sqrt(pow(px - ex, 2) + pow(py - ey, 2)) < range)
            return true;
        else
            return false;
        break;

    case 4:
        if (px > ex && sqrt(pow(px - ex, 2) + pow(py - ey, 2)) < range)
            return true;
        else
            return false;
        break;

    default:
        break;
    }
    return false;
}

bool Player::canAttack()
{
    return (this->curAnimation.y == 1 && this->curAnimation.getWholeTime() > 0.5f);
}

bool Player::isAttacking()
{
    return (this->curAnimation.y == 1 && this->curAnimation.getWholeTime() < 0.6f); //animaatioon menee 0.6f aikaa ja attack animaation y = 1
}
void Player::getHit(float amount, int dir)
{
    if (this->curArmor != nullptr)
        amount = amount / this->curArmor->getProtection();
    this->decreaseHp(amount);
    this->setKnockBack(dir);
    if (MUSIC_ON)
        damagesound.play();
    if (this->isAlive())
    {
    }
    else
    {
        this->curAnimation = Animation(1280, 768, 64, 64, 1);
    }
}
void Player::stop()
{
    curAnimation = still;
}

void Player::setAnimation(int facing)
{
    switch (facing)
    {
    case 1: // N E S W
        curAnimation = Animation(0, 512, 64, 64, 1);
        curAnimation.y = 0;
        if (curWeapon != nullptr)
            this->curWeapon->setCurAnimation("stillUp");
        if (curArmor != nullptr)
            this->curArmor->setCurAnimation("stillUp");
        break;
    case 2:
        curAnimation = Animation(0, 704, 64, 64, 1);
        curAnimation.y = 0;
        if (curWeapon != nullptr)
            this->curWeapon->setCurAnimation("stillRight");
        if (curArmor != nullptr)
            this->curArmor->setCurAnimation("stillRight");

        break;
    case 3:
        curAnimation = Animation(0, 640, 64, 64, 1);
        curAnimation.y = 0;
        if (curWeapon != nullptr)
            this->curWeapon->setCurAnimation("stillDown");
        if (curArmor != nullptr)
            this->curArmor->setCurAnimation("stillDown");

        break;
    case 4:
        curAnimation = Animation(0, 576, 64, 64, 1);
        curAnimation.y = 0;
        if (curWeapon != nullptr)
            this->curWeapon->setCurAnimation("stillLeft");
        if (curArmor != nullptr)
            this->curArmor->setCurAnimation("stillLeft");

        break;
    default:
        break;
    }
}

void Player::setWalkingDir(int dir)
{
    this->walkingdir = dir;
}

void Player::setPos(const float x, const float y)
{
    if (this->hitbox)
        this->hitbox->setPos(sf::Vector2f(x, y));
    else
        this->sprite.setPosition(sf::Vector2f(x, y));
}

void Player::updateCollision(TileMap &tilemap, const float &dt)
{

    //kartan reunat
    sf::Vector2f pos = this->getPosition();
    if (pos.x < 0.f)
    {
        this->setPos(0.f, pos.y);
        this->stopVelocityX();
    }
    else if (pos.x + this->getHitbox()->getGlobalBounds().width > MAP_WIDTH * TILE_SIZE)
    {
        this->setPos(MAP_WIDTH * TILE_SIZE - this->getHitbox()->getGlobalBounds().width, pos.y);
        this->stopVelocityX();
    }
    if (pos.y < 0.f)
    {
        this->setPos(pos.x, 0.f);
        this->stopVelocityY();
    }
    else if (pos.y + this->getHitbox()->getGlobalBounds().height > MAP_HEIGHT * TILE_SIZE)
    {
        this->setPos(pos.x, MAP_HEIGHT * TILE_SIZE - this->getHitbox()->getGlobalBounds().height);
        this->stopVelocityY();
    }

    int fromX;
    int toX;
    int fromY;
    int toY;
    sf::Vector2f coords;

    //renderöintialue collisionille pelaajan suunnan mukaan
    sf::Vector2f downrightCorner = sf::Vector2f(this->getHitbox()->getPosition().x + this->getHitbox()->getGlobalBounds().width,
                                                this->getHitbox()->getPosition().y + this->getHitbox()->getGlobalBounds().height);
    switch (this->getFacing())
    {
        //north
    case 1:
        coords = this->getCoords(this->getPosition());
        fromX = coords.x - 1;
        toX = coords.x + 1;
        fromY = coords.y - 1;
        toY = coords.y;

        break;
        //east
    case 2:
        coords = this->getCoords(downrightCorner);
        fromX = coords.x;
        toX = fromX + 1;
        fromY = coords.y - 1;
        toY = fromY + 2;
        break;
        //south
    case 3:
        coords = this->getCoords(downrightCorner);
        fromX = coords.x - 1;
        toX = coords.x + 1;
        fromY = coords.y;
        toY = fromY + 1;

        break;
        //west
    case 4:
        coords = this->getCoords(this->getPosition());
        fromX = coords.x - 1;
        toX = coords.x;
        fromY = coords.y - 1;
        toY = coords.y + 1;
        break;
    default:
        break;
    }

    for (int x = fromX; x <= toX; x++)
    {
        for (int y = fromY; y <= toY; y++)
        {
            sf::FloatRect playerBounds = this->getHitbox()->getGlobalBounds();
            Tile *currentTile;
            sf::FloatRect wallBounds;
            sf::FloatRect nextPos = this->getNextPosBounds(dt);
            if (y < MAP_HEIGHT && x < MAP_WIDTH)
            {
                int index = y * MAP_WIDTH + x;
                currentTile = tilemap.getTiles().at(y * MAP_WIDTH + x);

                wallBounds = tilemap.getTiles().at(y * MAP_WIDTH + x)->getBounds();
            }
            else
            {
                currentTile = nullptr;
            }

            //tarkastaa intersectit ja muutta pelaajan sijainnin/nopeuden sen mukaan
            if (currentTile)
            {
                if (!currentTile->getCanWalk())
                {

                    if (currentTile->intesect(nextPos))
                    {

                        if (playerBounds.top < wallBounds.top && playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height && playerBounds.left < wallBounds.left + wallBounds.width && playerBounds.left + playerBounds.width > wallBounds.left)
                        {

                            this->stopVelocityY();
                            this->setPos(playerBounds.left, wallBounds.top - playerBounds.height);
                        }

                        //top collision
                        else if (playerBounds.top > wallBounds.top && playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height && playerBounds.left < wallBounds.left + wallBounds.width && playerBounds.left + playerBounds.width > wallBounds.left)
                        {

                            this->stopVelocityY();
                            this->setPos(playerBounds.left, wallBounds.top + wallBounds.height);
                        }

                        //right collision
                        else if (playerBounds.left < wallBounds.left && playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width && playerBounds.top < wallBounds.top + wallBounds.height && playerBounds.top + playerBounds.height > wallBounds.top)
                        {

                            this->stopVelocityX();
                            this->setPos(wallBounds.left - playerBounds.width, playerBounds.top);
                        }

                        //left collision
                        else if (playerBounds.left > wallBounds.left && playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width && playerBounds.top < wallBounds.top + wallBounds.height && playerBounds.top + playerBounds.height > wallBounds.top)
                        {

                            this->stopVelocityX();
                            this->setPos(wallBounds.left + wallBounds.width, playerBounds.top);
                        }
                    }
                }
            }
        }
    }
}

void Player::update(const float &dt)
{
    if (this->movement)
        this->movement->update(dt);
    if (!this->isAlive())
        ;
    else if (this->isAttacking())
        ;
    else if (this->isIdle())
        this->setAnimation(facing);
    else if (walkingdir == 4 && curAnimation.y != leftWalk.y)
    {
        curAnimation = leftWalk;
        if (curWeapon != nullptr)
            this->curWeapon->setCurAnimation("stillLeft");
        if (curArmor != nullptr)
            this->curArmor->setCurAnimation("leftWalk");
        this->facing = 4; // west
    }
    else if (walkingdir == 2 && curAnimation.y != rightWalk.y)
    {
        curAnimation = rightWalk;
        if (curWeapon != nullptr)
            this->curWeapon->setCurAnimation("stillRight");
        if (curArmor != nullptr)
            this->curArmor->setCurAnimation("rightWalk");
        this->facing = 2; // east
    }
    else if (walkingdir == 1 && curAnimation.y != upWalk.y)
    {
        curAnimation = upWalk;
        if (curWeapon != nullptr)
            this->curWeapon->setCurAnimation("stillUp");
        if (curArmor != nullptr)
            this->curArmor->setCurAnimation("upWalk");
        this->facing = 1; // north
    }
    else if (walkingdir == 3 && curAnimation.y != downWalk.y)
    {
        curAnimation = downWalk;
        if (curWeapon != nullptr)
            this->curWeapon->setCurAnimation("stillDown");
        if (curArmor != nullptr)
            this->curArmor->setCurAnimation("downWalk");
        this->facing = 3; // south
    }
    curAnimation.Update(dt);
    curAnimation.ApplyToSprite(sprite);
    this->hitbox->update();
    if (curWeapon != nullptr)
    {
        curWeapon->setPos(this->getPosition().x - 64.f, this->getPosition().y - 64.f);
        this->curWeapon->update(dt);
    }
    if (curArmor != nullptr)
    {
        curArmor->setPos(this->getPosition().x, this->getPosition().y);
        this->curArmor->update(dt);
    }
    this->updateHPBar();
}

void Player::render(sf::RenderTarget *target)
{
    // piirtää pelaajahahmon ikkunaan
    target->draw(this->sprite);

    target->draw(this->collisionBox);
    hitbox->render(*target);
    if (curArmor != nullptr)
        this->curArmor->render(target);
    if (curWeapon != nullptr)
        this->curWeapon->render(target);
    target->draw(this->collisionBox);

    //HPbar
    target->draw(this->hpBarBack);
    target->draw(this->hpBarInside);
}
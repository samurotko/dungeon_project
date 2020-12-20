#include "gamestate.hpp"
#include <cmath>

void GameState::initFonts()
{
    if (!this->font.loadFromFile("../Resources/fonts/PixellettersFull.ttf"))
        std::cout << "Could not load font." << std::endl;
}

GameState::GameState(sf::RenderWindow *window, std::stack<State *> *states)
    : State(window, states)
{
    initView();
    initRenderTexture();
    initText();
    initFonts();
    InitPauseMenu();

    this->tilemap.createTiles();

    //enemies
    enemies.push_back(new Enemy(13, 13, "noArmor", "noWeapon", 5));
    enemies.push_back(new Enemy(3, 12, "robes", "sword", 5, 2));
    enemies.push_back(new Enemy(5, 20, "noArmor", "sword", 5));
    enemies.push_back(new Enemy(23, 22, "robes", "sword", 5));
    enemies.push_back(new Enemy(17, 25, "robes", "sword", 5));
    enemies.push_back(new Enemy(13, 30, "robes", "sword", 5, 1));
    enemies.push_back(new Enemy(9, 25, "robes", "sword", 5));

    //Bossi ja kaverit
    enemies.push_back(new Enemy(29, 6, "chain", "sword", 10));
    enemies.push_back(new Enemy(29, 7, "noArmor", "noWeapon", 5));
    enemies.push_back(new Enemy(29, 5, "noArmor", "noWeapon", 5));
    enemies.push_back(new Enemy(30, 6, "noArmor", "noWeapon", 5));
    enemies.push_back(new Enemy(28, 6, "noArmor", "noWeapon", 5));

    mapitems.push_back(new Item("potion", 10, 5));
    mapitems.push_back(new Item("potion", 3, 11));
    mapitems.push_back(new Item("potion", 4, 19));
    mapitems.push_back(new Item("potion", 22, 20));
    mapitems.push_back(new Item("potion", 21, 20));

    if (MUSIC_ON)
    {
        buffer.loadFromFile("../Resources/sounds/awesomeness.wav");
        sound.setBuffer(buffer);
        sound.play();
        sound.setLoop(true);
    }
}

GameState::~GameState()
{
    delete this->pausemenu;
    for (auto i : this->enemies)
        delete i;
    for (auto i : this->mapitems)
        delete i;
}

void GameState::InitPauseMenu()
{
    this->pausemenu = new PauseMenu(*this->window, this->font);
    this->pausemenu->addButton();
}

void GameState::updateDt()
{
    this->dt = this->dtClock.restart().asSeconds();
}

void GameState::UpdatePauseMenuButtons()
{
    if (this->pausemenu->isButtonPressed("QUIT"))
        this->exit();
    if (this->pausemenu->isButtonPressed("CONTINUE"))
        this->unpauseState();
}

void GameState::UpdatePaused(const float &dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && this->getKeytime())
    {
        if (!this->paused)
            this->pauseState();
    }
}

void GameState::initRenderTexture()
{
    this->renderTexture.create(WINDOW_WIDTH, WINDOW_HEIGHT);
    this->renderSprite.setTexture(this->renderTexture.getTexture());
    this->renderSprite.setTextureRect(sf::IntRect(0, 0, WINDOW_SIZE.first, WINDOW_SIZE.second));
}

void GameState::initView()
{
    this->view.setSize(sf::Vector2f(WINDOW_SIZE.first, WINDOW_SIZE.second));
    this->view.setCenter(sf::Vector2f(player.getPosition()));
}

void GameState::initText()
{
    font.loadFromFile("../Resources/fonts/PixellettersFull.ttf");

    potText.setFont(font);
    potText.setFillColor(sf::Color::Green);
    potText.setPosition(30, 10);
    potText.setCharacterSize(50);
    potText.setStyle(sf::Text::Style::Bold);

    winText.setFont(font);
    winText.setFillColor(sf::Color::Yellow);
    winText.setPosition(WINDOW_WIDTH / 2 - 300, WINDOW_HEIGHT / 2 - 200);
    winText.setCharacterSize(200);
    winText.setStyle(sf::Text::Style::Bold);
    winText.setString("You Win!");
}

void GameState::updatePlayer(const float &dt)
{
    timer += 0.01;
    if (this->player.getKnockBack() > 0)
    {
        if (this->player.getKnockBack() == 1)
            this->player.move(dt, 0.f, -3000.f);

        if (this->player.getKnockBack() == 2)
            this->player.move(dt, 3000.f, 0.f);

        if (this->player.getKnockBack() == 3)
            this->player.move(dt, 0, 3000.f);

        if (this->player.getKnockBack() == 4)
            this->player.move(dt, -3000.f, 0.f);
        this->player.setKnockBack(0);
    }

    if (this->player.isAttacking())
    {
        if (this->player.canAttack())
            this->player.hitEnemy(enemies);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        this->player.attack();
    }
    // liikuttaa WASD näppäimillä pelaajahahmoa
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        this->player.move(dt, -1.f, 0.f);
        this->player.setWalkingDir(4);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        this->player.move(dt, 1.f, 0.f);
        this->player.setWalkingDir(2);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        this->player.move(dt, 0.f, -1.f);
        this->player.setWalkingDir(1);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        this->player.move(dt, 0.f, 1.f);
        this->player.setWalkingDir(3);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
    {
        if (timer > 1)
        {
            player.usePotion();
            timer = 0;
        }
    }
    //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    //  this->exit();
}
void GameState::updateEnemies(const float &dt)
{

    float px = this->player.getPosition().x;
    float py = this->player.getPosition().y;

    for (std::list<Enemy *>::const_iterator it = enemies.begin(); it != enemies.end(); it++)
    {

        if (!((*it)->isInRange(&this->player, 5, 200)))
            continue;
        float ex = (*it)->getPosition().x;
        float ey = (*it)->getPosition().y;

        if ((*it)->getKnockBack() > 0 && (*it)->isAlive())
        {
            if ((*it)->getKnockBack() == 1)
                (*it)->move(dt, 0.f, -70.f);

            if ((*it)->getKnockBack() == 2)
                (*it)->move(dt, 70.f, 0.f);

            if ((*it)->getKnockBack() == 3)
                (*it)->move(dt, 0.f, 70.f);

            if ((*it)->getKnockBack() == 4)
                (*it)->move(dt, -70.f, 0.f);

            (*it)->setKnockBack(0);
        }

        //liikuttaa vihollista pelaajan suuntaan
        if (!(*it)->isAlive())
            ;

        else if ((*it)->isAttacking())
        {
            if ((*it)->canAttack())
                (*it)->hitPlayer();
        }
        else if ((*it)->isInRange(&this->player, 5, (*it)->getAttackRange()) && (*it)->isAlive())
        {
            (*it)->attack(&this->player);
        }
        else if (ey >= py && abs(ex - px) <= abs(ey - py))
        {
            if ((*it)->isInRange(&this->player, 5, 200)) //200 siis range jolta enemy lähtee liikkumaan
            {
                (*it)->setWalkingDir(1);
                (*it)->move(dt, 0.f, -1.f);
            }
            else
                (*it)->setIdle(1);
            (*it)->setWalkingDir(1);
        }
        else if (ex >= px && abs(ex - px) >= abs(ey - py))
        {
            if ((*it)->isInRange(&this->player, 5, 200))
            {
                (*it)->setWalkingDir(4);
                (*it)->move(dt, -1.f, 0.f);
            }
            else
                (*it)->setIdle(1);
            (*it)->setWalkingDir(4);
        }
        else if (ey <= py && abs(ex - px) <= abs(ey - py))
        {
            if ((*it)->isInRange(&this->player, 5, 200))
            {
                (*it)->setWalkingDir(3);
                (*it)->move(dt, 0.f, 1.f);
            }
            else
                (*it)->setIdle(1);
            (*it)->setWalkingDir(3);
        }
        else if (ex <= px && abs(ex - px) >= abs(ey - py))
        {
            if ((*it)->isInRange(&this->player, 5, 200))
            {
                (*it)->setWalkingDir(2);
                (*it)->move(dt, 1.f, 0.f);
            }
            else
                (*it)->setIdle(1);
            (*it)->setWalkingDir(2);
        }
    }
}

void GameState::update(const float &dt)
{
    this->updateMousePos(); //update always
    this->updatekeytime(dt);
    this->UpdatePaused(dt);

    if (!this->paused) //updates when not paused
    {
        // collision esineen kanssa
        for (auto i = mapitems.begin(); i != mapitems.end(); i++)
        {
            if (player.getHitbox()->checkIntersect((*i)->getSprite().getGlobalBounds()))
            {
                player.storeItem(*i);
                i = mapitems.erase(i);
            }
        }

        this->updateMousePos();
        for (std::list<Enemy *>::const_iterator it = enemies.begin(); it != enemies.end(); it++)
        {
            (*it)->update(dt);
            if (!(*it)->isAlive() && (*it)->getAnimationTime() > 3.f)
            {
                player.getXp(); // Testi xp varten
                delete *it;
                it = enemies.erase(it);
            }
        }
        this->player.update(dt);
        updatePlayer(dt);
        this->player.updateCollision(this->tilemap, dt);

        updateEnemies(dt);

        if (!this->player.isAlive())
        {
            std::cout << "Game Over" << std::endl;
            this->exit();
        }
    }
    //updates only pausemenu
    else
    {
        this->pausemenu->update(this->mousePosView);
        this->UpdatePauseMenuButtons();
    }
}

void GameState::render(sf::RenderTarget *target)
{
    hpText.setString("HP: " + std::to_string(player.getHp()));
    potText.setString("Potions: " + std::to_string(this->player.getInventory().size()));

    if (!target)
        target = this->window;
    this->renderTexture.clear();

    this->view.setCenter((sf::Vector2f(std::round(player.getPosition().x), std::round(player.getPosition().y)))); // Rounding fixes flickering
    this->renderTexture.setView(this->view);
    this->tilemap.render(&this->renderTexture); // renderöi grafiikat
    this->texturemap.render(&this->renderTexture);

    // this->renderTexture.draw(this->testsprite);
    this->player.render(&this->renderTexture);

    for (auto i : mapitems)
    {
        this->renderTexture.draw(i->getSprite());
    }

    for (std::list<Enemy *>::const_iterator it = enemies.begin(); it != enemies.end(); it++)
    {
        (*it)->render(&this->renderTexture);
    }
    this->renderTexture.display();
    //this->renderSprite.setTexture(this->renderTexture.getTexture());
    target->draw(this->renderSprite);
    //target->draw(hpText);
    target->draw(potText);

    if (this->enemies.empty())
    {
        target->draw(winText);
    }

    if (this->paused) //renderöi pausemenun
    {
        this->pausemenu->render(*target);
    }
}
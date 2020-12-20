#include "tilemap.hpp"
#include <cmath>

TileMap::TileMap()
{
    unsigned fromX = 0;
    unsigned toX = 0;
    unsigned fromY = 0;
    unsigned toY = 0;

    this->tileTextures.loadFromFile("../Resources/textures/tiles.png");
    this->loadCounter = sf::Vector2i(0, 0);
    std::ifstream fmap("../Resources/map/map.txt");
    if (fmap.is_open())
    {
        this->sprites.setTexture(tileTextures);
        while (!fmap.eof())
        {
            std::string str;
            fmap >> str;
            char x = str[0], y = str[2];
            if (!isdigit(x) || !isdigit(y))
                map[loadCounter.x][loadCounter.y] = sf::Vector2i(-1, -1);
            else
                map[loadCounter.x][loadCounter.y] = sf::Vector2i(x - '0', y - '0');
            // vaihtaa riviä
            if (fmap.peek() == '\n')
            {
                loadCounter.x = 0;
                loadCounter.y++;
            }
            else
                loadCounter.x++;
        }
        loadCounter.y++;
    }
    fmap.close();

    //set collision box
    this->collision.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    this->collision.setFillColor(sf::Color(0, 0, 255, 150));
}

//luo jokiselle tilelle Tileobjektin, joka kertoo suoraan tilen sijainnin pikseleinä ja canWalk arvon
void TileMap::createTiles()
{

    int count = 0;
    for (int i = 0; i < MAP_WIDTH; i++)
    {
        for (int j = 0; j < MAP_HEIGHT; j++)
        {
            if (map[i][j].x > -1 && map[i][j].y > -1)
            {

                count++;
                if ((map[i][j].y >= 6 && map[i][j].y <= 9))
                {
                    this->sprites.setPosition(i * TILE_SIZE, j * TILE_SIZE);
                    this->sprites.setTextureRect(sf::IntRect(map[i][j].x * TILE_SIZE, map[i][j].y * TILE_SIZE, TILE_SIZE, TILE_SIZE));
                    this->tiles.insert({j * MAP_WIDTH + i, new Tile(i * TILE_SIZE, j * TILE_SIZE, false, this->sprites)});
                }
                else
                {
                    this->sprites.setPosition(i * TILE_SIZE, j * TILE_SIZE);
                    this->sprites.setTextureRect(sf::IntRect(map[i][j].x * TILE_SIZE, map[i][j].y * TILE_SIZE, TILE_SIZE, TILE_SIZE));
                    this->tiles.insert({j * MAP_WIDTH + i, new Tile(i * TILE_SIZE, j * TILE_SIZE, true, this->sprites)});
                }
            }
            else
            {

                this->tiles.insert({j * MAP_WIDTH + i, new Tile(i * TILE_SIZE, j * TILE_SIZE, false)});
            }
        }
    }
}

std::map<int, Tile *> TileMap::getTiles()
{
    return tiles;
}

void TileMap::render(sf::RenderTarget *target)
{

    /*for (int i = 0; i < loadCounter.x; i++)
    {
        for (int j = 0; j < loadCounter.y; j++)
        {
            if (map[i][j].x != -1 && map[i][j].y != -1)
            {
                this->sprites.setPosition(i * TILE_SIZE, j * TILE_SIZE);
                this->sprites.setTextureRect(sf::IntRect(map[i][j].x * TILE_SIZE, map[i][j].y * TILE_SIZE, TILE_SIZE, TILE_SIZE));

                target->draw(this->sprites);
            }
        }
    }*/

    //piirtää collisionboxin seinien kohdalle, debuggausta varten, poistetaan myöhemmin
    for (auto k = tiles.begin(); k != this->tiles.end(); k++)
    {
        Tile *t = k->second;
        target->draw(t->getSprite());
    }
    /*if (!this->tiles.empty())
         {
             for (int x = 0; x < MAP_WIDTH; x++) {
                 for (int y = 0; y < MAP_HEIGHT; y++) {
                     Tile* currentTile = this->getTiles().at(y * MAP_WIDTH + x);
                     if (!currentTile->getCanWalk())

                     {
                         this->collision.setPosition(currentTile->getSprite().getPosition());

                         target->draw(this->collision);
                     }
                 }
             }
         }*/
}
int TileMap::tileIndex(sf::Vector2f pos)
{
    int x;
    int y;

    x = (pos.x - fmod(pos.x, TILE_SIZE) + 1) / TILE_SIZE;
    y = (pos.y - fmod(pos.y, TILE_SIZE) + 1) / TILE_SIZE;

    /*if ((x < MAP_WIDTH && x >= 0) &&
        (y < MAP_HEIGHT && y >= 0))*/
    return MAP_WIDTH * y + x;
}

TileMap::~TileMap()
{
    for (auto i : this->tiles)
        delete i.second;
    //korjaa
    this->tiles.clear();
}
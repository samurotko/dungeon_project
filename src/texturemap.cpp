#include "texturemap.hpp"

TextureMap::TextureMap()
{
    this->tileTextures.loadFromFile("../Resources/textures/tiles.png");
    this->loadCounter = sf::Vector2i(0, 0);
    std::ifstream fmap("../Resources/map/texturemap.txt");
    if (fmap.is_open())
    {
        this->sprites.setTexture(tileTextures);

        while (!fmap.eof())
        {
            std::string str;
            fmap >> str;
            if (str.length() == 3)
            {
                char x = str[0], y = str[2]; // Ei osaa ottaa huomioon jos x tai y > 9
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
            else
            {
                char x = str[0], y = str[3]; // y skippaa ekan digitin koska oletusavroisesti se on 1
                if (!isdigit(x) || !isdigit(y))
                    map[loadCounter.x][loadCounter.y] = sf::Vector2i(-1, -1);
                else
                    map[loadCounter.x][loadCounter.y] = sf::Vector2i(x - '0', 10 + y - '0');
                // vaihtaa riviä
                if (fmap.peek() == '\n')
                {
                    loadCounter.x = 0;
                    loadCounter.y++;
                }
                else
                    loadCounter.x++;
            }
        }
        loadCounter.y++;
    }
    fmap.close();
}

void TextureMap::render(sf::RenderTarget *target)
{

    for (int i = 0; i < loadCounter.x; i++)
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
    }
}

TextureMap::~TextureMap()
{
}
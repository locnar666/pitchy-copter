#include "map.h"
#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;

//Constructeur
Map::Map(Helico& helico) : joueur(helico)
{ }

bool Map::load(const string& tileset, sf::Vector2u tileSize, std::vector<int> tiles, unsigned int width, unsigned int height)
{
 // on charge la texture du tileset
    if (!m_tileset.loadFromFile(tileset))
        return false;

    // on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4);

    // on remplit le tableau de vertex, avec un quad par tuile
    for (unsigned int i = 0; i < width; ++i)
        for (unsigned int j = 0; j < height; ++j)
        {
            // on récupère le numéro de tuile courant
            tileNumber = tiles[i + j * width];
            //std::cout << tileNumber << std::endl;

            // on en déduit sa position dans la texture du tileset
            int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);
            //std::cout << tu << " " << tv << std::endl;

            // on récupère un pointeur vers le quad à définir dans le tableau de vertex
            sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

            // on définit ses quatre coins
            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

            // on définit ses quatre coordonnées de texture
            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }
    return true;
}

bool Map::indiceTile(std::vector<int> &tabTile, unsigned int t_width, unsigned int t_height)
{

    sf::Vector2f position_joueur = this->joueur.getPosition();
    sf::FloatRect rect_joueur = this->joueur.getGlobalBounds();
    //test
    std::cout << position_joueur.x << std::endl;
    std::cout << position_joueur.y << std::endl;

    if ((position_joueur.x < 0 || (position_joueur.x + rect_joueur.width - 1) >= 800) ||  // Dépasse en largeur
        (position_joueur.y < 0 || (position_joueur.y + rect_joueur.height - 1) >= 480))    // Dépasse en hauteur
    {
        return true;
    }

    int xmin = position_joueur.x / 32;
    int ymin = position_joueur.y / 32;
    int xmax = (position_joueur.x + rect_joueur.width - 1) / 32;
    int ymax = (position_joueur.y + rect_joueur.height - 1) / 32;

    //int numberTile = tileNumber;
    for (unsigned int i = 0; i < t_width; ++i)
        for (unsigned int j = 0; j < t_height; ++j)
        {
            // on récupère le numéro de tuile courant
            tileNumber = tabTile[i + j * t_width];
            //std::cout << tileNumber << std::endl;
            if (tileNumber < 4)

            return true;
        }


    //int nbtiles[] = tabtileH[];
    //std::cout << tileNumber << std::endl;
    return false;
}


void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // on applique la transformation
        states.transform *= getTransform();

        // on applique la texture du tileset
        states.texture = &m_tileset;

        // et on dessine enfin le tableau de vertex
        target.draw(m_vertices, states);
}


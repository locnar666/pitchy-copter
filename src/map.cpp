#include <include/Map.h>
#include <SFML/Graphics.hpp>
#include <iostream>


Map::Map(Helico& helico, const char *tileset_filename, sf::Vector2u tileSize, unsigned int width, unsigned int height)
: joueur(helico)
{
   std::ifstream map_stream("Map/test_Presentatio.txt"); //Map/Carte_middle_tiles.txt
   std::vector<int> tiles(std::istream_iterator<int>(map_stream),
                          std::istream_iterator<int>{});

 // on charge la texture du tileset
    if (!this->tileset.loadFromFile(tileset_filename))
        std::cout << "Impossible de charger la carte" << std::endl;

    // on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
    this->vertices.setPrimitiveType(sf::Quads);
    this->vertices.resize(width * height * 4);

    // on remplit le tableau de vertex, avec un quad par tuile
    for(unsigned int i=0; i < width; ++i)
        for(unsigned int j=0; j < height; ++j)
        {
            // on récupère le numéro de la tuile courante
            this->tileNumber = (tiles[i + j * width]) ;

            //std::cout << tileNumber << std::endl;

            // on en déduit sa position dans la texture du tileset
            int tu = this->tileNumber % (this->tileset.getSize().x / tileSize.x);
            int tv = this->tileNumber / (this->tileset.getSize().x / tileSize.x);
            //std::cout << tu << " " << tv << std::endl;

            // on récupère un pointeur vers le quad à définir dans le tableau de vertex
            sf::Vertex* quad = &this->vertices[(i + j * width) * 4];

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
    //Copie du tableau "tiles" pour fonction "indiceTile"
    tabTile = tiles;
}

bool Map::indiceTile()
{
    sf::Vector2f position_joueur = this->joueur.getPosition();
    sf::FloatRect rect_joueur = this->joueur.getGlobalBounds();

    if ((position_joueur.y < 0 || (position_joueur.y + rect_joueur.height - 1) >= 480))    // Dépasse en hauteur
    {
        return true;
    }

    int xmin = position_joueur.x / 16;
    int ymin = position_joueur.y / 16;
    int xmax = (position_joueur.x + rect_joueur.width - 1) / 16;
    int ymax = (position_joueur.y + rect_joueur.height - 1) / 16;

    for (int i = xmin; i <= xmax; ++i)
        for (int j = ymin; j <= ymax; ++j)
        {
            // on récupère le numéro de tuile courant
            tileNumber = tabTile[i + j * 1000]; // 100 = Largeur map
            if (tileNumber == 5 || (tileNumber >= 10 && tileNumber <= 20) || tileNumber == 25)
                return true;
        }
    return false;
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // on applique la transformation
        states.transform *= getTransform();

        // on applique la texture du tileset
        states.texture = &this->tileset;

        // et on dessine enfin le tableau de vertex
        target.draw(this->vertices, states);
}


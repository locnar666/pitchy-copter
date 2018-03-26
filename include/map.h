#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "Helico.h"

class Map : public sf::Drawable, public sf::Transformable
{
    public:

        //Constructeur
        Map(Helico&);

        //const int*
        bool load(const std::string& tileset, sf::Vector2u tileSize, std::vector<int> tiles, unsigned int width, unsigned int height);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const;
        bool indiceTile(std::vector<int> &tabTile, unsigned int t_width, unsigned int t_height);

    private:
        //Variables de la classe en accès privé

        sf::VertexArray m_vertices;
        sf::Texture m_tileset;

        int tileNumber;
        int tileNombre[];
        int i;
        int j;

        Helico& joueur;
        // fonction TEST


};
#endif

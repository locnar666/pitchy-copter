#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "Helico.h"

/*!
 * \class Map
 * \brief Creation de la TileMap
 * \date 06 avril 2018
 */

class Map : public sf::Drawable, public sf::Transformable
{
    public:

        //Constructeur
        /*!
         * \brief Permet d'importer un fichier text avec des nombres. Chaque nombre à l'interieur de ce
         * fichier correspond à une "tuile" (du TileSet -> importer lors de la creation du jeu).
         * Cette classe fait la correspondance entre chiffres et image. Elle gere aussi, dans une
         * methode, les collisions (en retrouvant la position du joueur, puis en checkant le nombre
         * de la tuile.
        */
        Map(Helico&, const char *tileset_filename,
            sf::Vector2u tileSize,
            unsigned int width, unsigned int height);
        /*!
         * \brief dessine la map
         * \param target, state
        */
        virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const;
        /**
        * \brief Gestion des collisions en recuperant le nombre correspondant a la tuile.
        * \return vrai si Tuile considéree comme solide, faux sinon
        */
        bool indiceTile();

    private:
        sf::VertexArray vertices;
        sf::Texture tileset;

        int tileNumber;
        std::vector<int> tabTile;

        Helico& joueur;



};
#endif

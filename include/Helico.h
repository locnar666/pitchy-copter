#ifndef HELICO_H
#define HELICO_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

/*!
 * \class Helico
 * \brief Representation de l'helicoptere.
 * \date 06 avril 2018
 *
 * \brief Permet de creer le sprit joueur vivant en début de partie puis de changer le sprit en
 * joueur mort à la fin de celle ci. Une recharge est egalement effectuee lorsque le
 * joueur recommence
 *
 */
class Helico : public sf::Sprite
{
    public:
        //Constructeur
        Helico();

        //Fonctions
        /*!
         * \brief Charge sprit joueur mort
        */
        void estMort();
        /*!
         * \brief Recharge sprit joueur de base
        */
        void recommence();
        /*!
         * \brief Bouger sur l'axe Y
         * \param window Fenetre de rendu SFML
        */
        void MoveY(sf::RenderWindow &window);

    private:
        //Variables de la classe en accès privé
        sf::Texture BabyTexture;

        bool m_enVie = true;
        //Map T_map;

};
#endif

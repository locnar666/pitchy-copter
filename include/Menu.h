#ifndef MENU_H
#define MENU_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

#define Max_Items 3

/*!
 * \class Menu
 * \brief Creation du menu principal
 * \date 06 avril 2018
 *
 * \brief Permet de creer la fenetre principale du menu
 *
 */

class Menu
{
    public:
        /*!
         * \brief Creation du menu
         * \param largeur pour la taille x de la fenetre
         * \param hauteur pour la taille y de la fenetre
         * \param posiX pour la position x de la caméra
         * \param posiY pour la position y de la caméra
        */
        Menu(float largeur, float hauteur, float posiX, float posiY);

        virtual ~Menu();

        /*!
         * \brief Dessine le menu
         * \param window fenêtre de rendu SFML
        */
        void draw(sf::RenderWindow &window);

        // Determine la couleur du text en fonction de la position de la souris
        /*!
         * \brief cherche position souris et en fonction de cette position,
         * colore le text pour simuler la séléction
         * \param positionSouris position de la souris dans la fenetre
        */
        float getPosition(sf::Vector2i positionSouris);

        //void mouvement();
        //void selectionItem();

    protected:

    private:

        sf::Font font;
        sf::Text menu[Max_Items];

        int itemSelection;
};

#endif // MENU_H

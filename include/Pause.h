#ifndef PAUSE_H
#define PAUSE_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

#define Max_Pause_Items 3

/*!
 * \class Pause
 * \brief Creation de la fenêtre de pause.
 * \date 06 avril 2018
 *
 * \brief Creer une fenetre avec transparence pour le menu pause
 *
 */

class Pause
{
    public:
        /*!
         * \brief Creation de la fenetre de pause
         * \param largeur pour la taille x de la fenetre
         * \param hauteur pour la taille y de la fenetre
         * \param posiX pour la position x de la caméra
         * \param posiY pour la position y de la caméra
        */
        Pause(float largeur, float hauteur, float posiX, float posiY);
        virtual ~Pause();

        /*!
         * \brief Dessine un rectangle avec transparence puis le text par dessus
         * \param window fenêtre de rendu SFML
        */
        void draw(sf::RenderWindow &window);
        /*!
         * \brief cherche position souris et en fonction de cette position,
         * colore le text pour simuler la séléction
         * \param positionSouris position de la souris dans la fenetre
        */
        float getPosition(sf::Vector2i positionSouris);

    protected:

    private:
        sf::Font font;
        sf::Text m_pause[Max_Pause_Items];
        sf::RectangleShape transparence;

        int itemSelection;

};

#endif // PAUSE_H

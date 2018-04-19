#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#define Max_GameOver_Items 3

/*!
 * \class GameOver
 * \brief Creation de la fenetre de fin de jeu.
 * \date 06 avril 2018
 *
 * \brief Creer une fenetre avec transparence pour lorsque le joueur meurt
 *
 */

class GameOver
{
    public:
        /*!
         * \brief Creation de la fenetre de fin de partie
         * \param largeur pour la taille x de la fenetre
         * \param hauteur pour la taille y de la fenetre
         * \param posiX pour la position x de la caméra
         * \param posiY pour la position y de la caméra
        */
        GameOver(float largeur, float hauteur, float posiX, float posiY);
        virtual ~GameOver();
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
        sf::Text m_gameOver[Max_GameOver_Items];
        sf::RectangleShape transparence;

        int itemSelection;
};

#endif // GAMEOVER_H

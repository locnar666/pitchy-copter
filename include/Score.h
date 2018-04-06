#ifndef SCORE_H
#define SCORE_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>
#include <sstream>

/*!
 * \class Score
 * \brief Creation du systeme de score (compte en seconde)
 * \date 06 avril 2018
 *
 * \brief Gestion de l'horloge qui fera office tableau des scores (chaque seconde = un point)
 *
 */

class Score : public sf::Text
{
    public:
        Score();
        /*!
         * \brief Récupère le temps depuis le lancement de la partie et le converti en string pour affichage text
        */
        void getTime();
        /*!
         * \brief Stop le temps (pause)
        */
        void stopTime();
        /*!
         * \brief Redemarre le temps (score) ex: nouvelle partie
        */
        void restart();

    protected:

    private:
        sf::Clock horloge;
        sf::Time temps_ecoule = sf::milliseconds(10);
        sf::Font police;

        std::string message;
        std::string nv_message;

        bool pauseScore = false;
};

#endif // SCORE_H

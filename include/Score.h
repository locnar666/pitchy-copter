#ifndef SCORE_H
#define SCORE_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <include/DataBase.h>
#include <include/DBPlayer.h>

#include <iostream>
#include <string>
#include <sstream>

/*!
 * \class Score
 * \brief Creation du systeme de score (compte en pixels)
 * \date 06 avril 2018
 *
 * \brief Gestion du score
 *
 */

class Score : public sf::Text
{
    public:
        Score();
        /*!
         * \brief recupere le score
        */
        float getTime();

        /*!
         * \brief Reinitialise le score à 0
        */
        void restart();




    protected:

    private:

        sf::Font police;

        float m_score;

        std::string message;

};

#endif // SCORE_H

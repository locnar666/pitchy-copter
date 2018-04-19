#ifndef JEU_H
#define JEU_H

#include <include/Helico.h>
#include <include/Map.h>
#include <include/Score.h>
#include <include/Menu.h>
#include <include/Pause.h>
#include <include/GameOver.h>
#include <include/DataBase.h>
#include <include/DBPlayer.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>

#include <sstream>

#define GAME_TITLE    "Pitchy copter"
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 480

/*!
 * \class Jeu
 * \brief Déroulement du jeu
 * \date 06 avril 2018
 * \version 1.0
 *
 * \brief Methodes correspondantes aux différents états de jeu (menu principal, jouer,
 * pause, gameOver)
 *
 */

class Jeu
{
    public:
        Jeu();

        /*!
         * \brief Lance la boucle principale du jeu
        */
        void lancer();
        /*!
         * \brief Affiche le menu principal. Raffraichi l'affichage.
        */
        void menuPrincipal();
        /*!
         * \brief Affiche l'écran pause
        */
        void menuPause();
        /*!
         * \brief Affiche l'écran de fin de partie
        */
        void gameOver();
        /*!
         * \brief Check etat du jeu. Recupere une variable m_etat qui fait réference à
         * une énumeration contenant les différents états
        */
        void check_etat();

    private:
        Helico joueur;
        Map tile_map;
        Score temps_score;

        sf::Event event;
        sf::RenderWindow window;
        sf::View camera;

        //Gestion des différents etats du jeu
        enum Etat{menu_principal, jouer_jeu, pause, game_over};

        int m_etat = 0;

        bool menu_pause;
        bool utilise_pause = false;
        bool retour_au_menu = false;
        bool estMort = false;
};

#endif // JEU_H

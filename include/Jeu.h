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
#include <include/Son.h>
#include <include/Option.h>
#include <include/Background.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>

#include <sstream>
#include <string>

#define GAME_TITLE    "Pitchy copter"
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 480

/*!
 * \class Jeu
 * \brief Deroulement du jeu
 * \date 06 avril 2018
 * \version 1.0
 *
 * \brief Methodes correspondantes aux differents etats de jeu (menu principal, jouer,
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
         * \brief Affiche l'ecran pause
        */
        void menuPause();
        /*!
         * \brief Affiche l'ecran de fin de partie
        */
        void gameOver();
        /*!
         * \brief Affiche l'ecran des options
        */
        void menu_option();
        /*!
         * \brief Check etat du jeu. Recupere une variable m_etat qui fait reference a
         * une enumeration contenant les differents etats
        */
        void check_etat();

        void entrerNom();

    private:
        Helico joueur;
        Map tile_map;
        Score temps_score;
        DataBase bdd;
        std::vector<DBPlayer*>* joueurs;

        Background background;

        sf::Event event;
        sf::RenderWindow window;
        sf::View camera;

        sf::Time time = sf::seconds(0.01f);;
        sf::Clock clock;

        //Gestion des différents etats du jeu
        enum Etat{menu_principal, jouer_jeu, pause, game_over, option, nomJoueur};

        int m_etat = 0;

        bool menu_pause;
        bool utilise_pause = false;
        bool retour_au_menu = false;
        bool estMort = false;
        bool jouer_zic;


        std::string nom_joueur;
};

#endif // JEU_H

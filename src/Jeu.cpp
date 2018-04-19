#include <include/Jeu.h>

#include <SFML/System/Vector2.hpp>

#include <iterator>
#include <vector>

#define X_SPEED      3
#define Y_SPEED_UP   -9
#define Y_SPEED_DOWN 3


Jeu::Jeu()
: tile_map(this->joueur,
           "images/TileSet/Middle_TileSet16X16.bmp",
           sf::Vector2u(16, 16),
           800, 30),
  window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 16), GAME_TITLE)
{
    this->window.setFramerateLimit(60);
    this->window.setVerticalSyncEnabled(true);
    this->window.setActive();

    //initialisation de la camera
    camera.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)); // Largeur map == nbTiles *32
}

void Jeu::check_etat() // !! TEMPORAIRE
{
    switch (m_etat)
    {
        case (menu_principal): this->menuPrincipal(); // case 0
        case (jouer_jeu): this->lancer();             // case 1
        case (pause): this->menuPause();              // case 2
        case (game_over): this->gameOver();           // case 3
    }
}

void Jeu::menuPrincipal()
{
    float camera_X = (camera.getCenter().x - (SCREEN_WIDTH/2));
    float camera_Y = (camera.getCenter().y - (SCREEN_HEIGHT/2));

    Menu menu(window.getSize().x, window.getSize().y, camera_X, camera_Y);

    if (retour_au_menu){ //replace le joueur au début du niveau...
    //réinitialisation de la camera
    camera.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
    this->joueur.setPosition(50, 10); // Largeur map == nbTiles *32
    this->temps_score.setPosition(630, 10);
    }

    while (window.isOpen())
    {
        while(window.pollEvent(event))
        {
            sf::Vector2i localPosition = sf::Mouse::getPosition(window);
            menu.getPosition(localPosition);

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (menu.getPosition(localPosition) == 0){
                    m_etat = 1;
                    this->check_etat();}
                    if (menu.getPosition(localPosition) == 1){
                    }// Affiche les options;
                    if (menu.getPosition(localPosition) == 2){
                    exit(0);} // Quitte le jeu...
                }
            }
        }
        window.clear();
        menu.draw(window);
        window.display();
    }
}

void Jeu::menuPause() // !!!!!!!!!!!!!!!!-> Score qui continu à tourner apres menu pause <-!!!!!!!!!!!!!!!!!!
{
    float camera_X = (camera.getCenter().x - (SCREEN_WIDTH/2));
    float camera_Y = (camera.getCenter().y - (SCREEN_HEIGHT/2));

    Pause e_pause(window.getSize().x, window.getSize().y, camera_X, camera_Y);

    while(window.isOpen())
    {
        while (menu_pause)
        {
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                {
                    menu_pause = false;
                    std::cout << "je quitte le menu pause" << std::endl;
                    m_etat = 1;
                    this->check_etat();
                }

                sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                e_pause.getPosition(localPosition);

                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        if (e_pause.getPosition(localPosition) == 0){
                        m_etat = 0;
                        utilise_pause = false;
                        retour_au_menu = true; //reinitialise le jeu...
                        this->check_etat();}// menu principal
                        if (e_pause.getPosition(localPosition) == 1){
                        }// Affiche les options;
                        if (e_pause.getPosition(localPosition) == 2){
                        exit(0);} // Quitte le jeu...
                    }
                }
            }

        this->window.clear();
        //la couche "pause est la derniere à etre dessinée
        this->window.draw(this->tile_map);
        this->window.draw(this->joueur);
        this->window.draw(this->temps_score);

        e_pause.draw(window);

        this->window.display();
        }
    }
}

void Jeu::gameOver()
{
    float camera_X = (camera.getCenter().x - (SCREEN_WIDTH/2));
    float camera_Y = (camera.getCenter().y - (SCREEN_HEIGHT/2));

    GameOver e_gameOver(window.getSize().x, window.getSize().y, camera_X, camera_Y);

    while(window.isOpen())
    {
        while (window.pollEvent(event))
        {
            sf::Vector2i localPosition = sf::Mouse::getPosition(window);
            e_gameOver.getPosition(localPosition);

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (e_gameOver.getPosition(localPosition) == 1)// menu principal
                    { // Reinitialise le jeu...
                        m_etat = 0;
                        retour_au_menu = true;
                        estMort = false;
                        this->joueur.recommence();
                        this->check_etat();
                    }
                    if (e_gameOver.getPosition(localPosition) == 2)
                    { // Quitte le jeu...
                        exit(0);
                    }
                }
            }
        this->window.clear();
        //la couche "GameOver" est la derniere à etre dessinée
        this->window.draw(this->tile_map);
        this->window.draw(this->joueur);
        this->window.draw(this->temps_score);

        e_gameOver.draw(window);

        this->window.display();
        }
    }
}

void Jeu::lancer()
{
    //descente automatique du joueur
    bool joueur_descend = true;

    if (!utilise_pause)
    {
        this->temps_score.restart();
    }
    utilise_pause = false;

    while(window.isOpen())
    {

        this->temps_score.getTime();
        this->joueur.move(X_SPEED, Y_SPEED_DOWN);

        //Gestion caméra
        camera.move(X_SPEED, 0);
        window.setView(camera);

        //Gestion collision en fonction du N° de la Tuile -> n° <= 4 == death
        if (this->tile_map.indiceTile())
        {
            std::cout << "dead" << std::endl;
            estMort = true;
            m_etat = 3;
            this->joueur.estMort();
            //this->temps_score.stopTime();
            this->temps_score.getTime();
            this->check_etat();
        }

        while(window.pollEvent(event))
        {
            //Mouvement joueur
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    joueur_descend = false;
                }
            } else if(event.type == sf::Event::MouseButtonReleased)
                joueur_descend = true;
            if (event.type == sf::Event::Closed)
                window.close();

            // !!!!! Pause -- TEMPORAIRE
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                m_etat = 2;
                menu_pause = true;
                utilise_pause = true; // gestion du score - evite de restart apres une pause
                this->temps_score.stopTime();
                this->check_etat();
            }
        }

        if(!joueur_descend)
        {
        //mouvement
        this->joueur.move(0, Y_SPEED_UP);
        }
        this->temps_score.move(X_SPEED, 0);

        //sf::View currentView = window.getView();

        // std::cout << this->joueur.getPosition().x << ", " << this->joueur.getPosition().y << std::endl;
        this->window.clear();


        this->window.draw(this->tile_map);
        this->window.draw(this->joueur);
        this->window.draw(this->temps_score);


        this->window.display();

    }
}
/*
#include <iostream>
#include "database.h"
#include <vector>
#include "produit.h"

using namespace std;

int main()
{
    database bdd;
    bdd.openDatabase();

    bdd.executeQuery("CREATE TABLE IF NOT EXISTS joueurs (nom TEXT, score FLOAT)");
    //bdd.insertProduit("Banane", 1.3, 10);
    //bdd.insertProduit("Avocat", 2.5, 1);
    //bdd.insertProduit("Tomate", 1., 666);

    std::vector<Produit*>* produits = bdd.getAllProduits();
    for (int i=0; i<produits->size(); i++)
    {
        std::cout << (*produits)[i]->nom << " " << (*produits)[i]->prix << std::endl;
    }

    (*produits)[0]->nom = "Toto";
    bdd.updateProduit((*produits)[0]);

    bdd.deleteProduit((*produits)[0]->id);

    bdd.closeDatabase();

    return 0;
}*/



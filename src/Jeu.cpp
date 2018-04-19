#include <include/Jeu.h>

#include <SFML/System/Vector2.hpp>

#include <iterator>
#include <vector>

#define X_SPEED      3
#define Y_SPEED_UP   -9
#define Y_SPEED_DOWN 3


Jeu::Jeu()
: tile_map(this->joueur,
           "images/TileSet/Retest_Middle2_tileSet16x16.png",
           sf::Vector2u(16, 16),
           1000, 30),
  window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 16), GAME_TITLE)
{
    this->window.setFramerateLimit(60);
    this->window.setVerticalSyncEnabled(true);
    this->window.setActive();

    //initialisation de la camera
    camera.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)); // Largeur map == nbTiles *32
}

void Jeu::check_etat()
{
    switch (m_etat)
    {
        case (menu_principal): this->menuPrincipal(); // case 0
        case (jouer_jeu): this->lancer();             // case 1
        case (pause): this->menuPause();              // case 2
        case (game_over): this->gameOver();           // case 3
        case (option): this->menu_option();           // case 4
        case (nomJoueur): this->entrerNom();          // case 5
    }
}

void Jeu::menu_option()
{
    float camera_X = (camera.getCenter().x - (SCREEN_WIDTH/2));
    float camera_Y = (camera.getCenter().y - (SCREEN_HEIGHT/2));

    Option e_option(window.getSize().x, window.getSize().y, camera_X, camera_Y);

    while (window.isOpen())
    {
        while(window.pollEvent(event))
        {
            sf::Vector2i localPosition = sf::Mouse::getPosition(window);
            e_option.getPosition(localPosition);

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (e_option.getPosition(localPosition) == 0 ||
                        e_option.getPosition(localPosition) == 1)
                    {
                        bool test = e_option.changeEtatMusique();
                        if (test == false)
                        {
                            jouer_zic = false;
                        }
                        else
                        {
                            jouer_zic = true;
                        }
                    }
                    if (e_option.getPosition(localPosition) == 2)
                    {
                        m_etat = 0;
                        this->check_etat();
                    } // Quitte le jeu...
                }
            }
        }

        this->window.clear();

        e_option.draw(window);

        this->window.display();
    }

}

void Jeu::menuPrincipal()
{
    float camera_X = (camera.getCenter().x - (SCREEN_WIDTH/2));
    float camera_Y = (camera.getCenter().y - (SCREEN_HEIGHT/2));

    Menu menu(window.getSize().x, window.getSize().y, camera_X, camera_Y);

    if (retour_au_menu)
    {   //replace le joueur au début du niveau...
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
                    if (menu.getPosition(localPosition) == 0)
                    {
                        //jouer
                        m_etat = 1;
                        this->check_etat();
                    }
                    if (menu.getPosition(localPosition) == 1)
                    {
                        m_etat = 4;
                        this->check_etat();
                    }// Affiche les options;
                    if (menu.getPosition(localPosition) == 2)
                    {
                    exit(0);
                    } // Quitte le jeu...
                }
            }
        }
        this->window.clear();
        menu.draw(window);
        this->window.display();
    }
}

void Jeu::menuPause()
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

        e_pause.draw(window);//dessine un rectangle en transparence

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
                        this->temps_score.setCharacterSize(20);
                        this->joueur.recommence();
                        this->check_etat();
                    }
                    if (e_gameOver.getPosition(localPosition) == 2)
                    { // Quitte le jeu...
                        exit(0);
                    }
                }
            }
        }

        //******************* highScore *****************************
        joueurs = bdd.getAllPlayers();


        sf::Font font;
        sf::Text tableauScore[10];

        if (font.loadFromFile("images/Polices/ariblk.ttf"))
        {
            // Gestion erreur
        }

        std::stringstream ss[10];
        std::string tabJoueurs[10];

        for (int i = 0; i <= 9; i++)
        {

            //Convertir Float en String
            float scoreJoueur = (*joueurs)[i]->score;
            std::ostringstream tempsScore;
            tempsScore << scoreJoueur;

            ss[i] << i +1 << " /. " <<  (*joueurs)[i]->nom << " -> " <<tempsScore.str();

            tabJoueurs[i] = ss[i].str();

            tableauScore[i].setFont(font);
            tableauScore[i].setColor(sf::Color::Green);
            tableauScore[i].setString(tabJoueurs[i]);
            tableauScore[i].setCharacterSize(18);
            tableauScore[i].setPosition(sf::Vector2f(camera_X + (window.getSize().x/1.4), window.getSize().y / (9+1) *(i)));
        }

        this->temps_score.setCharacterSize(30);

        //repositionne le score en dessous du gameover
        this->temps_score.setPosition(sf::Vector2f(camera_X + (window.getSize().x/7), window.getSize().y / (3 + 1) *1));

        this->window.clear();

        this->window.draw(this->tile_map);
        this->window.draw(this->joueur);


        //la couche "GameOver" est la derniere à etre dessinée
        e_gameOver.draw(window);

        //Affiche liste des highscore
        for (int j = 0; j < 10; j++)
        {
            this->window.draw(tableauScore[j]);
        }


        this->window.draw(this->temps_score);


        this->window.display();
    }
}


void Jeu::entrerNom()
{

    float camera_X = (camera.getCenter().x - (SCREEN_WIDTH/2));
    float camera_Y = (camera.getCenter().y - (SCREEN_HEIGHT/2));

    sf::Text nom;
    sf::Text votreNom;
    sf::Font font;

    if (font.loadFromFile("images/Polices/ariblk.ttf"))
    {
        // Gestion erreur
    }
    nom.setFont(font);
    votreNom.setFont(font);

    nom.setColor(sf::Color::Green);
    nom.setCharacterSize(18);
    nom.setPosition(sf::Vector2f(camera_X + (window.getSize().x/2.5), window.getSize().y / 2 *(1)));

    votreNom.setString("Entrez votre nom: ");
    votreNom.setColor(sf::Color::Green);
    votreNom.setCharacterSize(18);
    votreNom.setPosition(sf::Vector2f(camera_X + (window.getSize().x/20), window.getSize().y / 2 *(1)));

    this->window.clear();
    this->window.draw(votreNom);
    this->window.display();


    while(window.isOpen())
    {

        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode < 128)
                {
                    nom_joueur += event.text.unicode;

                    nom.setString(nom_joueur);

                    this->window.clear();

                    this->window.draw(nom);
                    this->window.draw(votreNom);

                    this->window.display();
                }
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Return)
                {
                    camera.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
                    m_etat = 1;
                    utilise_pause = true;
                    this->check_etat();
                }
            }
        }
    }
}

void Jeu::lancer()
{
    //initialisation musique/bruitage
    Son zic;

    //Place Background au début du jeu
    this->background.setPosition(sf::Vector2f(0, 0));

    //Ouvre la base de données
    this->bdd.openDatabase();

    //descente automatique du joueur
    bool joueur_descend = true;

    if (!utilise_pause)
    {
        m_etat = 5;
        nom_joueur = "";
        this->temps_score.restart();
        //this->window.clear();
        this->check_etat();
    }

    utilise_pause = false;

    while(window.isOpen())
    {
        if (jouer_zic)
        zic.playSonDescend();

        //*********** Augmentation vitesse joueur en fonction du score **************
        float score = this->temps_score.getTime();

        background.move(1,0);

        if (score < 2500)
        {
            this->joueur.move(X_SPEED, Y_SPEED_DOWN);
            this->temps_score.move(X_SPEED, 0);

            //Gestion caméra
            camera.move(X_SPEED, 0);
            window.setView(camera);
        }
        else if((score > 2500) && (score < 5000))
        {
            this->joueur.move(X_SPEED +1, Y_SPEED_DOWN);
            this->temps_score.move(X_SPEED+1, 0);

            camera.move(X_SPEED +1, 0);
            window.setView(camera);
        }
        else if (score > 5000)
        {
            this->joueur.move(X_SPEED +2, Y_SPEED_DOWN);
            this->temps_score.move(X_SPEED+2, 0);

            camera.move(X_SPEED +2, 0);
            window.setView(camera);
        }

        //Gestion collision en fonction du N° de la Tuile -> n°5 || 10 -> 20 || 25 == death
        if (this->tile_map.indiceTile())
        {
            estMort = true;
            m_etat = 3; //revoie à "game over"

            this->joueur.estMort(); //sprit joueur mort

            //si musique activée
            if (jouer_zic)
            zic.playSonMort();

            //récupération du score
            this->temps_score.getTime();


            //travail sur BdD
            this->bdd.executeQuery("CREATE TABLE IF NOT EXISTS players (nom TEXT, score DOUBLE)");

            //this->bdd.insertPlayer(nom_joueur, score);

            //récupération des 10 HighScores
            joueurs = bdd.getAllPlayers();

            for (int i=0; i<joueurs->size(); i++)
            {
                // condition: recuperer scores joueur, si score actuel > au plus bas des 10 score alors:
                if (score >(*joueurs)[i]->score)
                {
                    this->bdd.insertPlayer(nom_joueur, score);
                    //Si insertion, alors suppression du 10eme
                    if ((joueurs->size()== 10))
                    {
                        int id_joueur_supp = (*joueurs)[9]->id;
                        this->bdd.deletePlayer(id_joueur_supp);
                    }
                    break;
                }
            }


            //m_etat = 3 -> GameOver
            this->check_etat();
        }

        while(window.pollEvent(event))
        {
            if (jouer_zic)
            zic.playSonDescend();

            //Mouvement joueur
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (jouer_zic)
                    zic.playSonMonte();
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
                this->check_etat();
            }
        }

        if(!joueur_descend)
        {
        //mouvement
        this->joueur.move(0, Y_SPEED_UP);
        }

        this->window.clear();

        this->window.draw(background);
        this->window.draw(this->tile_map);
        this->window.draw(this->joueur);
        this->window.draw(this->temps_score);

        this->window.display();

    }
}


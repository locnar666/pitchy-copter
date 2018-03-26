#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "main.h"
#include "Helico.h"
#include "Obstacle.h"
#include "map.h"
#include <iostream>

using namespace std;
using namespace sf;

int main(int argc, char *argv[])
{
    // Création d'une fenêtre en SFML
    RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32),
    "Pitchy Copter");

    //Limite les fps à 60 images / seconde
    window.setFramerateLimit(60);

    //On active la synchro verticale
    window.setVerticalSyncEnabled(true);

    //Ouverture d'un fichier en lecture
    ifstream monFlux("Map/Carte.txt");

    vector<int> nombres(istream_iterator<int>(monFlux),istream_iterator<int>{});

    //Helico Baby;
    Helico joueur(50, 10);

    Map tileMap(joueur);
    if (!tileMap.load("images/TileSet/SetOfTilessss.bmp", Vector2u(32, 32), nombres, 100, 15))
        return -1;



    cout << nombres[1] << " " << nombres[101] << " " << nombres[1401] << endl;

    sf::Event event;

    sf::View camera;
    camera.reset(sf::FloatRect(0, 0, 800, 480));

    // Boucle infinie, principale, du jeu
    while (window.isOpen())
    {
        /*while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }*/

        //sf::Vector2i pixelPos = Baby.getPosition();
        // conversion en coordonnées "monde"
        //sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

        joueur.MoveY(window);
        joueur.Vie();

        if (tileMap.indiceTile(nombres, 100, 15) == true)
        {
            cout << "mort!" << endl;
        }
        //Baby.Collision(tileMap);
        //Baby.getposition();

        camera.move(1, 0);

        window.setView(camera);





        /** DESSIN - DRAW **/

        //On efface l'écran et on l'affiche
        window.clear();

        //Affichage map
        window.draw(tileMap);

        //Affichage Sprit
        joueur.drawBaby(window);

        sf::View currentView = window.getView();

        window.display();
    }

//Utile? DESTRUCTOR
delete &joueur; //Seulement si pointeur

// On quitte
return 0;

}

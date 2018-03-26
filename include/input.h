#ifndef INPUT_H
#define INPUT_H

#include "Helico.h"

#include <SFML/Graphics.hpp>



class Input
{

//Structures
    public:

    //Constructeur
    Input();

    //Fonctions
    int getInput(sf::RenderWindow &window);
    int babyMove ();

    private:
    //Variables de la classe en accès privé
    sf::Event event;
    //bool monte = false;
    //Helico Baby;


};
#endif

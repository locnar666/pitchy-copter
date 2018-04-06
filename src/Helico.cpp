
#include <include/Helico.h>
#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;


//Constructeur
Helico::Helico()
{
    if (!BabyTexture.loadFromFile("images/BabyCopter.png"))
    {
    // Erreur
        cout << "Erreur durant le chargement de l'image de Baby Copter." << endl;
    }
    else
        this->setTexture(BabyTexture);

    this->setPosition(50, 0);
}

void Helico::estMort()
{
    //Reste à gerer la fin de partie
    if (!BabyTexture.loadFromFile("images/Mort.png"))
    {
    // Erreur
        cout << "Erreur durant le chargement de l'image de Baby Copter." << endl;
    }
    else
        this->setTexture(BabyTexture);
}

void Helico::recommence()
{
    if (!BabyTexture.loadFromFile("images/BabyCopter.png"))
    {
    // Erreur
        cout << "Erreur durant le chargement de l'image de Baby Copter." << endl;
    }
    else
        this->setTexture(BabyTexture);
}

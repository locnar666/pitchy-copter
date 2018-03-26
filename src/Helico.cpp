#include "Helico.h"
#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;


//Constructeur
Helico::Helico(int axeHelicox, int axeHelicoy) : m_axeHelicox(axeHelicox), m_axeHelicoy(axeHelicoy)
{
    int m_axeHelicox = axeHelicox;
    int m_axeHelicoy = axeHelicoy;

    if (!BabyTexture.loadFromFile("images/BabyCopter.png"))
    {
    // Erreur
        cout << "Erreur durant le chargement de l'image de Baby Copter." << endl;
    }
    else
        this->setTexture(BabyTexture);

    this->setPosition(m_axeHelicox, m_axeHelicoy);
}

void Helico::Vie()
{
    //Reste à gerer la fin de partie
    if (m_enVie == false)
    {
        if (!BabyTexture.loadFromFile("images/Mort.png"))
        {
        // Erreur
            cout << "Erreur durant le chargement de l'image de Baby Copter." << endl;
        }
        else
            this->setTexture(BabyTexture);
    }
}

void Helico::MoveY(sf::RenderWindow &window)
{
    sf::Event event;

    //m_axeHelicox +1 pour bouger avec la camera, pour le moment (temporaire)
    this->setPosition(m_axeHelicox+=1, m_axeHelicoy += 4);

    //Trouver moyen de mettre l"Event" dans le main...
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                //cout << "je monte" << endl;
                m_monte = true;
            }
        }
        if (event.type == sf::Event::MouseButtonReleased)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                //cout << "je descend" << endl;
                m_monte = false;
            }
        }
    }
    if (m_monte == true)
    {
        this->setPosition(m_axeHelicox, (m_axeHelicoy -= 9));
    }


    if ((m_axeHelicoy < 0) || (m_axeHelicoy > 480))
    {
        //cout << "Je meurs!!!" << endl;
        m_enVie = false;
    }
}

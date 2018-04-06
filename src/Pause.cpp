#include "Pause.h"

Pause::Pause(float largeur, float hauteur, float posiX, float posiY)
{

    //ctor
    transparence.setPosition(posiX, posiY);
    transparence.setSize(sf::Vector2f(800, 480));
    transparence.setFillColor(sf::Color(255, 255, 255, 120));

    if (font.loadFromFile("images/Polices/ariblk.ttf"))
    {
        // Gestion erreur
    }

    m_pause[0].setFont(font);
    m_pause[0].setColor(sf::Color::Black);
    m_pause[0].setString("Menu Principal");
    m_pause[0].setPosition(sf::Vector2f(posiX + (largeur/3), hauteur / (Max_Pause_Items + 1) *1));

    m_pause[1].setFont(font);
    m_pause[1].setColor(sf::Color::Black);
    m_pause[1].setString("Options");
    m_pause[1].setPosition(sf::Vector2f(posiX + (largeur/3), hauteur / (Max_Pause_Items + 1) *2));

    m_pause[2].setFont(font);
    m_pause[2].setColor(sf::Color::Black);
    m_pause[2].setString("Quitter");
    m_pause[2].setPosition(sf::Vector2f(posiX + (largeur/3), hauteur / (Max_Pause_Items + 1) *3));


    itemSelection = 0;
}

Pause::~Pause()
{
    //dtor
}

void Pause::draw(sf::RenderWindow &window)
{
    window.draw(transparence);
    for (int i = 0; i < Max_Pause_Items; i++)
    {
        window.draw(m_pause[i]);
    }
}

float Pause::getPosition(sf::Vector2i positionSouris)
{
    for (int j = 0; j < Max_Pause_Items; j++)
    {
        float position_text = m_pause[j].getPosition().y;

        if ((positionSouris.y <= (position_text += 40)) &&
            (positionSouris.y >= (position_text -= 40)))
        {
            m_pause[j].setColor(sf::Color::Red);
            return itemSelection = j;
        }
        else
        {
            m_pause[j].setColor(sf::Color::Black);
        }
    }
}

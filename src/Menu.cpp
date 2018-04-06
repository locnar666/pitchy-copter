/**
 * \file Menu.cpp
 * \brief Creation du menu principal
 * \date 06 avril 2018
 *
 * Permet de creer la fenetre principale du menu
 *
 */

#include "Menu.h"

Menu::Menu(float largeur, float hauteur,float posiX, float posiY)
{
    //ctor
    if (font.loadFromFile("images/Polices/ariblk.ttf"))
    {
        // Gestion erreur
    }

    menu[0].setFont(font);
    menu[0].setColor(sf::Color::White);
    menu[0].setString("Jouer");
    menu[0].setPosition(sf::Vector2f(posiX + (largeur/3), hauteur / (Max_Items + 1) *1));

    menu[1].setFont(font);
    menu[1].setColor(sf::Color::White);
    menu[1].setString("Options");
    menu[1].setPosition(sf::Vector2f(posiX + (largeur/3), hauteur / (Max_Items + 1) *2));

    menu[2].setFont(font);
    menu[2].setColor(sf::Color::White);
    menu[2].setString("Quitter");
    menu[2].setPosition(sf::Vector2f(posiX + (largeur/3), hauteur / (Max_Items + 1) *3));

    itemSelection = 0;
}

Menu::~Menu()
{
    //dtor
}

void Menu::draw(sf::RenderWindow &window)
{
    for (int i = 0; i < Max_Items; i++)
    {
        window.draw(menu[i]);
    }
}

float Menu::getPosition(sf::Vector2i positionSouris)
{
    for (int j = 0; j < Max_Items; j++)
    {
        float position_text = menu[j].getPosition().y;

        if ((positionSouris.y <= (position_text += 40)) &&
            (positionSouris.y >= (position_text -= 40)))
        {
            menu[j].setColor(sf::Color::Red);
            return itemSelection = j;
        }
        else
        {
            menu[j].setColor(sf::Color::White);
        }
    }
}

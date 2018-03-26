/*#include "input.h"
#include "input.h"

using namespace std;
using namespace sf;

//Constructeur
Input::Input()
{

}

//Fonctions
int Input::getInput(sf::RenderWindow &window)
{
    // Tant qu'il y a des évènements à traiter...
    while (window.pollEvent(event))
    {

        while (window.pollEvent(event))
        {
           if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    return 1;
                }
            }
            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    return 0;
                }

            }
        }
    }

}
int Input::babyMove()
{

sf::RenderWindow window;

    // Tant qu'il y a des évènements à traiter...
    while (window.pollEvent(event))
    {

        while (window.pollEvent(event))
        {
           if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    return true;
                }
            }
            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    return false;
                }

            }
        }
    }

}*/

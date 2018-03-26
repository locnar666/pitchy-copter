#ifndef HELICO_H
#define HELICO_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>


class Helico : public sf::Sprite
{
    public:
        //Constructeur
        Helico(int axeHelicox, int axeHelicoy);

        //Fonctions
        void Vie();
        void MoveY(sf::RenderWindow &window);

    private:
        //Variables de la classe en accès privé
        sf::Texture BabyTexture;

        int m_axeHelicox;
        int m_axeHelicoy;

        bool m_enVie = true;
        bool m_monte = false;
        //Map T_map;

};
#endif

#ifndef TEXTURE_H
#define TEXTURE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>


class Texture
{
public:

//Constructeur
Texture();

//Fonctions
void drawTexture(sf::RenderTexture &texture);


private:
//Variables de la classe en accès privé

//Background
sf::Texture texture;


};
#endif

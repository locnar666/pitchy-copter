#include "GameOver.h"

GameOver::GameOver(float largeur, float hauteur, float posiX, float posiY)
{
    //ctor
    transparence.setPosition(posiX, posiY);
    transparence.setSize(sf::Vector2f(800, 480));
    transparence.setFillColor(sf::Color(255, 255, 255, 120));

    if (font.loadFromFile("images/Polices/ariblk.ttf"))
    {
        // Gestion erreur
    }

    m_gameOver[0].setFont(font);
    m_gameOver[0].setColor(sf::Color::Red);
    m_gameOver[0].setCharacterSize(68);
    m_gameOver[0].setString("Game Over");
    m_gameOver[0].setPosition(sf::Vector2f(posiX + (largeur/4), hauteur / (Max_GameOver_Items + 1) *0.35));

    m_gameOver[1].setFont(font);
    m_gameOver[1].setColor(sf::Color::Black);
    m_gameOver[1].setString("Menu principal");
    m_gameOver[1].setPosition(sf::Vector2f(posiX + (largeur/3), hauteur / (Max_GameOver_Items + 1) *2));

    m_gameOver[2].setFont(font);
    m_gameOver[2].setColor(sf::Color::Black);
    m_gameOver[2].setString("Quitter");
    m_gameOver[2].setPosition(sf::Vector2f(posiX + (largeur/3), hauteur / (Max_GameOver_Items + 1) *2.75));

    itemSelection = 1;
}

GameOver::~GameOver()
{
    //dtor
}

void GameOver::draw(sf::RenderWindow &window)
{
    window.draw(transparence);
    for (int i = 0; i < Max_GameOver_Items; i++)
    {
        window.draw(m_gameOver[i]);
    }
}

float GameOver::getPosition(sf::Vector2i positionSouris)
{
    for (int j = 1; j < Max_GameOver_Items; j++)
    {
        float position_text = m_gameOver[j].getPosition().y;

        if ((positionSouris.y <= (position_text += 40)) &&
            (positionSouris.y >= (position_text -= 40)))
        {
            m_gameOver[j].setColor(sf::Color::White);
            return itemSelection = j;
        }
        else
        {
            m_gameOver[j].setColor(sf::Color::Black);
        }
    }
}

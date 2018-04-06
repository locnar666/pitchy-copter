#include "Score.h"

Score::Score()
{
    //ctor
    if (!police.loadFromFile("images/Polices/ariblk.ttf"))
    {
        std::cout << "erreur lors du chargement de police..." << std::endl;
    }

    //mise en place d'un Shape "text"
    this->setFont(police);
    this->setCharacterSize(18);
    this->setColor(sf::Color::Red);
    this->setPosition(630, 10);

    this->getTime();
}

void Score::getTime()
{
    if (!police.loadFromFile("images/Polices/ariblk.ttf"))
    {
        std::cout << "erreur lors du chargement de police..." << std::endl;
    }

    temps_ecoule = horloge.getElapsedTime();

    //conversion float -> string
    float sec = temps_ecoule.asSeconds();
    std::ostringstream temps;
    temps << sec;
    message = "score: " + temps.str();

    if (pauseScore == true)
    {
        this->setString(nv_message);
        pauseScore = false;
    }
    else
    {
        this->setString(message);
    }
}

void Score::stopTime()
{
    nv_message = message;
    //horloge.restart();

    pauseScore = true;
    this->getTime();
    //std::cout << nv_message << std::endl;
    //this->setString(nv_message);

}

void Score::restart()
{
    horloge.restart();
}

/*void Score::pause_score()
{

}*/

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
    this->setCharacterSize(20);
    this->setColor(sf::Color::Red);
    this->setPosition(630, 10);

    this->getTime();
}

float Score::getTime()
{
    m_score = (this->getPosition().x) - 630;

    //conversion float -> string
    std::ostringstream temps;
    temps << m_score;
    message = "score: " + temps.str();


    this->setString(message);
    return m_score;
}


void Score::restart()
{
    m_score = 0;
}




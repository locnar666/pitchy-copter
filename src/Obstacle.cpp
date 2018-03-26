#include "Obstacle.h"

Obstacle::Obstacle(int axeObstaclex, int axeObstacley, int axePositionx, int axePositiony) : m_axeObstaclex(axeObstaclex), m_axeObstacley(axeObstacley), m_axePositionx(axePositionx), m_axePositiony(axePositiony)
{
    //ctor
    obstacle.setSize(sf::Vector2f(m_axeObstaclex, m_axeObstacley));
    obstacle.setPosition(m_axePositionx, m_axePositiony);
    obstacle.setFillColor(sf::Color(100, 25, 200));
    //std::cout << "je cree" << std::endl;
}

Obstacle::~Obstacle()
{
    //dtor
}

void Obstacle::moveObstacle()//(int newAxex, int newAxey)
{
    m_newAxex = m_axePositionx -=4;
    m_newAxey = m_axePositiony;
    if (m_axePositiony == 170)
    {
        HautouBas = true;
    }
    if (m_axePositiony == 0)
    {
        HautouBas = false;
    }

    obstacle.setPosition(m_newAxex, m_newAxey);


    if (m_newAxex <=0)
    {
        std::cout << m_axePositionx << std::endl;
        std::cout << m_newAxey << std::endl;
        m_axePositionx = 800;

        if (HautouBas == true)
        {
            m_axePositiony += 15;
            if (m_newAxey >= 270)
            {
                m_axePositiony = 170;
            }
            obstacle.move(m_newAxex, m_newAxey);
        }

        if (HautouBas == false)
        {
            m_axePositiony -= 15;
            if (m_newAxey <= -200)
            {
                m_axePositiony = 170;
            }
            obstacle.move(m_newAxex, m_newAxey);
        }
    }
}


void Obstacle::drawObstacle(sf::RenderWindow &window)
{
    window.draw(obstacle);
    //std::cout << "je dessine" << std::endl;
}

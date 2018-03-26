#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <SFML/Graphics.hpp>
#include <iostream>

class Obstacle
{
    public:
        Obstacle(int axeObstaclex, int axeObstacley, int axePositionx, int axePositiony);
        virtual ~Obstacle();
        void drawObstacle(sf::RenderWindow &window);
        void moveObstacle();//(int newAxex, int newAxey);


    protected:

    private:

        int m_axeObstaclex;
        int m_axeObstacley;
        int m_axePositionx;
        int m_axePositiony;
        int m_newAxex;
        int m_newAxey;
        bool HautouBas;

        sf::RectangleShape obstacle;


};

#endif // OBSTACLE_H

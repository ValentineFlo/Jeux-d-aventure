#pragma once
#include "Region.h"

class ResuciteurRegion : public IRegion
{
public:

    ResuciteurRegion(float x, float y) : IRegion(x, y) {}

    void exe() override
    {
        std::cout << "lets goooooooo exe resuciteur" << std::endl;
    }

    void update() override
    {
        std::cout << "lets goooooooo update resuciteur" << std::endl;
    }

    void render() override
    {
        std::cout << "lets goooooooo render resuciteur" << std::endl;
    }

    float getX() const { return m_x; }
    float getY() const { return m_y; }

private:
    float m_x, m_y;

};
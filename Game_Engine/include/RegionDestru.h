#pragma once
#include "Region.h"

class DestructeurRegion : public IRegion
{
public:

    DestructeurRegion(float x, float y) : IRegion(x, y) {}

    void exe() override
    {
        std::cout << "lets goooooooo exe destru" << std::endl;
    }

    void update() override
    {
        std::cout << "lets goooooooo update destru" << std::endl;
    }

    void render() override
    {

        std::cout << "lets goooooooo render destru" << std::endl;
    }

    float getX() const { return m_x; }
    float getY() const { return m_y; }

private:
    float m_x, m_y;

};

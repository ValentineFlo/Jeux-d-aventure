#pragma once
#include "Region.h"

class DestructeurRegion : public IRegion
{
public:

    DestructeurRegion(float x, float y, float width, float height) : IRegion(x, y, width, height) {}


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

};

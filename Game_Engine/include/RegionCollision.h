#pragma once
#include "Region.h"

class CollisionRegion : public IRegion
{
public:

    CollisionRegion(float x, float y) : IRegion(x, y) {}

    void exe() override
    {
        std::cout << "lets goooooooo exe collision" << std::endl;
    }

    void update() override
    {
        std::cout << "lets goooooooo update collision" << std::endl;
    }

    void render() override
    {

        std::cout << "lets goooooooo render collision" << std::endl;
    }

	float getX() const { return m_x; }
	float getY() const { return m_y; }

private:
	float m_x, m_y;
};

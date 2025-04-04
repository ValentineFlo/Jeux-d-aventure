#pragma once
#include "Region.h"

class PlateformeRegion : public IRegion
{
public:

	PlateformeRegion(float x, float y) : IRegion(x, y) {}

    void exe() override
    {
        std::cout << "lets goooooooo exe plateforme" << std::endl;
    }

    void update() override
    {
        std::cout << "lets goooooooo update plateforme" << std::endl;
    }

    void render() override
    {

        std::cout << "lets goooooooo render plateforme" << std::endl;
    }

	float getX() const { return m_x; }
	float getY() const { return m_y; }

private:
	float m_x, m_y;
};
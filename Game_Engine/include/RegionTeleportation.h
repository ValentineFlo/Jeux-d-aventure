#pragma once
#include "Region.h"

class TeleportationRegion : public IRegion
{
public:

	TeleportationRegion(float x, float y, float width, float height, IComposite* scene)
        : IRegion(x, y, width, height, scene) 
    {}

    void update() override
    {
        std::cout << "lets goooooooo update teleportation" << std::endl;
    }

    void render() override
    {

        std::cout << "lets goooooooo render teleportation" << std::endl;
    }

	float getX() const { return m_x; }
	float getY() const { return m_y; }

};
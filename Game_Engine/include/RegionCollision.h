#pragma once
#include "Region.h"

class CollisionRegion : public IRegion
{
public:

    CollisionRegion(float x, float y, float width, float height, IComposite* scene) 
        : IRegion(x, y, width, height, scene) 
    {}

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

};

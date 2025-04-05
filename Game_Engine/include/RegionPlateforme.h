#pragma once
#include "Region.h"

class PlateformeRegion : public IRegion
{
public:

	PlateformeRegion(float x, float y, float width, float height, IComposite* scene) : IRegion(x, y, width, height, scene) {}


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

    void FixPosition() override
    {

        float decalX = m_scene->getRoot()->getScene()->getLeftTopCorner().x;
        float decalY = m_scene->getRoot()->getScene()->getLeftTopCorner().y;


        float x = (m_scene->getRoot()->getScene()->getBackgroundSize().x / 2) - m_x;
        float y = (m_scene->getRoot()->getScene()->getBackgroundSize().y / 2) - m_y;

        float dotposX = decalX - x;
        float dotposY = decalY - y;

        m_shape.setPosition(dotposX, dotposY);
    }

private:
	sf::RectangleShape m_shape;

};
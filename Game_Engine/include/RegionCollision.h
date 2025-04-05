#pragma once
#include "Region.h"
#include "SceneBase.h"

class CollisionRegion : public IRegion
{
public:

    CollisionRegion(float x, float y, float width, float height, IComposite* scene) 
        : IRegion(x, y, width, height, scene) 
    {
        m_shape.setSize(sf::Vector2f(width, height));
        m_shape.setPosition(x, y); 
        m_shape.setFillColor(sf::Color(0, 0, 0, 0));
        m_shape.setOutlineColor(sf::Color::Green);
        m_shape.setOutlineThickness(2.0f);

    }

    void update() override
    {
		std::cout << "lets goooooooo update collision" << std::endl;

		FixPosition();
    }

    void render() override
    {
        std::cout << "lets goooooooo render collision" << std::endl;

        m_scene->getRoot()->getScene()->getWindow()->draw(m_shape);

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

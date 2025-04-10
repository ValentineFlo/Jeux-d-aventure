#pragma once
#include "Region.h"

class PlateformeRegion : public IRegion, public NonDestructibleObject
{
public:

	PlateformeRegion(float x, float y, float width, float height, IComposite* scene)
        : IRegion(x, y, width, height)
        , NonDestructibleObject(scene)
    {}


    void Update(const float& deltatime) override
    {
        std::cout << "lets goooooooo update plateforme" << std::endl;
    }

    void ProcessInput(const sf::Event& event)
    {
        std::cout << "process collision" << std::endl;
    }

    void Render() override
    {

        std::cout << "lets goooooooo render plateforme" << std::endl;
    }

    AABB getBoundingBox() const override
    {
        return AABB(sf::Vector2f(m_x, m_y), sf::Vector2f(m_x + m_width, m_y + m_height));
    }

	float getX() const { return m_x; }
	float getY() const { return m_y; }

public :

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

    void HandleCollision() override
    {
        AABB boundingBox = getBoundingBox();

        //for (auto& objet : m_scene->getRoot()->getScene()->getFullTree())
        //{
        //    if (Collision(boundingBox, ))
        //    {
        //        std::cout << "Collision detected!" << std::endl;
        //    }
        //}


    }

    GameObjectType globalGameObjectType() override
    {
        return GameObjectType::NonDestructibleObject;
    }
private:
	sf::RectangleShape m_shape;

};
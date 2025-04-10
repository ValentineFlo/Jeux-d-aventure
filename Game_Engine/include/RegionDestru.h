#pragma once
#include "Region.h"

class DestructeurRegion : public IRegion, public NonDestructibleObject, public IComposite
{
public:

    DestructeurRegion(float x, float y, float width, float height, IComposite* scene)
        : IRegion(x, y, width, height)
        , NonDestructibleObject(scene)
        , IComposite(scene)
        , m_x(x)
        , m_y(y)
        , m_width(width)
        , m_height(height)
    {
        m_shape.setSize(sf::Vector2f(width, height));
        m_shape.setPosition(x, y);
        m_shape.setFillColor(sf::Color(0, 0, 0, 0));
        m_shape.setOutlineColor(sf::Color::Blue);
        m_shape.setOutlineThickness(2.0f);
    }


    void Update(const float& deltatime) override
    {
        FixPosition();
        HandleCollision();
    }

    void ProcessInput(const sf::Event& event)
    {
        std::cout << "process collision" << std::endl;
    }

    void Render() override
    {

        m_scene->getRoot()->getScene()->getWindow()->draw(m_shape);
    }

    AABB getBoundingBox() const override
    {
        return AABB(sf::Vector2f(m_x, m_y), sf::Vector2f(m_x + m_width, m_y + m_height));
    }

    float getX() const { return m_x; }
    float getY() const { return m_y; }



     void FixPosition() override
     {

         sf::Vector2f topLeft = m_scene->getRoot()->getScene()->GetCenterWindow();
         sf::Vector2f screenPos(m_x - topLeft.x, m_y - topLeft.y);

         m_shape.setPosition(screenPos);
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
    float m_x, m_y, m_width, m_height;
    sf::Vector2f getLastPosition() {}

};

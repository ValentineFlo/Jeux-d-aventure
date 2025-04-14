#pragma once
#include "Region.h"

class DestructeurRegion : public IRegion, public NonDestructibleObject, public IComposite
{
public:

    DestructeurRegion(float x, float y, float width, float height, IShapeSFML* game_object, IComposite* scene)
        : IRegion(x, y, width, height)
        , NonDestructibleObject(scene)
        , IComposite(scene)
        , m_x(x)
        , m_y(y)
        , m_width(width)
        , m_height(height)
        , m_game_object(game_object)
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

    void FixPosition() override
    {
        m_shape.setSize(sf::Vector2f(m_width, m_height));
        m_shape.setOrigin(m_width / 2.0f, m_height / 2.0f);

        if (m_game_object)
        {
            sf::Vector2f basePos = m_game_object->getPosition();
            m_shape.setPosition(basePos);
        }
    }

    AABB getBoundingBox() const override
    {
        return AABB(sf::Vector2f(m_x, m_y), sf::Vector2f(m_x + m_width, m_y + m_height));
    }

    float getX() const { return m_x; }
    float getY() const { return m_y; }


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
    IShapeSFML* m_game_object;

};

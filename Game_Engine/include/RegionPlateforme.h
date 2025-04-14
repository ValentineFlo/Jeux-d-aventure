#pragma once
#include "Region.h"

class PlateformeRegion : public IRegion, public NonDestructibleObject, public IComposite
{
public:

	PlateformeRegion(float x, float y, float width, float height, IShapeSFML* game_object, IComposite* scene)
        : IRegion(x, y, width, height)
        , NonDestructibleObject(scene)
        , IComposite(scene)
        , m_x(x)
        , m_y(y)
        , m_width(width)
        , m_height(height)
        , m_game_object(game_object)
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

public :


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
    IShapeSFML* m_game_object;

};
#pragma once
#include "Region.h"
#include "SceneBase.h"

class CollisionRegion : public IRegion, public NonDestructibleObject
{
public:

    CollisionRegion(float x, float y, float width, float height, IComposite* scene) 
        : IRegion(x, y, width, height, scene)
        , NonDestructibleObject(scene)

    {
        m_shape.setSize(sf::Vector2f(width, height));
        m_shape.setPosition(x, y); 
        m_shape.setFillColor(sf::Color(0, 0, 0, 0));
        m_shape.setOutlineColor(sf::Color::Green);
        m_shape.setOutlineThickness(2.0f);

    }

    void Update(const float& deltatime) override
    {
        std::cout << "update collision" << std::endl;
		FixPosition();
        HandleCollision();
    }

    void ProcessInput(const sf::Event& event) 
    {
        std::cout << "process collision" << std::endl;
    }

    void Render() override
    {
        std::cout << "render collision" << std::endl;
        m_scene->getRoot()->getScene()->getWindow()->draw(m_shape);
    }

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

	AABB getBoundingBox() const override
	{
		return AABB(sf::Vector2f(m_x, m_y), sf::Vector2f(m_x + m_width, m_y + m_height));

	}



    void HandleCollision() override
    {
        AABB regionBox = getBoundingBox();
        auto objets = m_scene->getFullTree();


        for (auto* objet : objets)
        {
           
           
            
        }

    }


    float getX() const { return m_x; }
    float getY() const { return m_y; }

private :
    sf::RectangleShape m_shape;
};


#pragma once
#include "Region.h"
#include "SceneBase.h"

class CollisionRegion : public IRegion, public NonDestructibleObject, public IComposite
{
public:

    CollisionRegion(float x, float y, float width, float height, IComposite* scene)
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
        m_shape.setOutlineColor(sf::Color::Green);
        m_shape.setOutlineThickness(2.0f);

    }


    void Update(const float& deltatime) override
    {
		FixPosition();
        HandleCollision();
    }

    void ProcessInput(const sf::Event& event) 
    {

    }

    void Render() override
    {
        m_scene->getRoot()->getScene()->getWindow()->draw(m_shape);
    }

     void FixPosition() override
     {
         sf::Vector2f topLeft = m_scene->getRoot()->getScene()->GetCenterWindow();
         sf::Vector2f screenPos(m_x - topLeft.x, m_y - topLeft.y );

         m_shape.setPosition(screenPos);


     }

	AABB getBoundingBox() const override
	{
		return AABB(sf::Vector2f(m_x, m_y), sf::Vector2f(m_x + m_width, m_y + m_height));

	}


    void HandleCollision() override
    {


        for (IComponent* component : m_parent->getChildren())
        {
            IGameObject* objet = dynamic_cast<IGameObject*>(component);
            if (objet == this) continue;

            if (getBoundingBox().Intersects(objet->GetBoundingBox()))
            {
                std::cout << "Collision avec : " << objet->GetBoundingBox().Amin.x << " " << objet->GetBoundingBox().Amin.y << std::endl;

 /*               objet->getShape()->setPosition(objet->getLastPosition());*/
            }
        }
    }


    float getX() const { return m_x; }
    float getY() const { return m_y; }

    GameObjectType globalGameObjectType() override
    {
        return GameObjectType::NonDestructibleObject;
    }


private :
    sf::RectangleShape m_shape;
    float m_x, m_y, m_width, m_height;

};


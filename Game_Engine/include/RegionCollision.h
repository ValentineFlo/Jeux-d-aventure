#pragma once
#include "Region.h"
#include "SceneBase.h"

class CollisionRegion : public IRegion, public NonDestructibleObject, public IComposite
{
public:

    CollisionRegion(float x, float y, float width, float height, IComposite* scene, GameObjectManager* manager)
        : IRegion(x, y, width, height, scene)
        , NonDestructibleObject(scene)
        , IComposite(scene)
<<<<<<< HEAD
        , m_object(manager)
=======
>>>>>>> 812f6f72dab72450f8958f492140c38a84aa6a57

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
<<<<<<< HEAD
        std::cout << m_object->getSize() << std::endl;

        for (IGameObject* objet : m_object->getAll())
        {
            if (objet->GetBoundingBox().Intersects(getBoundingBox()))
            {
                std::cout << "Collision!!!!!!!!!!!!!!" << std::endl;
            }

            return;
        }
=======
        /*for (IGameObject* objet :)
        {
            if (objet == this) continue;

            if (getBoundingBox().Intersects(objet->GetBoundingBox()))
            {
                std::cout << "Collision avec : " << objet << std::endl;

                objet->getShape()->setPosition(objet->getLastPosition());
            }
            
        }*/
>>>>>>> 812f6f72dab72450f8958f492140c38a84aa6a57

    }

    float getX() const { return m_x; }
    float getY() const { return m_y; }

private :
    sf::RectangleShape m_shape;
    GameObjectManager* m_object;
};


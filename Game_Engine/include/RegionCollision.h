#pragma once
#include "Region.h"
#include "SceneBase.h"
#include "Hero.h"

class CollisionRegion : public IRegion, public NonDestructibleObject, public IComposite
{
public:

    CollisionRegion(float x, float y, float width, float height, IShapeSFML* game_object, IComposite* scene)
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
        m_shape.setSize(sf::Vector2f(m_width, m_height));
        m_shape.setOrigin(m_width / 2.0f, m_height / 2.0f);

        if (m_game_object)
        {
            sf::Vector2f basePos = m_game_object->getPosition();
            m_shape.setPosition(basePos.x - m_x, basePos.y - m_y);
        }
    }


	AABB getBoundingBox() const override
	{
        sf::Vector2f pos = m_shape.getPosition();
        sf::Vector2f half = m_shape.getSize() / 2.f;
        return AABB(pos - half, pos + half);
	}


    void HandleCollision() override
    {
        AABB regionBox = getBoundingBox();

        for (IComponent* comp : m_scene->getRoot()->getFullTree())
        {
            IGameObject* obj = dynamic_cast<IGameObject*>(comp);
            if (!obj || obj == this) 
                continue;

            if (obj->globalGameObjectType() != GameObjectType::DestructibleObject)
                continue;

            AABB objetBox = obj->GetBoundingBox();

            if (regionBox.Intersects(objetBox))
            {
                std::cout << "Collision avec : " << typeid(*this).name()<< " " << typeid(*obj).name() << std::endl;

                /*Hero* hero = dynamic_cast<Hero*>(obj);
                if (hero)
                {
                    hero->getShape()->setPosition(hero->getLastPosition());
                }*/

                obj->HandleCollision(this);

                
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
    IShapeSFML* m_game_object;
};



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
        m_txtInteractionfont.loadFromFile("8514oem.fon");
        sf::Text text("hello", m_txtInteractionfont);
        text.setCharacterSize(30);
        text.setStyle(sf::Text::Bold);
        text.setFillColor(sf::Color::Blue);
        text.setPosition(x / 2, y / 2);

        m_text = text;

        m_shape.setSize(sf::Vector2f(width, height));
        m_shape.setPosition(x, y);
        m_shape.setFillColor(sf::Color(0, 0, 0, 0));
        m_shape.setOutlineThickness(2.0f);

    }

    void Update(const float& deltatime) override
    {
        FixPosition();
        HandleCollision();
    }


    void ProcessInput(const sf::Event& event)
    {
        bool press = sf::Keyboard::isKeyPressed(sf::Keyboard::E);

        if (!is_inInteraction)
            return;


        if (press && !m_pressed)
        {
            if (!m_toogle)
            {

                m_shape.setOutlineColor(sf::Color::Blue);
                m_toogle = true;
            }

            else
            {
                m_shape.setOutlineColor(sf::Color::Yellow);
                m_toogle = false;
            }

            

        }

        m_pressed = press;

    }

    void Render() override
    {
        m_scene->getRoot()->getScene()->getWindow()->draw(m_shape);
        m_scene->getRoot()->getScene()->getWindow()->draw(m_text);
    }

    void FixPosition() override
    {
        //m_shape.setSize(sf::Vector2f(m_width, m_height));
        //m_shape.setOrigin(m_width / 2.0f, m_height / 2.0f);

        //if (m_game_object)
        //{
        //    sf::Vector2f basePos = m_game_object->getPosition();
        //    m_shape.setPosition(basePos.x - m_x, basePos.y - m_y);
        //}
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
                std::cout << "Collision avec : " << typeid(*this).name() << " " << typeid(*obj).name() << std::endl;

                if (std::string(typeid(*obj).name()) == "class Hero")
                {
                    is_inInteraction = true;
                    for (IComponent* comp : m_scene->getRoot()->getFullTree())
                    {
                        IGameObject* obj = dynamic_cast<IGameObject*>(comp);
                        if (!obj || obj == this)
                            continue;

                        if (obj->globalGameObjectType() != GameObjectType::DestructibleObject)
                            continue;

                        std::cout << "Collision avec : " << typeid(*this).name() << " " << typeid(*obj).name() << std::endl;

                        
                            DestructibleObject* destru = static_cast<DestructibleObject*> (obj);
                            destru->ChangeLife(-2);
                            /*std::cout << destru->getCurrentLife() << std::endl;*/

                    }

                }
                else
                    is_inInteraction = false;

                obj->HandleCollision(this);

            }
            else
            {
                if (std::string(typeid(*obj).name()) == "class Hero")
                {
                    is_inInteraction = false;

                }
            }

        }

    }


    float getX() const { return m_x; }
    float getY() const { return m_y; }

    GameObjectType globalGameObjectType() override
    {
        return GameObjectType::NonDestructibleObject;
    }


private:
    sf::RectangleShape m_shape;
    float m_x, m_y, m_width, m_height;
    IShapeSFML* m_game_object;
    sf::Font m_txtInteractionfont;
    sf::Text m_text;
    bool is_inInteraction = false;
    bool m_toogle = false;
    bool m_pressed = false;
};


//#include "Mashroom.h"
//#include <iostream>
//
//#include "Region.h"
//#include "RegionCollision.h"
//
//Mashroom::Mashroom(float x, float y, float width, float height, IShapeSFML* background, IComposite* scene)
//    : DestructibleObject(scene, 10)
//    , IComposite(scene)
//    , m_background(background)
//    , m_counter(0)
//    , m_x(x)
//    , m_y(y)
//    , m_width(width)
//    , m_height(height)
//    , m_animate({ "potion.png" })
//
//
//{
//    m_animationComponent = new AnimationComponent(this);
//    setupAnimations();
//
//    m_animationComponent->setScale(sf::Vector2f(4.0f, 4.0f));
//}
//
//Mashroom::~Mashroom()
//{
//}
//
//void Mashroom::setupAnimations()
//{
//    const int FRAME_WIDTH = 16;
//    const int FRAME_HEIGHT = 16;
//
//    const int IDLE_FRAMES = 6;
//
//    Animation idleAnimDown("potion.png", IDLE_FRAMES, 100);
//    idleAnimDown.setFrameSize(sf::Vector2i(FRAME_WIDTH, FRAME_HEIGHT));
//    idleAnimDown.setStartPosition(sf::Vector2i(0, 0 * FRAME_HEIGHT), 1);
//
//    Animation idleAnimUp("potion.png", IDLE_FRAMES, 100);
//    idleAnimUp.setFrameSize(sf::Vector2i(FRAME_WIDTH, FRAME_HEIGHT));
//    idleAnimUp.setStartPosition(sf::Vector2i(0, 3 * FRAME_HEIGHT), 1);
//
//    Animation idleAnimLeft("potion.png", IDLE_FRAMES, 100);
//    idleAnimLeft.setFrameSize(sf::Vector2i(FRAME_WIDTH, FRAME_HEIGHT));
//    idleAnimLeft.setStartPosition(sf::Vector2i(0, 6 * FRAME_HEIGHT), 1);
//
//    Animation idleAnimRight("potion.png", IDLE_FRAMES, 100);
//    idleAnimRight.setFrameSize(sf::Vector2i(FRAME_WIDTH, FRAME_HEIGHT));
//    idleAnimRight.setStartPosition(sf::Vector2i(0, 9 * FRAME_HEIGHT), 1);
//
//    m_animationComponent->addAnimation("idle_down", idleAnimDown);
//    m_animationComponent->addAnimation("idle_up", idleAnimUp);
//    m_animationComponent->addAnimation("idle_left", idleAnimLeft);
//    m_animationComponent->addAnimation("idle_right", idleAnimRight);
//
//
//    m_animationComponent->getSprite().setScale(4.0f, 4.0f);
//}
//
//
//void Mashroom::ProcessInput(const sf::Event& event)
//{
//
//}
//
////AABB Mashroom::getBoundingBox() const
////{
////    return AABB(sf::Vector2f(m_x, m_y), sf::Vector2f(m_x + m_width, m_y + m_height));
////}
//
//
//void Mashroom::Update(const float& deltatime)
//{
//    for (IComponent* comp : m_scene->getRoot()->getFullTree())
//    {
//        IGameObject* obj = dynamic_cast<IGameObject*>(comp);
//        if (!obj || obj == this)
//            continue;
//
//        if (obj->globalGameObjectType() != GameObjectType::DestructibleObject)
//            continue;
//
//        std::cout << "Collision avec : " << typeid(*this).name() << " " << typeid(*obj).name() << std::endl;
//
//        if (std::string(typeid(*obj).name()) == "class Hero")
//        {
//
//            Hero* hero = static_cast<Hero*> (obj);
//           /* if (hero->GetBoundingBox().Intersects(getBoundingBox()))
//            {
//
//            }*/
//
//        }
//
//    }
//    
//
//
//
//}
//
//void Mashroom::Render()
//{/*
//    m_scene->getRoot()->getScene()->getWindow()->draw(m_shape);*/
//    IComposite::Render();
//}
//

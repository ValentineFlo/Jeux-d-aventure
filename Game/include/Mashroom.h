//#pragma once
//#include "IGameObject.h"
//#include "Animation.h"
//#include "IShape.h"
//#include "RegionManager.h"
//
//class Mashroom : public DestructibleObject, public IComposite
//{
//
//public:
//    Mashroom(float x, float y, float width, float height, IShapeSFML* background, IComposite* scene);
//    ~Mashroom() override;
//   
//    void ProcessInput(const sf::Event& event) override;
//    void Update(const float& deltatime) override;
//    void Render() override;
//    void setupAnimations();
//    /*
//    AABB getBoundingBox() const override;*/
//
//private:
//    IShapeSFML* m_background;
//    RegionManager m_regionManager;
//    float m_x, m_y, m_width, m_height;
//    AnimateSprite m_animate;
//    AnimationComponent* m_animationComponent;
//    int m_counter;
//};
//#pragma once
//#include "IGameObject.h"
//#include "Animation.h"
//
//class Mashroom : public DestructibleObject, public IComposite
//{
//
//public:
//    Mashroom(IComposite* scene, IShapeSFML* background);
//    ~Mashroom() override;
//
//    void ProcessInput(const sf::Event& event) override;
//    void Update(const float& deltatime) override;
//    void Render() override;
//
//private:
//    IShapeSFML* m_background;
//    sf::RectangleShape m_shape;
//
//    int m_counter;
//};
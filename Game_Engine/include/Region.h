#include <iostream>
#include <memory>


enum RegionType
{
    COLLISIONABLE
    , DESTRUCTEUR
    , RESUCITEUR
    , PLATEFORME
    , TELEPORTATION
};

class IRegion
{
public:
    IRegion(float x, float y) : m_x(x), m_y(y) {}

    virtual ~IRegion() = default;
    virtual void exe() = 0;
    virtual void update() = 0;
    virtual void render() = 0;

    float getX() const { return m_x; }
    float getY() const { return m_y; }

protected:
    float m_x, m_y;

};
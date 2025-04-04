#pragma once
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
    IRegion(float x, float y, float width, float height) 
        : m_x(x)
        , m_y(y)
		, m_width(width)
		, m_height(height)
    {}

    virtual ~IRegion() = default;
    virtual void update() = 0;
    virtual void render() = 0;
	virtual bool isInside(float x, float y) const
	{
		return (x >= m_x && x <= m_x + m_width && y >= m_y && y <= m_y + m_height);
	}

    float getX() const { return m_x; }
    float getY() const { return m_y; }

protected:
    float m_x, m_y;
    float m_width, m_height;

};



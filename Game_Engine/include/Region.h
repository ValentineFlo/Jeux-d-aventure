#pragma once
#include <iostream>
#include <memory>
#include "IGameObject.h"

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
    IRegion(float x, float y, float width, float height, IComposite* scene)
        : m_x(x)
        , m_y(y)
		, m_width(width)
		, m_height(height)
    {
        
    }

    virtual ~IRegion() = default;
	virtual void FixPosition() = 0;
    virtual AABB getBoundingBox() const = 0; 
    virtual void HandleCollision() = 0;

    float getX() const { return m_x; }
    float getY() const { return m_y; }
	float getWidth() const { return m_width; }
	float getHeight() const { return m_height; }

	void setX(float x) { m_x = x; }
	void setY(float y) { m_y = y; }
	void setWidth(float width) { m_width = width; }
	void setHeight(float height) { m_height = height; }

protected:
    float m_x, m_y;
    float m_width, m_height;

};



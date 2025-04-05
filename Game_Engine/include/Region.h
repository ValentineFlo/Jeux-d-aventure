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
        , m_scene(scene)
    {
        
    }

    virtual ~IRegion() = default;
    virtual void update() = 0;
    virtual void render() = 0;
	virtual void FixPosition() = 0;

    float getX() const { return m_x; }
    float getY() const { return m_y; }
    
protected:
    float m_x, m_y;
    float m_width, m_height;
    IComposite* m_scene;

};



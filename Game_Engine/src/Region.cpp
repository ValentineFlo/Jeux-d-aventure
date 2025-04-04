#include "Region.h"


Region::Region(RegionType type, float x, float y)
    : m_x(x)
    , m_y(y)
{
    switch (type)
    {
    case COLLISIONABLE:
        m_typeptr = std::unique_ptr<IRegion>(new CollisionRegion());
        break;
    case DESTRUCTEUR:
        m_typeptr = std::unique_ptr<IRegion>(new DestructeurRegion());
        break;
    case RESUCITEUR:
        m_typeptr = std::unique_ptr<IRegion>(new ResuciteurRegion());
        break;
    case PLATEFORME:
        m_typeptr = std::unique_ptr<IRegion>(new PlateformeRegion());
        break;
    case TELEPORTATION:
        m_typeptr = std::unique_ptr<IRegion>(new TeleportationRegion());
        break;
    default:
        throw std::invalid_argument("Type de region invalide.");
    }
}

void Region::exe()
{
    m_typeptr->exe();
}

void Region::update()
{
    m_typeptr->update();
}

void Region::render()
{
    m_typeptr->render();
}

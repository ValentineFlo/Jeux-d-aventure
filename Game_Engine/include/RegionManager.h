#pragma once
#include <vector>
#include <memory>
#include "Region.h"
#include "RegionCollision.h"
#include "RegionDestru.h"
#include "RegionPlateforme.h"
#include "RegionResuciteur.h"
#include "RegionTeleportation.h"

class RegionManager

{
public:
    static std::unique_ptr<IRegion> createRegion(RegionType type, float x, float y, float width, float height)
    {
        switch (type) 
        {
        case COLLISIONABLE:
            return std::make_unique<CollisionRegion>(x, y, width, height);
        case DESTRUCTEUR:
            return std::make_unique<DestructeurRegion>(x, y, width, height);
        case PLATEFORME:
            return std::make_unique<PlateformeRegion>(x, y, width, height);
        case RESUCITEUR:
            return std::make_unique<ResuciteurRegion>(x, y, width, height);
        case TELEPORTATION:
            return std::make_unique<TeleportationRegion>(x, y, width, height);
        default:
            throw std::runtime_error("Type de region inconnu");
        }
    }

    void addRegion(RegionType type, float x, float y, float width, float height)
    {
        m_regions.push_back(RegionManager::createRegion(type, x, y, width, height));
    }
    

    void updateAll()
    {
        for (auto& region : m_regions)
        {
            region->update();
        }
    }

    void renderAll()
    {
        for (auto& region : m_regions)
        {
            region->render();
        }
    }

private:
    std::vector<std::unique_ptr<IRegion>> m_regions;
};

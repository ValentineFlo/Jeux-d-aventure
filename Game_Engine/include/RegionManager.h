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
    static std::unique_ptr<IRegion> createRegion(RegionType type, float x, float y, float width, float height, IComposite* scene)
    {
        switch (type) 
        {
        case COLLISIONABLE:
            return std::unique_ptr <CollisionRegion>(new CollisionRegion(x, y, width, height, scene));
        case DESTRUCTEUR:
            return std::unique_ptr <DestructeurRegion>(new DestructeurRegion(x, y, width, height, scene));
        case PLATEFORME:
            return std::unique_ptr <PlateformeRegion>(new PlateformeRegion(x, y, width, height, scene));
        case RESUCITEUR:
			return std::unique_ptr <ResuciteurRegion>(new ResuciteurRegion(x, y, width, height, scene));
        case TELEPORTATION:
            return std::unique_ptr <TeleportationRegion>(new TeleportationRegion(x, y, width, height, scene));
        default:
            throw std::runtime_error("Type de region inconnu");
        }
    }

    void addRegion(RegionType type, float x, float y, float width, float height, IComposite* scene)
    {
        m_regions.push_back(RegionManager::createRegion(type, x, y, width, height, scene));
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

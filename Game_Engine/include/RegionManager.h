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

    static std::unique_ptr<IRegion> createRegion(RegionType type, float x, float y, float width, float height, IShapeSFML* game_object, IComposite* scene)
    {
        switch (type) 
        {
        case COLLISIONABLE:
            return std::unique_ptr <CollisionRegion>(new CollisionRegion(x, y, width, height, game_object, scene));
        case DESTRUCTEUR:
            return std::unique_ptr <DestructeurRegion>(new DestructeurRegion(x, y, width, height, game_object, scene));
        case PLATEFORME:
            return std::unique_ptr <PlateformeRegion>(new PlateformeRegion(x, y, width, height, game_object, scene));
        case RESUCITEUR:
			return std::unique_ptr <ResuciteurRegion>(new ResuciteurRegion(x, y, width, height, game_object, scene));
        case TELEPORTATION:
            return std::unique_ptr <TeleportationRegion>(new TeleportationRegion(x, y, width, height, game_object, scene));
        default:
            throw std::runtime_error("Type de region inconnu");
        }
    }
       
    void addRegion(RegionType type, float x, float y, float width, float height, IShapeSFML* game_object, IComposite* scene)
    {
        m_regions.push_back(RegionManager::createRegion(type, x, y, width, height, game_object, scene));
    }


private:
    std::vector<std::unique_ptr<IRegion>> m_regions;
};

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

class IRegion /*: IGameObject*/
{
public:
    virtual ~IRegion() = default;
    virtual void exe() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
};



class CollisionRegion : public IRegion
{
public:

    void exe() override
    {
        std::cout << "lets goooooooo exe collision" << std::endl;
    }

    void update() override
    {
        std::cout << "lets goooooooo update collision" << std::endl;
    }

    void render() override
    {

        std::cout << "lets goooooooo render collision" << std::endl;
    }

};

class DestructeurRegion : public IRegion
{
public:

    void exe() override
    {
        std::cout << "lets goooooooo exe destru" << std::endl;
    }

    void update() override
    {
        std::cout << "lets goooooooo update destru" << std::endl;
    }

    void render() override
    {

        std::cout << "lets goooooooo render destru" << std::endl;
    }

};

class ResuciteurRegion : public IRegion
{
public:
    void exe() override
    {
        std::cout << "lets goooooooo exe resuciteur" << std::endl;
    }

    void update() override
    {
        std::cout << "lets goooooooo update resuciteur" << std::endl;
    }

    void render() override
    {

        std::cout << "lets goooooooo render resuciteur" << std::endl;
    }
};

class PlateformeRegion : public IRegion
{
public:
    void exe() override
    {
        std::cout << "lets goooooooo exe plateforme" << std::endl;
    }

    void update() override
    {
        std::cout << "lets goooooooo update plateforme" << std::endl;
    }

    void render() override
    {

        std::cout << "lets goooooooo render plateforme" << std::endl;
    }
};


class TeleportationRegion : public IRegion
{
public:
    void exe() override
    {
        std::cout << "lets goooooooo exe teleportation" << std::endl;
    }

    void update() override
    {
        std::cout << "lets goooooooo update teleportation" << std::endl;
    }

    void render() override
    {

        std::cout << "lets goooooooo render teleportation" << std::endl;
    }
};

class Region : public IRegion
{
public:
    Region(RegionType type, float x, float y)
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

    void exe() override
    {
        m_typeptr->exe();
    }

    void update() override
    {
        m_typeptr->update();
    }

    void render() override
    {
        m_typeptr->render();
    }

private:
    float m_x, m_y;

protected:
    std::unique_ptr<IRegion> m_typeptr;
};
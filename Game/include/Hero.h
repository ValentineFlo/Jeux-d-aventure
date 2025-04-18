#pragma once
#include "IGameObject.h"
#include "MegaBoss.h"
#include "Animation.h"

class Hero : public DestructibleObject, public IComposite
{
protected:
    enum State
    {
        IDLE,
        MOVE,
        JUMP,
        FALL,
        HAND_ATTACK,
        PISTOL_ATTACK,
        RELOAD
    };

    struct IState
    {
        virtual ~IState() = default;
        virtual IState* handle(const State& state) = 0;
        virtual void update(Hero* ship, float deltaTime) = 0;
    };

    struct IdleState : IState
    {
        ~IdleState() override = default;
        IState* handle(const State& state) override;
        void update(Hero* ship, float deltaTime) override;
    };

    struct MoveState : IState
    {
        ~MoveState() override = default;
        IState* handle(const State& state) override;
        void update(Hero* ship, float deltaTime) override;
    };

    struct JumpState : IState
    {
        ~JumpState() override = default;
        IState* handle(const State& state) override;
        void update(Hero* ship, float deltaTime) override;
    };

    struct FallState : IState
    {
        ~FallState() override = default;
        IState* handle(const State& state) override;
        void update(Hero* ship, float deltaTime) override;
    };

    struct HandAttackState : IState
    {
        ~HandAttackState() override = default;
        IState* handle(const State& state) override;
        void update(Hero* ship, float deltaTime) override;

        float attackDuration = 0.3f;
        float attackTimer = 0.0f;

        RectangleSFML* meleeHitbox = nullptr;
        bool damageDealt = false;
    };

    struct PistolAttackState : IState
    {
        ~PistolAttackState() override = default;
        IState* handle(const State& state) override;
        void update(Hero* ship, float deltaTime) override;
    };

    struct ReloadState : IState
    {
        ~ReloadState() override = default;
        IState* handle(const State& state) override;
        void update(Hero* ship, float deltaTime) override;

    private:
        float reloadTime = 100.0f;
        float reloadTimer = 0.0f;
    };

    IState* m_currentState;

public:
    friend BorderShip;
    Hero(IComposite* scene, sf::Vector2f BasePosition);
    ~Hero() override;

    void ProcessInput(const sf::Event& event) override;
    void physics();
    void Update(const float& deltatime) override;
    void Render() override;

    float anglecalcul();
    void HandleCollision(IGameObject* object) override;
    void ChangeLife(const float& life) override;
    void ChangeLifewithoutinvincibility(const float& life);

    void ChangeState(const State& newState);
    float distanceToBoss(MegaBoss* boss);

    void createMeleeHitbox(float angle, float offsetDistance);
    void checkMeleeCollisions(RectangleSFML* attackHitbox);

    bool IsDestroyed();

    

    std::string getOrientationString() const;

    sf::Vector2f getLastPosition()
    {
        return m_lastPosition;
    }

    IPhysics* m_physics;

private:
    //IShapeSFML* m_background;
    IShapeSFML* m_target;

    sf::View m_view;

    float m_angle;
    Timer m_elapsedTime;
    Timer m_invisibility;
    Timer m_meleeAttackTimer;

    AnimateSprite m_animate;
    AnimationComponent* m_animationComponent;
    
    
    ITurret* m_turret;
    KT::VectorND<bool, 4> m_strafe{ false,false,false,false };

    std::vector<MegaBoss*> m_enemiesInGame;
    float m_detectionRadius;

    float m_meleeDamage;
    float m_meleeAttackCooldown;

    void setupAnimations();
    Orientation determineOrientation(float angle);
    Orientation m_currentOrientation;

    const sf::Vector2f& m_lastPosition;


    float PlateformeXmin=0.f;
    float PlateformeXmax=0.f;
    float PlateformeY = 0.f;
};
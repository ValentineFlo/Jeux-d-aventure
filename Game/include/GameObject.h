#pragma once
#include "IGameObject.h"
#include "VectorND.h"
#include "SceneBase.h"
#include "IShape.h"
#include <array>

class Hero;
enum trust
{
	Right = 0
	, Left = 1
	, Up = 2
	, Down = 3
	, Default = 4
};

class Cursor : public NonDestructibleObject, public ILeaf
{
public:
	Cursor(IComposite* scene);
	void ProcessInput(const sf::Event& event) override;

	void Update(const float& deltatime);

	void Render() override;

private:
	AnimateSprite m_animate;
};

class Physics : public IPhysics
{
public:
	Physics(const float& maxVelocity, const float& thrust, const float& frictionCoef);
	void ExecutePhysics(KT::VectorND<bool, 4>& isStrafing, float framerate);

	sf::Vector2f calculPosition(IShapeSFML* entity, ISceneBase* scene, float framerate);
	float getMaxVelocity() { return m_maxVelocity; }
	float getFrictionCoef() { return m_frictionCoef; }
	float getThrust() { return m_thrust; }
	bool on_ground=false;
	sf::Vector2f m_velocity;
private:
	float m_maxVelocity;
	float m_frictionCoef;
	float m_thrust;
	
	//std::array<float, 4> movementDirection;
};


class IBorder : public NonDestructibleObject, public ILeaf
{
public:

	IBorder(IComposite* scene, sf::Vector2f BasePosition, sf::Vector2f Size);
	void ProcessInput(const sf::Event& event) override = 0;
	void Update(const float& deltatime);
	void Render() override = 0;

protected:
	sf::Vector2f m_position;
	sf::Vector2f m_size;
};

class BorderShip : public IBorder
{
public:
	BorderShip::BorderShip(IComposite* scene, sf::Vector2f BasePosition, sf::Vector2f Size, Hero* ship);
	void ProcessInput(const sf::Event& event) override {}
	void Update(const float& deltatime);
	void Render() override;

private:
	sf::Vector2f VerifyLimit();
	Hero* m_ship;
	AnimateSprite m_sprite;
	Timer m_elapsedTime;
	bool IsInBorder;
};

enum class Position
{
	Left
	, Right
	, Up
	, Down
};

class ExternBorder : public IBorder
{
public:
	ExternBorder(IComposite* scene, sf::Vector2f BasePosition, sf::Vector2f Size, Position pos, sf::Vector2f WorldSize);
	void ProcessInput(const sf::Event& event) override {}
	void Update(const float& deltatime);
	void Render() override;
protected:
	sf::Vector2f m_diffposition;
	sf::Vector2f m_worldSize;
};

class WorldBorder : public ExternBorder
{
public:
	WorldBorder(IComposite* scene, sf::Vector2f BasePosition, sf::Vector2f Size, Position pos, sf::Vector2f WorldSize, float Securitydistance);
	void HandleCollision(IGameObject* object) override;
};

class GameBorder : public ExternBorder
{
public:
	GameBorder(IComposite* scene, sf::Vector2f BasePosition, sf::Vector2f Size, Position pos, sf::Vector2f WorldSize);
	void HandleCollision(IGameObject* object) override;
};

class ITurret : public NonDestructibleObject, public IComposite
{
public:
	ITurret(IComposite* scene, IShapeSFML* game_object, sf::Vector2f& positiondiff);
	virtual ~ITurret() = default;
	void ProcessInput(const sf::Event& event) override = 0;
	void setBullet(float Size, float Speed, float hp);
	void Update(const float& deltatime);
	void Render() override = 0;
	virtual void Fire() = 0;
	void SetFireRate(const float& fireRate);
	void SetOverloadGun(const float& overloadcoodown, float MaxShot);
	IShapeSFML* getGameObject() const { return m_gameObject; }

	sf::Vector2f m_positionDiff;
	float angle = 0.f;
protected:
	
	IShapeSFML* m_gameObject;
	Timer m_fireRate;
	Timer m_coolDown;
	Counter m_masShot;

	float m_bulletSpeed;
	float m_bulletLife;
	float m_bulletSize;
};

class PlayerSprite : public AnimateSprite
{
public:
	PlayerSprite();
};

class FixTurret : public  ITurret
{
public:
	FixTurret(IComposite* scene, IShapeSFML* game_object, sf::Vector2f& positiondiff, float angle);
	void ProcessInput(const sf::Event& event) override {}
	void Update(const float& deltatime);
	void Render() override;
	void Fire() override;
	
private:
	float m_angleDiff;
	SquareSFML BaseShape;
};

class AutoTurret : public ITurret
{
public:
	AutoTurret(IComposite* scene, IShapeSFML* game_object, IShapeSFML* Target, sf::Vector2f& positiondiff);
	void ProcessInput(const sf::Event& event) override {}
	void Update(const float& deltatime);
	void Render() override;
	void Fire() override;
private:
	SquareSFML BaseShape;
	IShapeSFML* m_Target;

};

class IBullet : public DestructibleObject, public ILeaf
{
public:
	IBullet(AnimateSprite animate, IComposite* scene, ITurret* gun, float angle, float speed, float size, float hp);
	void Render() override = 0;
	void ProcessInput(const sf::Event& event) = 0;
	void Update(const float& deltatime);

	ITurret* getTurret() const { return m_gun; }

protected:
	ITurret* m_gun;
	sf::Vector2f m_gunPosition;
	float m_gunangle;
	float m_speed;
	float m_size;
	AnimateSprite m_animate;
};

class ClassicBullet : public IBullet
{
public:
	ClassicBullet(AnimateSprite animate, IComposite* scene, ITurret* gun, float angle, float speed, float size, float hp);
	void Render() override;
	void ProcessInput(const sf::Event& event) {};
	void Update(const float& deltatime);
	void HandleCollision(IGameObject* object) override;

private:
	Timer m_elapsedTime;
};

enum class Color
{
	Blue
	, Pink
	, Orange
};

class Life : public NonDestructibleObject, public ILeaf
{
public:
	Life(IComposite* scene, DestructibleObject* game_object, Color color);
	~Life();
private:
	void Render() override;
	void ProcessInput(const sf::Event& event) {};
	void Update(const float& deltatime);
protected:
	DestructibleObject* m_object;
	IShapeSFML* m_backgroundShape;
	AnimateSprite m_animate;
	AnimateSprite m_animateBackground;
	float m_sizeDiff;
};



class DecorativeGameObject : public NonDestructibleObject, public ILeaf
{
public:
	DecorativeGameObject(IComposite* scene, const sf::Vector2f& position, float size);
	DecorativeGameObject(IComposite* scene, const sf::Vector2f& position, const sf::Vector2f& size);

	void ProcessInput(const sf::Event& event) override {}
	void Update(const float& deltatime) override;
	void Render() override;

	void setPosition(const sf::Vector2f& position);
	sf::Vector2f getPosition() const;

	void setAnimationTextures(const std::vector<std::string>& texturePaths);
	void setAnimationSpeed(float animationSpeed);
	void stopAnimation();
	void resumeAnimation();

private:
	AnimateSprite m_animate;
	Timer m_animationTimer;
	float m_animationSpeed;
	bool m_isAnimating;
};
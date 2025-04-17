#include "Game.h"
#include "Hero.h"
#include "IGameObject.h"
#include <iostream>

Game::Game(sf::RenderWindow* window, const float& framerate, TextureCache* texture) :
	ISceneBase(window, framerate, texture),
	//cursor(this),
	m_bossSpawnTimer(10.0f)

{
	m_Background = new SquareSFML(10000, sf::Vector2f(0, 0));
	m_Background->setTexture(m_texture->getTexture("marsmid.png"));
	m_hero = new Hero(this, {0.f,0.f});
	
	//m_regionManager.addRegion(COLLISIONABLE, 850.0f, 500.0f, 900.0f, 50.0f,  this);
	//m_regionManager.addRegion(DESTRUCTEUR, 10.0f, 130.0f, 900.0f, 900.0f,  this);
	m_regionManager.addRegion(COLLISIONABLE, -60.f, 760.0f, 500.0f, 25.f,  this);
	m_regionManager.addRegion(COLLISIONABLE, -60.f, 960.0f, 2000.0f, 25.0f,  this);
	m_regionManager.addRegion(COLLISIONABLE, 2100.0f, 960.0f, 2000.0f, 25.0f,  this);
	m_regionManager.addRegion(COLLISIONABLE, 40.f, 2000.0f, 500.0f, 25.0f,  this);

	new BorderShip(m_hero, { 0.f,0.f }, { 10000.f,0.f }, static_cast<Hero*>(m_hero));
	new GameBorder(this, { 0.f,0.f }, { 5.f,5.f }, Position::Down, { 10000.f,10000.f });
	new GameBorder(this, { 0.f,0.f }, { 5.f,5.f }, Position::Up, { 10000.f,10000.f });
	new GameBorder(this, { 0.f,0.f }, { 5.f,5.f }, Position::Left, { 10000.f,10000.f });
	new GameBorder(this, { 0.f,0.f }, { 5.f,5.f }, Position::Right, { 10000.f,10000.f });
	new WorldBorder(this, { 0.f,0.f }, { 5.f,5.f }, Position::Down, { 10000.f,10000.f }, 1000);
	new WorldBorder(this, { 0.f,0.f }, { 5.f,5.f }, Position::Up, { 10000.f,10000.f }, 1000);
	new WorldBorder(this, { 0.f,0.f }, { 5.f,5.f }, Position::Left, { 10000.f,10000.f }, 1000);
	new WorldBorder(this, { 0.f,0.f }, { 5.f,5.f }, Position::Right, { 10000.f,10000.f }, 1000);
	//m_spawner = new AsteroidSpawner(this, 10);
	//m_bossSpawner = new BossSpawner(this, 1);
	//sf::Vector2f bossSpawnPosition(GetCenterWindow().x, GetCenterWindow().y - 300);
	//m_bossSpawner->SetSpawnPosition(bossSpawnPosition);

	getWindow()->setMouseCursorVisible(false);
}

void Game::Update(const float& deltatime)
{
	
	for (auto& obj : getChildren())
	{
		obj->Update(deltatime);
	}

	//cursor.Update(deltatime);
	//m_spawner->Spawn();

	//m_bossSpawnTimer.NextTIck(deltatime);
	//if (m_bossSpawnTimer.ActionIsReady())
	//{
	//	m_bossSpawner->Spawn();
	//	m_bossSpawnTimer.setNewTimer(9999999999999999.0f);
	//}
	auto vec = getFullTree();
	collision.HandleCollision(vec);
	


}

void Game::ProcessInput(const sf::Event& event)
{
	for (auto& obj : getChildren())
	{
		obj->ProcessInput(event);
	}
	//cursor.ProcessInput(event);

}

void Game::Render()
{
	getWindow()->draw(static_cast<SquareSFML*>(m_Background)->getShape());
	for (auto& obj : getChildren())
	{
		obj->Render();
	}
	//cursor.Render();
}
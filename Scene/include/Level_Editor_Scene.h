#pragma once
#include "SceneBase.h"
#include "TextureAtlas.h"

class Level_Editor_Scene : public ISceneBase
{
public:
	Level_Editor_Scene(sf::RenderWindow* window, const float& framerate, TextureCache* texture)
		:ISceneBase(window, framerate, texture)
		,m_window(window)
	{
		m_tilemap = new TileMap(texture);
		m_tilemap->CreateEmpty(window->getSize().x, window->getSize().y);
	}
	virtual ~Level_Editor_Scene()
	{
		delete m_tilemap;
		m_tilemap = nullptr;
	}

	void ProcessInput(const sf::Event& event) override
	{
		
		if (event.type == sf::Event::MouseButtonPressed)
		{
			auto posMouseinGrid = m_tilemap->ConvertPixeltoCase({ event.mouseButton.x ,event.mouseButton.y });
			switch (event.mouseButton.button)
			{
			case sf::Mouse::Left:
				m_tilemap->setTile(posMouseinGrid, 'r');
				break;

			case sf::Mouse::Right:
				if(m_tilemap->hasTile(posMouseinGrid)==true)
					m_tilemap->removeTile(posMouseinGrid);
				break;
			default:
				break;
			}
		}
		if (event.type == sf::Event::KeyPressed)
		{
			std::string filename;
			switch (event.key.code)
			{
			case sf::Keyboard::Enter:
				
				std::cout << "Please enter the file name without the file type abbreviation(.txt) :" << "\n";
				std::cin >> filename;
				if(filename.find('.') != std::string::npos)
					throw std::runtime_error("You have entered the file type or put a dot in the file name");

				LevelFactory::SaveLevel(*(m_tilemap), filename + ".txt");
				
				break;
			case sf::Keyboard::L:
				LevelFactory::LoadLevel(*(m_tilemap), "level1.txt");
				break;
			default:
				break;
			}
		}
	}

	 void Update(const float& deltatime) override
	 {

	 }

	 void Render() override
	 { 
		 m_tilemap->Render(*(m_window));
	 }

private:
	sf::RenderWindow* m_window;
	TileMap* m_tilemap;
	
};
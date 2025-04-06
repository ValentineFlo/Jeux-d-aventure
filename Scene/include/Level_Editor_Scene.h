#pragma once
#include "SceneBase.h"

class Level_Editor_Scene : public ISceneBase
{
public:
	Level_Editor_Scene(sf::RenderWindow* window, const float& framerate, TextureCache* texture);
	virtual ~Level_Editor_Scene()=default;

	 void Update(const float& deltatime) override;

	 void ProcessInput(const sf::Event& event) override;

	 void Render() override;

private:
};
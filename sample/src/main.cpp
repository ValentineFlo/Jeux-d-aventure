//#include "SceneManager.h"
//#include "SFML/Graphics.hpp"
//#include "Game.h"
//#include "MenuScenes.h"
//#include <GameObject.h>
//
////TODO
//int main(int argc, char** argv)
//{
//    SceneManager a(argv[0], 1920, 1080, "CyberpunkShooter"/*,sf::Style::Fullscreen*/);
//    a.AddScene(new MainMenuScene(a.getWindow(), 240.0f, a.geTextureCash(), &a));
//    a.AddScene(new Game(a.getWindow(), 240.0f, a.geTextureCash(), &a));
//    a.AddScene(new PauseMenuScene(a.getWindow(), 240.0f, a.geTextureCash(), &a));
//    a.AddScene(new GameOverScene(a.getWindow(), 240.0f, a.geTextureCash(), &a));
//    a.Exe();
//
//}

#include "SceneManager.h"
#include "SFML/Graphics.hpp"
#include "Game.h"
#include <GameObject.h>
#include "RegionManager.h"

//TODO
int main(int argc, char** argv) 
{
    //SceneManager a(argv[0], 1920, 1080, "CyberpunkShooter"/*,sf::Style::Fullscreen*/);
    //a.AddScene(new Game(a.getWindow(), 240, a.getTextureCache()));
    //a.Exe();

    RegionManager region; 
    region.createRegion(COLLISIONABLE, 0.0f, 0.0f, 2.0f, 2.0f);

    region.updateAll();
    region.renderAll();
    return 0;
}
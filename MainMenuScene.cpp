#include "MainMenuScene.h"

using namespace cocos2d;

// Initialization.
bool MainMenuScene::init()
{
	bool bRect = false;
	do 
	{
		CC_BREAK_IF(!CCScene::init());

		// Initialize mainMenuLayer.
		mainMenuLayer = MainMenuLayer::create();

		// Add it to the scene.
		this->addChild(mainMenuLayer);

		bRect = true;
	} while (0);
	return bRect;
}

#ifndef __MAINMENUSCENE_H__
#define __MAINMENUSCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include "data.h"
#include "MainMenuLayer.h"

class MainMenuScene : public cocos2d::CCScene
{
public:
	MainMenuScene(){}

	// Initialization.
	bool init();

	CREATE_FUNC(MainMenuScene);
private:
	cocos2d::CCLayer *mainMenuLayer;
};

#endif
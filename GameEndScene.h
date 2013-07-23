#ifndef __GAMEENDSCENE_H__
#define __GAMEENDSCENE_H__

#include "GameScene.h"

class GameEndScene : public cocos2d::CCScene
{
public:
	// Initialization.
	bool init();

	// Display the win result.
	cocos2d::CCScene* displayWinResult();

	// Display the fail result.
	cocos2d::CCScene* displayFailResult();

	void unLockNextLevel();

	CREATE_FUNC(GameEndScene);
};

#endif
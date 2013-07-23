#pragma once
#include "cocos2d.h"
#include "GameLayer.h"
#include "GameControlLayer.h"

class GameScene : public cocos2d::CCScene
{
public:
	GameScene(void);
	~GameScene(void);

	virtual bool init();
	void update( float dt );

	CREATE_FUNC(GameScene);
private:
	GameLayer *_gameLayer;
	GameControlLayer *_gamecontrollayer;
};

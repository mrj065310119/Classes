#include "GameScene.h"
using namespace cocos2d;

GameScene::GameScene(void)
{
	_gameLayer = NULL;
	_gamecontrollayer = NULL;
}

GameScene::~GameScene(void)
{
}

bool GameScene::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCScene::init());

		_gameLayer = GameLayer::create();
		CC_BREAK_IF(!_gameLayer);
		this->addChild(_gameLayer, 1);

		_gamecontrollayer = GameControlLayer::create();
		CC_BREAK_IF(!_gamecontrollayer);
		this->addChild(_gamecontrollayer,2);

/*		this->scheduleUpdate();*/
		bRet = true;
	} while (0);

	return bRet;
}

void GameScene::update( float dt )
{
	
}


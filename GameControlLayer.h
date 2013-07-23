#ifndef __GAME_CONTROL_LAYER_H__
#define __GAME_CONTROL_LAYER_H__

#include "cocos2d.h"

#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"

#include "data.h"

class GameControlLayer : public cocos2d::CCLayer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// a selector callback
	void menuReplayCallback(CCObject* pSender);

	void menuPauseAndContinueCallback(CCObject* pSender);

	void menuGaBackMenuCallback(CCObject* pSender);
	// implement the "static node()" method manually
	CREATE_FUNC(GameControlLayer);

private:
	cocos2d::CCSize winSize;
	bool isPause;

};

#endif  
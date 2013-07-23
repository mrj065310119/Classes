#ifndef __GAMEENDLAYER_H__
#define __GAMEENDLAYER_H__

#include "cocos2d.h"

using namespace cocos2d;

class GameEndLayer : public CCLayer
{
public:
	// Initialization.
	bool init();

	// Generate a layer show the win information.
	CCLayer* generateWinLayer();

	// Generate a layer show the fail information.
	CCLayer* generateFailLayer();

	// Generate the background.
	CCSprite* generateBackground(const char* fileName);

	// Add button menu to the layer.
	void addWinMenu();
	void addFailMenu();

	// Response to replay item.
	void onReplay(CCObject* pSender);

	// Response to next item.
	void onNext(CCObject* pSender);

	// Response to levels item.
	void onLevels(CCObject* pSender);

	// Generate animation of win scene.
	void generateWinAnimation();

	CREATE_FUNC(GameEndLayer);
private:
	CCSpriteFrameCache* pigCache;
};

#endif
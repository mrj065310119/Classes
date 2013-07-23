#include "SelectLevelScene.h"
#include "SelectLevelLayer.h"
// #include "GameScene.h"
// #include <math.h>

using namespace cocos2d;

// Initialize the resource.
bool SelectLevelScene::init()
{
	bool bRect = false;
	do 
	{
		CC_BREAK_IF(!CCScene::init());
		
		backgroundLayer = CCLayer::create();
		this->addChild(backgroundLayer);
		addBackground();

		// Add level layer.
		levelLayer = SelectLevelLayer::create();
		this->addChild(levelLayer);

		bRect = true;
	} while (0);
	return bRect;
}

// Add background.
void SelectLevelScene::addBackground()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	// Create background.
	CCSprite* background = CCSprite::create(selectLevelSceneBg);
	background->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	CCSize bgSize = background->getContentSize();

	// Calculate the scale values between window size and background size.
	float scaleX = winSize.width / bgSize.width;
	float scaleY = winSize.height / bgSize.height;

	// Scale the background and add it to the layer.
	background->setScaleX(scaleX);
	background->setScaleY(scaleY);
	backgroundLayer->addChild(background, 0);
}

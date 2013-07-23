#include "GameEndLayer.h"
#include "GameScene.h"
#include "data.h"
#include "SelectLevelLayer.h"
#include "SelectLevelScene.h"

using namespace cocos2d;

// Initialization.
bool GameEndLayer::init()
{
	bool bRect = false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		pigCache = CCSpriteFrameCache::sharedSpriteFrameCache();
		pigCache->addSpriteFramesWithFile(pigList, pigImageList);

		bRect = true;
	} while (0);
	return bRect;
}

// Generate a layer show the win information.
CCLayer* GameEndLayer::generateWinLayer()
{
	this->addChild(generateBackground(winBackground), 0);

	// Show the score.************************************
	// Show the score.************************************
	// Show the score.************************************
	// Show the score.************************************

	// Add menu of win to the layer.
	addWinMenu();

	return this;
}

// Generate a layer show the fail information.
CCLayer* GameEndLayer::generateFailLayer()
{
	this->addChild(generateBackground(failBackground), 0);

	// Add menu of fail to the layer.
	addFailMenu();

	return this;
}

// Generate background.
CCSprite* GameEndLayer::generateBackground(const char* fileName)
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	// Add  background.
	CCSprite* background = CCSprite::create(fileName);
	background->setPosition(winSize / 2);

	// Scale the background.
	CCSize bgSize = background->getContentSize();
	float scaleX = winSize.width / bgSize.width;
	float scaleY = winSize.height / bgSize.height;
	background->setScaleX(scaleX);
	background->setScaleY(scaleY);

	return background;
}

// Add button menu to win layer.
void GameEndLayer::addWinMenu()
{
	CCMenuItemImage* replay = CCMenuItemImage::create(nameOfRestartNormal, nameOfRestartSelect, this,
		menu_selector(GameEndLayer::onReplay));
	replay->setScale(1.5f);
	CCMenuItemImage* levels = CCMenuItemImage::create(nameOfSelectLevelNormal, nameOfSelectLevelSelect, this,
		menu_selector(GameEndLayer::onLevels));
	levels->setScale(1.5f);
	CCMenuItemImage* next = CCMenuItemImage::create(nextButtonNormal, nextButtonSelect, this,
		menu_selector(GameEndLayer::onNext));
	next->setScale(1.5f);
	CCMenu* menu = CCMenu::create(replay, levels, next, NULL);

	// Padding the items.
	menu->alignItemsHorizontallyWithPadding(20);
	menu->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2 - levels->getPositionX(),
		CCDirector::sharedDirector()->getWinSize().height / 4));

	this->addChild(menu, 2);
}

// Add button menu to fail layer.
void GameEndLayer::addFailMenu()
{
	CCMenuItemImage* replay = CCMenuItemImage::create(nameOfRestartNormal, nameOfRestartSelect, this,
		menu_selector(GameEndLayer::onReplay));
	replay->setScale(1.5f);
	CCMenuItemImage* levels = CCMenuItemImage::create(nameOfSelectLevelNormal, nameOfSelectLevelSelect, this,
		menu_selector(GameEndLayer::onLevels));
	levels->setScale(1.5f);

	CCMenu* menu = CCMenu::create(replay, levels, NULL);
	//menu->setScale(1.5f);

	// Padding the items.
	menu->alignItemsHorizontallyWithPadding(20);

	menu->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2 ,
		CCDirector::sharedDirector()->getWinSize().height / 3));
	this->addChild(menu, 2);
}

// Response to replay item.
void GameEndLayer::onReplay(CCObject* pSender)
{
	GameScene* gameScene = GameScene::create();
	CCDirector::sharedDirector()->replaceScene(CCTransitionProgressHorizontal::create(0.5f,gameScene));
}

// Response to next item.
void GameEndLayer::onNext(CCObject* pSender)
{
	SelectLevelLayer::addLevelNum();
	GameScene* gameScene = GameScene::create();
	CCDirector::sharedDirector()->replaceScene(CCTransitionProgressHorizontal::create(0.5f,gameScene));
}

// Response to levels item.
void GameEndLayer::onLevels(CCObject* pSender)
{
	SelectLevelScene* selectLevel = SelectLevelScene::create();
	CCDirector::sharedDirector()->replaceScene(CCTransitionProgressHorizontal::create(0.5f,selectLevel));
}

// Generate animation of win scene.
void GameEndLayer::generateWinAnimation()
{

}

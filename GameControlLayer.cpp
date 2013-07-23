#include "GameControlLayer.h"
#include "GameScene.h"
#include "SelectLevelScene.h"
USING_NS_CC;
using namespace std;

#define  PI 3.1415926

// on "init" you need to initialize your instance
bool GameControlLayer::init()
{
	bool bRet = false;
	do 
	{
		//////////////////////////////////////////////////////////////////////////
		// super init first
		//////////////////////////////////////////////////////////////////////////

		CC_BREAK_IF(! CCLayer::init());
		
		winSize = CCDirector::sharedDirector()->getWinSize();

		//暂停菜单
		CCMenuItemImage *pPauseItem = CCMenuItemImage::create(
			nameOfPauseNormal,
			nameOfPauseSelect,
			this,
			menu_selector(GameControlLayer::menuPauseAndContinueCallback));
		CC_BREAK_IF(! pPauseItem);

		//pPauseItem->setPosition(ccp(winSize.width - pPauseItem->getContentSize().width / 2 , winSize.height - pPauseItem->getContentSize().height / 2));

		//重玩菜单
		CCMenuItemImage *pRestartItem = CCMenuItemImage::create(
			nameOfRestartNormal,
			nameOfRestartSelect,
			this,
			menu_selector(GameControlLayer::menuReplayCallback));
		CC_BREAK_IF(! pRestartItem);
		//pRestartItem->setPosition(ccpSub(pPauseItem->getPosition(),ccp(pRestartItem->getContentSize().width,0)));

		//返回主菜单
		CCMenuItemImage *pGoBackMenuItem = CCMenuItemImage::create(
			nameOfSelectLevelNormal,
			nameOfSelectLevelSelect,
			this,
			menu_selector(GameControlLayer::menuGaBackMenuCallback));
		CC_BREAK_IF(! pGoBackMenuItem);
		//pGoBackMenuItem->setPosition(ccpSub(pRestartItem->getPosition(),ccp(pGoBackMenuItem->getContentSize().width,0)));



		// 创建菜单
		CCMenu* pMenu = CCMenu::create(pGoBackMenuItem,pRestartItem,pPauseItem,NULL);
		pMenu->alignItemsHorizontallyWithPadding(pGoBackMenuItem->getContentSize().width / 2);
		pMenu->setPosition(ccp(winSize.width - pGoBackMenuItem->getContentSize().width * 2,winSize.height - pGoBackMenuItem->getContentSize().height));
		CC_BREAK_IF(! pMenu);

		// Add the menu to GameLayer layer as a child layer.
		this->addChild(pMenu, 1);

		isPause = false;

		bRet = true;
	} while (0);

	return bRet;
}

void GameControlLayer::menuReplayCallback(CCObject* pSender)
{
	//重新开始游戏
	GameScene *pScene = GameScene::create();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFlipX::create(0.5f,pScene));

	//(this->getParent())->release();
}

void GameControlLayer::menuPauseAndContinueCallback( CCObject* pSender )
{
	//暂停
	if(!isPause)
	{
		CCDirector::sharedDirector()->stopAnimation();

		isPause = true;
	}
	//继续
	else
	{
		CCDirector::sharedDirector()->startAnimation();
		isPause = false;
	}
}

void GameControlLayer::menuGaBackMenuCallback( CCObject* pSender )
{
	//返回主界面
	SelectLevelScene *pScene = SelectLevelScene::create();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFlipX::create(0.5f,pScene));
}

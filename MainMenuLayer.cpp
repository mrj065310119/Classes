#include "MainMenuLayer.h"
#include "data.h"
#include "SelectLevelScene.h"

using namespace cocos2d;

// Initialization.
bool MainMenuLayer::init()
{
	bool bRect = false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		generateBackground();
		generateMenu();

		bRect = true;
	} while (0);
	return bRect;
}

// Generate background.
void MainMenuLayer::generateBackground()
{
	srand(time(0));
	// Get game window size.
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	// Create sky.
	CCSprite* sky = CCSprite::create(skyImage);
	sky->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	CCSize bgSize = sky->getContentSize();

	// Calculate the scale values between window size and sky size.
	scaleX = winSize.width / bgSize.width;
	scaleY = winSize.height / bgSize.height;
	maxScale = ((scaleY > scaleY) ? scaleX : scaleY);

	// Scale the sky and add it to the layer.
	sky->setScaleX(scaleX);
	sky->setScaleY(scaleY);
	this->addChild(sky, 0);

	// Add sun.
	CCSprite* sun = CCSprite::create(sunImage);
	sun->setPosition(ccp(100.0, winSize.height - 50));
	this->addChild(sun, 1);

	// Add ground.
	int i = 0;
	int total = 0;
	float high = 0;
	while(total < winSize.width){
		CCSprite* ground = CCSprite::create(groundImage);
		high = ground->getContentSize().height;
		ground->setPosition(ccp((i + 0.5) * ground->getContentSize().width , 
			high / 2));
		this->addChild(ground, 5);
		i++;
		total += ground->getContentSize().width;
	}

	// Add trees.
	for(int i = 0; i < 20; i++)
	{
		CCSprite* tree = CCSprite::create(treeImage);
		float x = rand() % (int)(winSize.width / 2) + winSize.width / 2;
		tree->setPosition(ccp(x, high + 10));
		this->addChild(tree, 1);
	}

	// Add pigs.
	for(int i = 0; i < 3; i++)
	{
		CCSprite* pig = CCSprite::create(pigs[0]);
		float scalePig = (winSize.width / 8) / pig->getContentSize().width;
		pig->setScale(scalePig);
		pig->setPosition(ccp((i + 0.5) * (pig->getContentSize().width / 2 * scalePig), 
			high + 10));
		this->addChild(pig, 2);
	}

	CCSprite *title = CCSprite::create("title.png");
	title->setScale(maxScale);
	title->setPosition(ccp(winSize.width / 2,winSize.height / 3));
	this->addChild(title);
}

// Create the menu.
void MainMenuLayer::generateMenu()
{

	// Get game window size.
 	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	// Create play selection.
	CCSprite* playSelection = CCSprite::create(clouds[0]);
	float sx = winSize.width / playSelection->getContentSize().width / 8;
	float sy = winSize.height / playSelection->getContentSize().height / 8;
	float maxs = ((sx > sy) ? sx : sy);
	CCMenuItemSprite* playItem = CCMenuItemSprite::create(playSelection,
		NULL, NULL, this, menu_selector(MainMenuLayer::play));
	playItem->setScale(maxs);
	playItem->setPosition(ccp(rand() % (int)(winSize.width / 8) + winSize.width / 6 ,
		rand() % (int)(winSize.height / 3) + winSize.height / 2));

	// Create option selection.
	CCSprite* optionSelection = CCSprite::create(clouds[1]);
	CCMenuItemSprite* optionItem = CCMenuItemSprite::create(optionSelection,
		NULL, NULL, this, menu_selector(MainMenuLayer::option));
	optionItem->setScale(maxs);
	optionItem->setPosition(ccp(rand() % (int)(winSize.width / 8) + winSize.width / 6 * 2,
		rand() % (int)(winSize.height / 3) + winSize.height / 2));


	// Create help selection.
	CCSprite* helpSelection = CCSprite::create(clouds[2]);
	CCMenuItemSprite* helpItem = CCMenuItemSprite::create(helpSelection,
		NULL, NULL, this, menu_selector(MainMenuLayer::help));
	helpItem->setScale(maxs);
	helpItem->setPosition(ccp(rand() % (int)(winSize.width / 8) + winSize.width / 6 * 3,
		rand() % (int)(winSize.height / 3) + winSize.height / 2));

	// Create exit selection.
	CCSprite* exitSelection = CCSprite::create(clouds[3]);
	CCMenuItemSprite* exitItem = CCMenuItemSprite::create(exitSelection,
		NULL, NULL, this, menu_selector(MainMenuLayer::exit));
	exitItem->setScale(maxs);
	exitItem->setPosition(ccp(rand() % (int)(winSize.width / 8) + winSize.width / 6 * 4,
		rand() % (int)(winSize.height / 3) + winSize.height / 2));

	// Create the menu with selections above.
	CCMenu* mainMenu = CCMenu::create(playItem, optionItem, helpItem, exitItem, NULL);
	mainMenu->setPosition(ccp(0, 0));
	this->addChild(mainMenu, 4);
}

// Response function of play item in the main menu.
void MainMenuLayer::play(CCObject* pSender)
{
	SelectLevelScene *levelScene = SelectLevelScene::create();
	//CCDirector::sharedDirector()->replaceScene(levelScene);

	CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.5f,levelScene));
}

// Response function of option item in the main menu.
void MainMenuLayer::option(CCObject* pSender)
{

}

// Response function of help item in the main menu.
void MainMenuLayer::help(CCObject* pSender)
{

}

// Response function of exit item in the main menu.
void MainMenuLayer::exit(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();
}
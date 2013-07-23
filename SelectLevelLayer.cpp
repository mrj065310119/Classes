#include "SelectLevelLayer.h"
#include "data.h"
#include "GameScene.h"

using namespace cocos2d;

int SelectLevelLayer::levelNum = 0;
bool SelectLevelLayer::gameComplete = false;

// Initialization.
bool SelectLevelLayer::init()
{
	bool bRect = false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		// Get the window size.
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		// Set the moving velocity.
		velocity = winSize.width;

		// Open the touch function.
		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true); 

		// Generate the layer.
		generateLevelLayer();
		loadDataFromXml();
		bRect = true;
	} while (0);
	return bRect;
}


// Generate the level layer with level selections.
void SelectLevelLayer::generateLevelLayer()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	
	// Load the level icons into cache.
	CCSpriteFrameCache* levelIconCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	levelIconCache->addSpriteFramesWithFile(levelItemList, levelItemImageList);

	// For each cycle, generate a menu with nine levels.
	// The game totally has three big levels, each big level has nine small levels.
	
	CCSprite *img = CCSprite::createWithSpriteFrame(levelIconCache->spriteFrameByName("0-0.png"));
	int verNum = 3;
	int horNum = 3;
	float startx = winSize.width / 2.0 - (verNum / 2.0 - 0.5) * img->getContentSize().width * 1.5;
	float kx = startx;
	float starty = winSize.height / 2.0 + (horNum / 2.0 - 0.5) * img->getContentSize().height * 1.2 ;
	float ky = starty;
	
	menuItems = CCArray::create();
	menuItems->retain();
	
	for (int i = 0; i < 3; i++)
	{
		kx = startx;
		ky = starty;

		CCLayer* level = CCLayer::create();
		CCPoint position = ccp(10 + i * 200, winSize.height / 5);
		level->setPosition(ccp( winSize.width * i, 0));
		this->addChild(level, 1);

		// Add background to the level.
		CCSprite* background = CCSprite::create(levelBg[i]);
		background->setPosition(ccp(winSize.width / 2, winSize.height / 2));
		CCSize bgSize = background->getContentSize();
		float scaleX = winSize.width / bgSize.width;
		float scaleY = winSize.height / bgSize.height;
		background->setScaleX(scaleX);
		background->setScaleY(scaleY);
		level->addChild(background);

		// Generate a level menu.
		CCMenu* levelMenu = CCMenu::create();

		// Generate level items, each item represents one small level.
		char str[20];
		for (int j = 0; j < 9; j++)
		{
			sprintf(str, "%d-%d.png", i, j);
 			CCSprite* levelItemFrame = CCSprite::createWithSpriteFrame(levelIconCache->spriteFrameByName(str));

			sprintf(str, "%d-%ddisable.png", i, j);
			
			CCSprite* levelItemDisableFrame = CCSprite::createWithSpriteFrame(levelIconCache->spriteFrameByName(str));
			
			CCMenuItemSprite *levelItem = CCMenuItemSprite::create(levelItemFrame, NULL,
				levelItemDisableFrame, level, menu_selector(SelectLevelLayer::selectLevel));

			levelItem->setPosition(ccp(kx + (j % verNum) * levelItem->getContentSize().width * 1.5 ,
				                       ky - (j / horNum) * levelItem->getContentSize().height * 1.1 ));
			levelItem->setEnabled(false);
			menuItems->addObject(levelItem);
			int tag = 9 * i + j;

			// Add the item to the menu with a tag.
			levelMenu->addChild(levelItem,0,tag);
		}

		// Scale the menu with window scaling.
		levelMenu->setScaleX(scaleX);
		levelMenu->setScaleY(scaleY);

		levelMenu->setPosition(CCPointZero);

		level->addChild(levelMenu, 2, i);


	}
}

// Get the level number that user selected.
int SelectLevelLayer::getLevelNum()
{
	return levelNum;
}

// Response function of action of selecting a level.
void SelectLevelLayer::selectLevel(CCObject* pSender)
{
	// Record the selected level number, it can be get through get function.
	CCMenuItem* item =(CCMenuItem *)(pSender);
	levelNum = item->getTag();
	
	// Jump to game scene.
	GameScene* gameScene = GameScene::create();
	CCDirector::sharedDirector()->replaceScene(CCTransitionMoveInR::create(0.5f,gameScene));
}

// Add level number of one.
void SelectLevelLayer::addLevelNum()
{
	if(levelNum % 10 < 8)
	{	
		levelNum++;
	} else {
		if (levelNum / 10 < 2)
		{
			levelNum = (levelNum / 10 + 1) * 10;
		} 
		else
		{
			gameComplete = true;
		}
	}
}

// Get the start position of the touch action.
bool SelectLevelLayer::ccTouchBegan(
	cocos2d::CCTouch* touch,cocos2d::CCEvent* event)
{
	startPosition = touch->getLocation();

	// Set the start position as last position.
	lastPosition = touch->getLocation();
	return true;
}

// Get the end position of the touch action, and move the levelLayer.
void SelectLevelLayer::ccTouchEnded(
	cocos2d::CCTouch* touch, cocos2d::CCEvent* event)
{
	endPosition = touch->getLocation();
	moveLevelLayer();
}

// Response function of touch action, move the levelLayer with mouse.
void SelectLevelLayer::moveLevelLayer()
{
	// Get current levelLayer position.
	CCPoint currentPosition = this->getPosition();
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	float maxX = 0;
	float minX = -2 * winSize.width;

	// If current big level in the screen is the first one, 
	// the layer cannot be dragged to the right.
	if (currentPosition.x > maxX)
	{
		float duration = (currentPosition.x - maxX) / velocity;
		moveLayer( ccp(maxX, currentPosition.y), duration);
		return;
	}
	// If current big level in the screen is the last one, 
	// the layer cannot be dragged to the left.
	if (currentPosition.x < minX)
	{
		float duration = (minX - currentPosition.x) / velocity;
		moveLayer(ccp(minX, currentPosition.y), duration);
		return;
	}

	// Drag the levelLayer to the right.
	if (startPosition.x < endPosition.x && 
		currentPosition.x < maxX)
	{
		// Calculate the duration of the moving animation.
		float temp = abs((int)currentPosition.x % (int)winSize.width);
		float length = temp;
		float duration = length / velocity;

		// Get the destination position of the levelLayer.
		CCPoint destination = ccp(((int)(currentPosition.x / winSize.width)) * winSize.width, 
			currentPosition.y);
		
		// Move the levelLayer to the destination in time duration.
		moveLayer(destination, duration);
	} 
	// Drag the levelLayer to the left.
	else if(startPosition.x > endPosition.x && 
		currentPosition.x > minX)
	{
		// Calculate the duration of the moving animation.
		float temp = abs((int)currentPosition.x % (int)winSize.width);
		float length = winSize.width - temp;
		float duration = length / velocity;

		// Get the destination position of the levelLayer.
		CCPoint destination = ccp(((int)(currentPosition.x / winSize.width) - 1) * winSize.width, 
			currentPosition.y);
		
		// Move the levelLayer to the destination in time duration.
		moveLayer(destination, duration);
	}
}

// Move the levelLayer to the destination in time t.
void SelectLevelLayer::moveLayer(CCPoint destination, float t)
{
	this->stopAllActions();
	CCFiniteTimeAction* moveAction = CCMoveTo::create(0.5,destination);
	this->runAction(moveAction);
}

// Move the levelLayer while dragging the screen.
void SelectLevelLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint currentPosition = this->getPosition();
	CCPoint mousePosition = pTouch->getLocation();

	float shiftDistance = mousePosition.x - lastPosition.x;
	this->setPosition(ccp(currentPosition.x + shiftDistance, currentPosition.y));

	// Set last position as the current mouse position.
	lastPosition = mousePosition;
}

void SelectLevelLayer::loadDataFromXml()
{
	TiXmlDocument* pDoc = new TiXmlDocument( XML_FILE );
	unsigned long nLength = 0;
	char* pBuff = (char*)cocos2d::CCFileUtils::sharedFileUtils()->getFileData(cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename(XML_FILE).c_str(),"rt", &nLength );
	pDoc->LoadMemory( pBuff, nLength );

	TiXmlElement *Root = pDoc->RootElement();  //根，<Rank>
	TiXmlElement *pFirE = Root->FirstChildElement("unlocks"); //叶子节点
	TiXmlElement *pUnLocks = pFirE->FirstChildElement();

	while(pUnLocks != NULL)
	{
		if(!pUnLocks->ValueStr().compare("unlock"))
		{
			int num = atoi(pUnLocks->FirstChild()->Value());
			CCMenuItem *item = (CCMenuItem *)menuItems->objectAtIndex(num);
			item->setEnabled(true);
		}
		pUnLocks = pUnLocks->NextSiblingElement();
	}

	delete pDoc;
}
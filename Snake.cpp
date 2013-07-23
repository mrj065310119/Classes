// 
#include "Snake.h"
// 
Snake::Snake():Animal()
{
	type = SNAKE;
	moveTime = 10.0f;
	lifeNum = 1.2f;
	lifeLeft = lifeNum;
	init();	 
}

Snake::Snake( float life,float time ):Animal(life,time)
{
}

bool Snake::init()
{
	bool bRet = false;
	do 
	{	
		CC_BREAK_IF(!CCSprite::initWithFile("snake1.png"));
		pLife->setPosition(ccp(pLife->getContentSize().width / 2,this->getContentSize().height + pLife->getContentSize().height));

		CCAnimation* animation =CCAnimation::create();
		//char *spriteImg[] = {"snake1.png","snake2.png","snake3.png","snake4.png","snake5.png","snake6.png","snake7.png"};

		char str[20];
		for(int i=0;i<7;i++)
		{
			sprintf(str,"snake%d.png",i + 1);
			animation->addSpriteFrameWithFileName(str);
		}
		animation->setDelayPerUnit(0.1f);
		animation->setRestoreOriginalFrame(true);
		myAction = CCRepeatForever::create(CCAnimate::create(animation));
		myAction->retain();
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		this->setPosition(ccp(size.width, 12));	
		produceLoc = ccp(size.width, 12);

		bRet = true;
	} while (0);

	return bRet;
}

float Snake::moveBack()
{
	//CCSprite::initWithFile("snakeBack1.png");
	//pLife->setRotationY(180);
	deleteExploreShit();
	this->stopAllActions();
	CCAnimation* animation =CCAnimation::create();

	char str[20];
	for(int i=0;i<3;i++)
	{
		sprintf(str,"snakeBack%d.png",i + 1);
		animation->addSpriteFrameWithFileName(str);
	}
	animation->setDelayPerUnit(0.2f);
	animation->setRestoreOriginalFrame(true);
	myAction = CCRepeatForever::create(CCAnimate::create(animation));
	this->runAction(myAction);

	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCActionInterval *move = CCMoveTo::create(moveTime / 2,ccp(size.width, 12));
	moveTo = CCSequence::create(move/*,CCCallFuncN::create(this,callfuncN_selector(GameLayer::deleteAnimal))*/,NULL);

	this->runAction(moveTo);

	hasMoveBack = true;
	return moveTime / 2;
}


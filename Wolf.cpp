// 
#include "Wolf.h"
// 
 Wolf::Wolf():Animal()
 {
	type = WOLF;
	moveTime = 8.0f;
	lifeLeft = lifeNum;
	init();	 
 }

 Wolf::Wolf( float life,float time ):Animal(life,time)
 {
 }

bool Wolf::init()
{
	bool bRet = false;
	do 
	{	
		CC_BREAK_IF(!CCSprite::initWithFile("wolf1.png"));
		pLife->setPosition(ccp(getContentSize().width / 2,this->getContentSize().height + pLife->getContentSize().height));
	
		CCAnimation* animation =CCAnimation::create();
		
		char str[20];
		for(int i=0;i<3;i++)
		{
			sprintf(str,"wolf%d.png",i + 1);
			animation->addSpriteFrameWithFileName(str);
		}
		animation->setDelayPerUnit(0.25f);
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

float Wolf::moveBack()
{
	deleteExploreShit();
	this->stopAction(moveTo);
	CCSprite::setRotationY(180);
	pLife->setRotationY(180);
	
	CCSprite *pig = CCSprite::create("pig.png");
	pig->setRotation(90);
	pig->setPosition(ccp(getContentSize().width / 4,getContentSize().height / 2));
	this->addChild(pig,-1);

	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCActionInterval *move = CCMoveTo::create(moveTime / 2,ccp(size.width, 12));
	moveTo = CCSequence::create(move/*,CCCallFuncN::create(this,callfuncN_selector(GameLayer::deleteAnimal))*/,NULL);
	this->runAction(moveTo);

	hasMoveBack = true;

	return moveTime / 2;
}


// 
#include "Eagle.h"
// 
Eagle::Eagle():Animal()
{
	type = EAGLE;
	lifeNum = 0.6f;
	lifeLeft = lifeNum;
	moveTime = 5.0f;
	init();	 
}

Eagle::Eagle( float life,float time ):Animal(life,time)
{
}

bool Eagle::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCSprite::initWithFile("eagle1.png"));
		pLife->setPosition(ccp(getContentSize().width / 2,this->getContentSize().height + pLife->getContentSize().height));

		CCAnimation* animation =CCAnimation::create();
		char *spriteImg[] = {"eagle1.png","eagle2.png","eagle3.png","eagle4.png","eagle3.png","eagle2.png","eagle1.png"};
		
		for(int i=0;i<7;i++)
			animation->addSpriteFrameWithFileName(spriteImg[i]);
		animation->setDelayPerUnit(0.05f);
		animation->setRestoreOriginalFrame(true);
		myAction = CCRepeatForever::create(CCAnimate::create(animation));
		myAction->retain();

		CCSize size = CCDirector::sharedDirector()->getWinSize();
		this->setPosition(ccp(size.width,size.height - getContentSize().height / 2));	
		produceLoc = ccp(size.width,size.height - getContentSize().height / 2);
		CCActionInterval *move = CCMoveTo::create(moveTime / 2,ccp(size.width, 12));
	
		moveTo = CCSequence::create(move,CCCallFunc::create(this,callfunc_selector(Eagle::deleteSelf)),NULL);

		bRet = true;
	} while (0);

	return bRet;
}

float Eagle::moveBack()
{
	deleteExploreShit();
	this->stopAction(moveTo);
	CCSprite::setRotationY(180);
	pLife->setRotationY(180);

	CCSprite *pig = CCSprite::create("pig.png");
	pig->setRotationY(180);
	pig->setPosition(ccp(getContentSize().width / 2,0));
	this->addChild(pig);

	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCActionInterval *move = CCMoveTo::create(moveTime / 2,ccp(size.width,size.height - getContentSize().height / 2));
	//moveTo = CCMoveTo::create(moveTime / 2,ccp(size.width,size.height - getContentSize().height / 2));
	//moveTo = CCSequence::create(move,CCCallFuncN::create(this,callfuncN_selector(GameLayer::deleteAnimal)),NULL);
	moveTo = CCSequence::create(move/*,CCCallFuncN::create(this,callfuncN_selector(GameLayer::deleteAnimal))*/,NULL);
	this->runAction(moveTo);

	hasMoveBack = true;

	return moveTime / 2;
}


#include "Animal.h"
#include <math.h>
Animal::Animal()
{
	lifeNum = 1.0f;
	lifeLeft = lifeNum;
	moveTime = 10.0f;
	speed = 1.0f;
	hasMoveBack = false;
	exploreShitTag = 100;
	//abc = 111;
	init();
	pLife = CCSprite::create(nameOfLifeLine);
	pLife->setPosition(ccp(getContentSize().width / 2,getContentSize().height + pLife->getContentSize().height));
	//pLife->setAnchorPoint(CCPointZero);
	pLifeLeft = CCSprite::create(nameOfLife);
	pLifeLeft->setPosition(CCPointZero);
	pLifeLeft->setAnchorPoint(CCPointZero);
	pLife->addChild(pLifeLeft);
	this->addChild(pLife);
}

Animal::Animal( float life,float time )
{
	Animal();
	lifeLeft = lifeNum = life;
	moveTime = time;
}

Animal::~Animal()
{}

bool Animal::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCSprite::initWithFile("eagle1.png"));
			
		CCAnimation* animation =CCAnimation::create();
		char *spriteImg[] = {"eagle1.png","eagle2.png","eagle3.png","eagle4.png","eagle3.png","eagle2.png","eagle1.png"};
		
		for(int i=0;i<7;i++)
			animation->addSpriteFrameWithFileName(spriteImg[i]);
		animation->setDelayPerUnit(0.05f);
		animation->setRestoreOriginalFrame(true);
		myAction = CCRepeatForever::create(CCAnimate::create(animation));
		
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		moveTo = CCMoveTo::create(moveTime,ccp(0,size.height - getContentSize().height));

		produceLoc = ccp(size.width,size.height - getContentSize().height / 2);
		this->setPosition(ccp(size.width,size.height - getContentSize().height / 2));	
		
		bRet = true;
	} while (0);
	
	return bRet;
}


void Animal::beAttacked( float lost )
{
	lifeLeft -= lost;
	pLife->removeChild(pLifeLeft,true);

	pLifeLeft = CCSprite::create(nameOfLife);
	pLifeLeft->setPosition(CCPointZero);
	pLifeLeft->setAnchorPoint(CCPointZero);
	pLifeLeft->setScaleX(lifeLeft / lifeNum);
	pLife->addChild(pLifeLeft);


}

float Animal::getLifeNum()
{
	return lifeLeft;
}

void Animal::moveToPig( cocos2d::CCPoint loc )
{
	pigLoc = loc;
	speed = (this->getPositionX() - loc.x) / moveTime;
	moveTo = CCMoveTo::create(moveTime,loc);
	this->runAction(moveTo);
	this->runAction(myAction);
}

void Animal::reduceSpeed()
{
	
	CCPoint loc;
	if(hasMoveBack)
		return;
	else
		loc = pigLoc;
	exploreShit = CCSprite::create("exploreShit.png");
	exploreShit->setPosition(ccp(getContentSize().width / 2,0));
	if(this->getChildByTag(exploreShitTag) != NULL)
		this->removeChild(exploreShit,true);
	this->addChild(exploreShit,0,exploreShitTag);
	this->stopAction(moveTo);
	float angle = fabs((getPositionY() - loc.y) / (getPositionX() - loc.x)); 
	float keepTime = 3.0f;
	float tempSpeed = 0.5 * speed;
	float nextLocx,nextLocy;
	if(getPositionX() - loc.x >= 0)
	{
		nextLocx = getPositionX() - tempSpeed * keepTime * cos(angle);
		nextLocy = getPositionY() - tempSpeed * keepTime * sin(angle);
		if (nextLocx < loc.x)
		{	
			keepTime = (getPositionX() - loc.x) / tempSpeed;
			nextLocx = loc.x;
			nextLocy = loc.y;
		}
	}
	else if(getPositionX() - loc.x < 0)
	{
		nextLocx = getPositionX() + tempSpeed * keepTime * cos(angle);
		nextLocy = getPositionY() + tempSpeed * keepTime * sin(angle);
		if (nextLocx > loc.x)
		{	
			keepTime = (loc.x - getPositionX()) / tempSpeed;
			nextLocx = loc.x;
			nextLocy = loc.y;
		}
	}

	CCPoint nextLoc = ccp(nextLocx,nextLocy);
	CCActionInterval *moveTo1 = CCMoveTo::create(keepTime,nextLoc);
	float nextTime = fabs(nextLoc.x - loc.x) / speed;
	CCActionInterval *moveTo2 = CCMoveTo::create(nextTime,loc);
	moveTo = CCSequence::create(moveTo1,CCCallFunc::create(this,callfunc_selector(Animal::deleteExploreShit)),moveTo2,NULL);
	
	this->runAction(moveTo);
	//this->runAction(myAction);
}

void Animal::deleteExploreShit()
{
	if(getChildByTag(exploreShitTag) != NULL)
		this->removeChild(exploreShit,true);
}

float Animal::moveBack()
{
	return 0;
}

void Animal::deleteSelf()
{
	removeFromParentAndCleanup(true);
}

animalType Animal::getType()
{
	return type;
}

bool Animal::isMoveBack()
{
	return hasMoveBack;
}


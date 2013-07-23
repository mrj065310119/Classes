#include "Player.h"
USING_NS_CC;

Player::Player(void)
{
	
}


Player::~Player(void)
{
	pigs->release();
	totalShits->release();
}

bool Player::init()
{
	bool bRet = false;
	do 
	{
		// Load the level icons into cache.
		CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
		cache->addSpriteFramesWithFile(farmerPlist, farmerPvrczz);
		CCSprite::initWithSpriteFrame(cache->spriteFrameByName("farmerStand.png"));
		//CCSprite::initWithFile(nameOfPlayer);
		//初始化站立动作
		CCAnimation* animation = CCAnimation::create();
		int count = 6;
		while(count--)
			animation->addSpriteFrame(cache->spriteFrameByName("farmerStand.png"));
		animation->addSpriteFrame(cache->spriteFrameByName("farmerStand2.png"));

		animation->setDelayPerUnit(0.2f);
		animation->setRestoreOriginalFrame(true);
		standAction = CCRepeatForever::create(CCAnimate::create(animation));
		this->runAction(standAction);
		
		//初始化抛投动作
		CCAnimation* animationThrow =CCAnimation::create();
		char str[20];
		for (int i= 0;i < 4;i++)
		{
			sprintf(str,"farmerThrow%d.png",(4 - i));
			animationThrow->addSpriteFrame(cache->spriteFrameByName(str));
		}
		animationThrow->setDelayPerUnit(0.05f);
		animationThrow->setRestoreOriginalFrame(true);
		
		//创建抛投动作
		throwAction = CCAnimate::create(animationThrow);
		throwAction->retain();

		//初始化Player数据
		numOfPig = 5;

		for (int i = 0;i < numOfType;i++)
			numOfShit[i] = 1;
		totalShits = CCArray::create();
		totalShits->retain();


		pigs = CCArray::create();
		pigs->retain();
		for (int i = 0;i < numOfPig;i++)
		{
			Pig *pig = Pig::create();
			pigs->addObject(pig);
		}

		
		bRet = true;
	}while(0);


	return bRet;
}


void Player::updateNumOfPig( int inc )
{
	int count = inc;
	if(inc < 0)
		while(inc++ < 0 && numOfPig > 0)
		{
			numOfPig--;
			Pig *pig = (Pig *)pigs->objectAtIndex(pigs->count() - 1);
			this->removeChild(pig,true);
			pigs->removeLastObject(true);		
			
		}
	else if(inc >= 0)
		while(inc-- > 0 && numOfPig > 0 )
		{
			numOfPig++;
			Pig *pig = Pig::create();
			this->addChild(pig);
			pigs->addObject(pig);
		}

	//numOfPig += count;
}

int Player::getNumOfPig()
{
	return numOfPig;
}

void Player::useShit(int type)
{
	this->runAction(throwAction);
	numOfShit[type]--;
}

cocos2d::CCArray* Player::getTotalShits()
{
	int num = pigs->count();
	for (int i = 0;i < num;i++)
	{
		Pig *temp = (Pig *)pigs->objectAtIndex(i);
		totalShits->addObjectsFromArray(temp->getShits());
	}

	int numOfTotal = totalShits->count();
	for (int i = 0;i < numOfTotal;i++)
	{
		Shit *temp = (Shit *)totalShits->objectAtIndex(i);
		numOfShit[temp->getShitType()]++;
	}
	totalShits->removeAllObjects();
	return totalShits;
}

int Player::getNumOfShit(int type)
{
	getTotalShits();
	return numOfShit[type];
}

cocos2d::CCArray* Player::getPigs()
{
	return pigs;
}

void Player::deletePigAtIndex( int index )
{
	numOfPig--;
	Pig *pig = (Pig *)pigs->objectAtIndex(index);
	pigs->removeObjectAtIndex(index);
}

void Player::setPigNum(int num)
{
	pigs->removeAllObjects();
	numOfPig = num;
	for (int i = 0 ; i< numOfPig ;i++)
	{
		Pig *pig = Pig::create();
		pigs->addObject(pig);
	}
}




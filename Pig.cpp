
#include "Pig.h"
#include "cocos2d.h"
using namespace cocos2d;
//////构造函数与解析函数
Pig::Pig()
{
}
Pig::~Pig()
{
	shits->release();
}

bool Pig::init()
{
	bool bRet = false;

	do 
	{
		CC_BREAK_IF(!CCSprite::init());
		CC_BREAK_IF(!CCSprite::initWithFile("pig.png"));
		shits = CCArray::create();
		shits->retain();

		speedOfProduce = 5.0f;
		this->schedule(schedule_selector(Pig::produceShit),speedOfProduce);
		bRet = true;
	} while (0);

	return bRet;
}

void Pig::produceShit( float dt )
{
	shit = Shit::create();
	int type = rand() % numOfType;
	shit->setShitType(type);
	shits->addObject(shit);

	//Shit *temp = Shit::create(nameOfShit[type]);
}

cocos2d::CCArray* Pig::getShits()
{
	CCArray *temp = CCArray::create();
	for (unsigned int i = 0;i < shits->count();i++)
		temp->addObject(shits->objectAtIndex(i));
	
	shits->removeAllObjects();
	return temp;
}

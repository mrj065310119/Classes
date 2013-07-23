#pragma once
#include "cocos2d.h"
#include "data.h"
using namespace cocos2d;
enum animalType{WOLF,EAGLE,SNAKE};

class Animal: public cocos2d::CCSprite
{
public:
	Animal();
	Animal(float life,float time);
	~Animal();
	virtual bool init();
	virtual float moveBack();

	void moveToPig(cocos2d::CCPoint loc);
	void reduceSpeed();
	void beAttacked(float lost);
	float getLifeNum();
	bool isMoveBack();
	void deleteExploreShit();
	void deleteSelf();
	animalType getType();
protected:
	animalType type;
	float lifeNum;
	float lifeLeft;
	float speed;
	float moveTime;
	bool hasMoveBack;
	CCSprite *pLife;
	CCSprite *pLifeLeft;
	CCActionInterval* moveTo;
	CCActionInterval* myAction;
	CCSprite *exploreShit;
	int exploreShitTag;
	CCPoint produceLoc;
	CCPoint pigLoc;
};

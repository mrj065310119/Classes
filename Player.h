#pragma once
#include "cocos2d.h"
#include "Pig.h"


class Player: public cocos2d::CCSprite
{
public:
	Player();
	~Player();
	//static Player* create();
	virtual bool init();

	void useShit(int type);
	void setPigNum(int num);

	void updateNumOfPig(int inc);
	void deletePigAtIndex(int index);
	int getNumOfPig();

	cocos2d::CCArray* getTotalShits();
	int getNumOfShit(int type);
	cocos2d::CCArray* getPigs();

	CREATE_FUNC(Player);

private:
	int numOfShit[numOfType];
	cocos2d::CCArray *totalShits;
	cocos2d::CCArray *pigs;
	int numOfPig;
	cocos2d::CCActionInterval *throwAction;
	cocos2d::CCActionInterval *standAction;
};

#ifndef __SHIT_H__
#define __SHIT_H__

#include "cocos2d.h"

#include "SimpleAudioEngine.h"


class Shit:public cocos2d::CCSprite
{
public:
	Shit();
	~Shit();

	virtual bool init();
	int getShitType();
	void setShitType(int type);
	bool getState();
	void setState(bool flag);

	float getPower();

   CREATE_FUNC(Shit);
private:
	bool hasShooted;
	int shitType;
	float power;
	
};

#endif  // __SHIT_H__
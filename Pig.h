#ifndef __PIG_H__
#define __PIG_H__

#include "cocos2d.h"
#include "data.h"
#include "Shit.h"

class Pig : public cocos2d::CCSprite
{
public:
	Pig();
	~Pig();
//	bool init();

	void produceShit(float dt);
	virtual bool init();

	cocos2d::CCArray* getShits();
	CREATE_FUNC(Pig);
private:
	cocos2d::CCArray *shits;
	float speedOfProduce;
	Shit *shit;
};

#endif  // __PIG_H__
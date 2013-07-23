#pragma once
#include "Animal.h"
#include "GameLayer.h"

class Snake: public Animal
{
public:
	Snake();
	Snake(float life,float time);
	virtual bool init();
	virtual float moveBack();
	
};

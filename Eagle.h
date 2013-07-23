#pragma once
#include "Animal.h"
#include "GameLayer.h"

class Eagle: public Animal
{
public:
	Eagle();
	Eagle(float life,float time);
	virtual bool init();
	virtual float moveBack();

};
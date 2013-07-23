#pragma once
#include "Animal.h"
#include "GameLayer.h"

class Wolf: public Animal
{
public:
	Wolf();
	Wolf(float life,float time);
 	virtual bool init();
	virtual float moveBack();

};
#include "Shit.h"
#include "data.h"

Shit::Shit()
{}
Shit::~Shit()
{}


int Shit::getShitType()//����shit������
{
	return shitType;
}
void Shit::setShitType(int type)//����shit������
{
	power = shitPower[type];
	shitType = type;
	char str[20];
	sprintf(str,"shit%d.png",type + 1);
	CCSprite::initWithFile(str);

}

bool Shit::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! CCSprite::init());
		
		CC_BREAK_IF(!CCSprite::initWithFile("shit1.png"));
		hasShooted = false;
		shitType = 1;
		power = 0.2f;

		bRet = true;
	} while (0);

	return bRet;
}

bool Shit::getState()
{
	return hasShooted;
}

void Shit::setState( bool flag )
{
	hasShooted = flag;
}

float Shit::getPower()
{
	return power;
}



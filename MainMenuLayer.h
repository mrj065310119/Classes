#ifndef __MAINMENULAYER_H__
#define __MAINMENULAYER_H__

#include "cocos2d.h"

using namespace cocos2d;

class MainMenuLayer : public CCLayer
{
public:
	// Initialize the data.
	bool init();

	// Generate background.
	void generateBackground();

	// Create the menu.
	void generateMenu();

	// Response function of play item in the main menu.
	void play(CCObject* pSender);

	// Response function of option item in the main menu.
	void option(CCObject* pSender);

	// Response function of help item in the main menu.
	void help(CCObject* pSender);

	// Response function of exit item in the main menu.
	void exit(CCObject* pSender);

	CREATE_FUNC(MainMenuLayer);
private:
	float scaleX;
	float scaleY;
	float maxScale;
};

#endif
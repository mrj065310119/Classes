#ifndef __SELECTLEVELLAYER_H__
#define __SELECTLEVELLAYER_H__

#include "cocos2d.h"
using namespace cocos2d;

class SelectLevelLayer : public CCLayer
{
public:
	bool init();

	// Generate the level layer with level selections.
	void generateLevelLayer();

	// Get the level number that user selected.
	static int getLevelNum();

	// Add level number of one.
	static void addLevelNum();

	// Response function of select a level.
	void selectLevel(CCObject* pSender);

	// Get start position and end position of touch action.
	bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	void ccTouchEnded(CCTouch* touch, CCEvent* event);

	// Move the layer while 
	void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);

	// Response function of touch action.
	void moveLevelLayer();
	// Move the layer to the destination in time t.
	void moveLayer(CCPoint destination, float t);

	void loadDataFromXml();

	CREATE_FUNC(SelectLevelLayer);

	static int levelNum;
private:
	CCArray *menuItems;
	// Record the start position and end position of the touch action.
	CCPoint startPosition;
	CCPoint endPosition;

	// Record the last position of the mouse while dragging.
	CCPoint lastPosition;

	// Velocity of the layer moving action.
	int velocity;

	static bool gameComplete;
};

#endif
#ifndef __SELECTLEVELSCENE_H__
#define __SELECTLEVELSCENE_H__

#include "data.h"
#include "cocos2d.h"
#include "SelectLevelLayer.h"

class SelectLevelScene : public cocos2d::CCScene
{
public:
	SelectLevelScene(){}
	// Initialize the resource.
	bool init();

	// Add background.
	void addBackground();

	CREATE_FUNC(SelectLevelScene);
private:
	cocos2d::CCLayer* backgroundLayer;
	SelectLevelLayer* levelLayer;
};


#endif
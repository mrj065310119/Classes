#ifndef __GAMELAYER_H__
#define __GAMELAYER_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "SimpleAudioEngine.h"
#include "Wolf.h"
#include "Eagle.h"
#include "Snake.h"
#include "Player.h"

class GameLayer : public cocos2d::CCLayer
{
public:
	void loadDataFromXml();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
	void initBox2d();
	void initExplosion(cocos2d::CCPoint location);
	void update(float dt);
	void addNewSpriteWithCoords( cocos2d::CCPoint point, cocos2d::CCSprite *sprite );//添加精灵
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // implement the "static node()" method manually
    CREATE_FUNC(GameLayer);

	//单点触控
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch,cocos2d::CCEvent *pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch *pTouch,cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch,cocos2d::CCEvent *pEvent);
	
	void createBullet(float dt);
	void updateShitsNum(float dt);
	void setShitType(CCObject* pSender);

	void gameLose();
	void gameWin();

	void deleteAnimal(cocos2d::CCNode *pSender);
	void addAnimal(cocos2d::CCNode *pSender);

private:
	cocos2d::CCSize winSize;
	
	//触摸点的坐标
	cocos2d::CCPoint touchBeganLoc;
	cocos2d::CCPoint touchMovedLoc;
	cocos2d::CCPoint touchEndedLoc;
	
	//当前可用shit
	Shit *shit;
	//当前可用shit种类
	int curType;
	//shit对应tag
	int shitTag;
	//已抛出去的shits
	cocos2d::CCArray *shits;
	
	//粒子系统，爆炸效果
	cocos2d::CCParticleSystem* particleSystem;
	//对应tag
	int particleTag;
	
	//蓄力箭头Tag
	int arrowTag;
	//蓄力条力度缩放量
	float scale;

	//菜单项和数字项
	cocos2d::CCArray *shitItems;
	cocos2d::CCArray *labels;

	//Box2D数据
	b2World *world;
	b2Body *body;

	//游戏场景内所有的野兽
	cocos2d::CCArray *animals;
	//每种野兽的数量
	int *numOfAnimals;
	//玩家
	Player *player;
	
	//猪位置
	cocos2d::CCPoint pigLoc;

};

#endif  
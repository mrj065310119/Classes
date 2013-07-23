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
	void addNewSpriteWithCoords( cocos2d::CCPoint point, cocos2d::CCSprite *sprite );//��Ӿ���
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // implement the "static node()" method manually
    CREATE_FUNC(GameLayer);

	//���㴥��
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
	
	//�����������
	cocos2d::CCPoint touchBeganLoc;
	cocos2d::CCPoint touchMovedLoc;
	cocos2d::CCPoint touchEndedLoc;
	
	//��ǰ����shit
	Shit *shit;
	//��ǰ����shit����
	int curType;
	//shit��Ӧtag
	int shitTag;
	//���׳�ȥ��shits
	cocos2d::CCArray *shits;
	
	//����ϵͳ����ըЧ��
	cocos2d::CCParticleSystem* particleSystem;
	//��Ӧtag
	int particleTag;
	
	//������ͷTag
	int arrowTag;
	//����������������
	float scale;

	//�˵����������
	cocos2d::CCArray *shitItems;
	cocos2d::CCArray *labels;

	//Box2D����
	b2World *world;
	b2Body *body;

	//��Ϸ���������е�Ұ��
	cocos2d::CCArray *animals;
	//ÿ��Ұ�޵�����
	int *numOfAnimals;
	//���
	Player *player;
	
	//��λ��
	cocos2d::CCPoint pigLoc;

};

#endif  
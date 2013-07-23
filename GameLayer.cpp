#include "SelectLevelScene.h"
#include "GameEndScene.h"
#include "GameLayer.h"
#include "GameScene.h"
#include "tinyxml.h"
#include "tinystr.h"
#include <math.h>
USING_NS_CC;
using namespace std;

#define PI 3.1415926
#define PTM_RATIO 32


// on "init" you need to initialize your instance
bool GameLayer::init()
{
    bool bRet = false;
    do 
	{
		CC_BREAK_IF(! CCLayer::init());
		winSize = CCDirector::sharedDirector()->getWinSize();
		
		//
		CCMenuItemImage *pCloseItem = CCMenuItemImage::create("CloseNormal.png","CloseSelected.png",this,
																menu_selector(GameLayer::menuCloseCallback));
        CC_BREAK_IF(! pCloseItem);

        pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));

        // Create a menu with the "close" menu item, it's an auto release object.
        CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
        pMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu);

        // Add the menu to GameLayer layer as a child layer.
        this->addChild(pMenu, 1);


        //添加背景图片
        CCSprite* pBackground = CCSprite::create(gameBackground[SelectLevelLayer::getLevelNum() / 10]);
        CC_BREAK_IF(! pBackground);
        // Place the sprite on the center of the screen
		float scalex = winSize.width / pBackground->getContentSize().width;
		float scaley = winSize.height / pBackground->getContentSize().height;
		pBackground->setScaleX(scalex);
		pBackground->setScaleY(scaley);
        pBackground->setPosition(ccp(winSize.width/2, winSize.height/2));	

        // Add the sprite to GameLayer layer as a child layer.
        this->addChild(pBackground, 0);

		curType = 0;  
		shitTag = 100;
		particleTag = 300;
		arrowTag = 700;

		//初始化物理世界
		initBox2d();		
		//初始化爆炸效果
		initExplosion(CCPointZero);  
		
		//初始化游戏数据
		player = Player::create();
		player->setPigNum(5);               //设置猪数量
		CCArray *pigs = CCArray::create();  //新建数组存放猪
		pigs = player->getPigs();

		//放置猪的位置
		CCPoint midLoc;
		for (unsigned int i = 0 ;i < pigs->count();i++)
		{
			Pig *pig = (Pig *)pigs->objectAtIndex(i);
			midLoc = ccp(pig->getContentSize().width ,12);
			pigLoc = midLoc;
			int pigWidth = (int)pig->getContentSize().width;
			pig->setPosition(ccpAdd(midLoc,ccp(-pigWidth / 2 + rand() % pigWidth,0)));
			pig->setRotationY(180);
			pig->setAnchorPoint(CCPointZero);
			this->addChild(pig,pigs->count() - i);
		}
		//放置木板的位置
		Pig *tempPig = Pig::create();
		CCSprite *board = CCSprite::create("board.png");
		board->setPosition(ccpAdd(pigLoc,ccp(-tempPig->getContentSize().width / 2,tempPig->getContentSize().height * 3 / 2)));
		this->addChild(board);

		//放置player的位置
		player->setPosition(ccpAdd(board->getPosition(),ccp(0,player->getContentSize().height / 2 + board->getContentSize().height / 2)));
		this->addChild(player,pigs->count() + 1);
		
		//初始化野兽数目
		numOfAnimals = new int[numOfAnimalType]; 
		animals = CCArray::create();
		animals->retain();

		
		int levelNum = SelectLevelLayer::getLevelNum();
		int bigLevel = levelNum / 9;
		int samllLevel = levelNum % 9;
		numOfAnimals[0] =  (samllLevel + 1);
		numOfAnimals[1] = 0;
		numOfAnimals[2] = 0;
		if(bigLevel == 1 || bigLevel == 2)
			numOfAnimals[1] = (samllLevel + 1);
		if(bigLevel == 2)
			numOfAnimals[2] = (samllLevel + 1);
		
		loadDataFromXml();
		float dt = -2.0f;
		for (int i = 0 ;i < numOfAnimalType;i++)
		{	
			for (int j = 0;j < numOfAnimals[i];j++)
			{
				Animal *newAniaml;
				if(i == 0)
					newAniaml = new Wolf();
				else if(i == 1)
					newAniaml = new Snake();
				else if(i == 2)
					newAniaml = new Eagle();

				newAniaml->setAnchorPoint(CCPointZero);
				this->addChild(newAniaml);
				animals->addObject(newAniaml);

				//定时往猪的地方移动
				dt += float(rand() % 3) + 2;
				newAniaml->runAction(CCSequence::create(CCDelayTime::create(dt),
					CCCallFuncN::create(this,callfuncN_selector(GameLayer::addAnimal)),NULL));
			}
		}

		//产生子弹
		createBullet(0.1f);
		
		//存放已抛投的子弹
		shits = CCArray::create();
		shits->retain();
		
		//shits的菜单项和数量
		shitItems = CCArray::createWithCapacity(numOfType);
		shitItems->retain();
		labels = CCArray::createWithCapacity(numOfType);
		labels->retain();

		CCMenu *shitMenu = CCMenu::create();
		shitMenu->setPosition(CCPointZero);
		char str[20];

		for (unsigned int i = 0; i < numOfType;i++)
		{
			CCMenuItem *shitItem = CCMenuItemImage::create(nameOfShit[i],nameOfShit[i],this,menu_selector(GameLayer::setShitType));
			shitItem->setPosition(ccp((i + 1) * winSize.width / 6,winSize.height * 4 / 5));
			shitItem->setAnchorPoint(CCPointZero);
			shitItem->setScale(1.2f);
			shitItems->addObject(shitItem);
			shitMenu->addChild(shitItem,0,i);

			sprintf(str," X %d",player->getNumOfShit(i));
			CCLabelTTF *label = CCLabelTTF::create(str,"Arial", 24);
			label->setPosition(ccpAdd(shitItem->getPosition(),ccp(shitItem->getContentSize().width * shitItem->getScale(),0.0f)));
			label->setAnchorPoint(CCPointZero);
			this->addChild(label);
			labels->addObject(label);

		}
		this->addChild(shitMenu);

		this->schedule(schedule_selector(GameLayer::updateShitsNum),1.0f);
		

		//this->setTouchEnabled(true);  //多点触控
		//开启单点触控
		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true); 
	
		
        bRet = true;
    } while (0);

    return bRet;
}

void GameLayer::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();
}

bool GameLayer::ccTouchBegan( cocos2d::CCTouch *pTouch,cocos2d::CCEvent *pEvent )
{
	if (player->getNumOfShit(curType) == 0 || shit->getState() )
		return false;
	
	CCPoint location = pTouch->getLocation();

	touchBeganLoc = location;
	return true;
}

void GameLayer::ccTouchEnded( cocos2d::CCTouch *pTouch,cocos2d::CCEvent *pEvent )
{
	if(this->getChildByTag(arrowTag) != NULL)
		this->removeChildByTag(arrowTag);
	CCPoint location = pTouch->getLocation();

	touchEndedLoc = location;
	float detx = touchEndedLoc.x - touchBeganLoc.x;
	float dety = touchEndedLoc.y - touchBeganLoc.y;
	CCPoint normalizeV = ccpNormalize(ccp(detx,dety));
	float maxPower = 0.5 * sqrt(winSize.width * winSize.width + winSize.height * winSize.height) ;
	float curPower = sqrt(detx * detx + dety * dety);
	curPower = (scale < 1.0) ? curPower:maxPower;
	CCPoint curForce = ccpMult(normalizeV,curPower);

	if(this->getChildByTag(shitTag) != NULL)
	{
		b2Vec2 force = body->GetWorldVector(b2Vec2(curForce.x  ,curForce.y ));
		b2Vec2 point_force = body->GetWorldPoint( b2Vec2(0.0f,0.0f) );
		body->SetActive(true);
		body->ApplyForce(force,point_force);
		player->useShit(curType);
		updateShitsNum(0.1f);
		shit->setState(true);
		shits->addObject(shit);
	}
	this->scheduleOnce(schedule_selector(GameLayer::createBullet),0.5);

}

void GameLayer::ccTouchMoved( cocos2d::CCTouch *pTouch,cocos2d::CCEvent *pEvent )
{
	if(this->getChildByTag(arrowTag) != NULL)
		this->removeChildByTag(arrowTag);

	CCPoint location = pTouch->getLocation();
	touchMovedLoc = location;

	float detx = touchMovedLoc.x - touchBeganLoc.x;
	float dety = touchMovedLoc.y - touchBeganLoc.y;
	float power = sqrt(detx * detx + dety * dety);

	float angle = 0;
	if (dety == 0)
		angle = 90;
	else
		angle = atan(detx / dety) * 180 / PI;

	if(detx >= 0 && dety < 0)
		angle += 180;
	else if(detx <= 0 && dety < 0)
		angle -= 180;

	CCSprite *sprite = CCSprite::create(nameOfArrow[0]);
 	sprite->setPosition(shit->getPosition());
	sprite->setAnchorPoint(ccp(0.5,0));
	sprite->setScale(0.8f);
 	sprite->setRotation(angle);

	CCSprite *sprite2 = CCSprite::create(nameOfArrow[1]);
	CCTexture2D *origTexture = sprite2->getTexture();

	scale = power / winSize.width * 2;
	scale = (scale < 1.0) ? scale : 1.0;
// 	CCRect rect = CCRect::CCRect(0,sprite2->getContentSize().height * (1.0 - scale),
// 		sprite2->getContentSize().width,sprite2->getContentSize().height * scale);
	CCRect rect = CCRectMake(0,sprite2->getContentSize().height * (1.0 - scale),
		sprite2->getContentSize().width,sprite2->getContentSize().height * scale);
	CCSprite *destSprite = CCSprite::create();
	destSprite->initWithTexture(origTexture,rect);
	destSprite->setAnchorPoint(CCPointZero);
	sprite->addChild(destSprite);
	
	this->addChild(sprite,player->getZOrder(),arrowTag);

	

}

void GameLayer::initBox2d()
{
	b2Vec2 gravity;
	gravity.Set(0.0f,-12.0f);
	world = new b2World( gravity );//创建世界，gravity可以理解为万有引力，物理中的g

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0); // bottom-left corner
	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	// 创建身体
	b2Body* groundBody = world->CreateBody(&groundBodyDef);
	
	// Define the ground box shape.
	//创建地面形状
	b2EdgeShape groundBox;
	// bottom
	groundBox.Set(b2Vec2(0,0), b2Vec2(winSize.width/PTM_RATIO,0));
	groundBody->CreateFixture(&groundBox,0);
// 	// top
// 	groundBox.Set(b2Vec2(0,winSize.height/PTM_RATIO), b2Vec2(winSize.width/PTM_RATIO,winSize.height/PTM_RATIO));
// 	groundBody->CreateFixture(&groundBox,0);
// 	// left
// 	groundBox.Set(b2Vec2(0,winSize.height/PTM_RATIO), b2Vec2(0,0));
// 	groundBody->CreateFixture(&groundBox,0);
// 	// right
// 	groundBox.Set(b2Vec2(winSize.width/PTM_RATIO,winSize.height/PTM_RATIO), b2Vec2(winSize.width/PTM_RATIO,0));
// 	groundBody->CreateFixture(&groundBox,0);

// 	groundBox.Set(b2Vec2((winSize.width / 2 - 100)/PTM_RATIO,winSize.height / 2 /PTM_RATIO), b2Vec2((winSize.width / 2 + 100 )/PTM_RATIO,winSize.height / 2 /PTM_RATIO));
// 	groundBody->CreateFixture(&groundBox,0);

	this->setAccelerometerEnabled(true);
	this->scheduleUpdate();//执行update函数
}

void GameLayer::update(float dt)
{	
	int32 velocityIterations = 8;
	int32 positionIteratoins = 1;
	world->Step( dt, velocityIterations, positionIteratoins);
	b2Body *node = world->GetBodyList();

	while(node)
	{
		b2Body *b = node;
		node = node->GetNext();
		if(b->GetUserData() != NULL)
		{
			Shit *myActor = (Shit *)b->GetUserData();

			myActor->setPosition(ccp((b->GetPosition().x )* PTM_RATIO,b->GetPosition().y * PTM_RATIO));//设置精灵位置
			myActor->setRotation( -1 * CC_RADIANS_TO_DEGREES(b->GetAngle()) );//设置精灵旋转方向

			CCPoint location = myActor->getPosition();

			if(world->GetContactCount() != 0)
			{
				b2Body *body1 = world->GetContactList()->GetFixtureA()->GetBody();
				b2Body *body2 = world->GetContactList()->GetFixtureB()->GetBody();

				if(body1 == b || body2 == b)
				{
					world->DestroyBody(b);
					this->removeChild(myActor);

					if(getChildByTag(particleTag) == particleSystem)
						this->removeChild(particleSystem);
					
					initExplosion(location);
					this->addChild(particleSystem,0,particleTag);
				}
			}

			else
			for(unsigned int i = 0 ;i < animals->count();i++)
			{
				Animal *animal = (Animal *)animals->objectAtIndex(i);
				if(animal->boundingBox().containsPoint(myActor->getPosition()) && shits->containsObject(myActor))
				{
					animal->beAttacked(myActor->getPower());
					if(myActor->getShitType() == 1 && animal->getType() != EAGLE)   //1为降速shit
						animal->reduceSpeed();	

					if(animal->getLifeNum() <= 0.0001)
					{
						this->removeChild(animal);
						animals->removeObjectAtIndex(i);
					}

					world->DestroyBody(b);
					this->removeChild(myActor);

					if(getChildByTag(particleTag) == particleSystem)
						this->removeChildByTag(particleTag);

					initExplosion(location);
					this->addChild(particleSystem,0,particleTag);	
					break;
				}
			}
			
			
		}
	}


	CCArray *arr = player->getPigs();
	for (unsigned int j = 0 ;j < animals->count();j++)
	{
		Animal *animal = (Animal *)animals->objectAtIndex(j);
		for(unsigned int i = 0;i < arr->count();i++)
		{
			Pig *pig = (Pig *)arr->objectAtIndex(i);	
			
			if(pig->boundingBox().intersectsRect(animal->boundingBox()) && !animal->isMoveBack())
			{
				player->deletePigAtIndex(i);
				this->removeChild(pig,true);
				float t = animal->moveBack();
				animal->runAction(CCSequence::create(CCDelayTime::create(t),
					CCCallFuncN::create(this,callfuncN_selector(GameLayer::deleteAnimal)),NULL));
				break;
			}
		}		
	}
	
	if(animals->count() == 0)
		gameWin();

}

void GameLayer::addNewSpriteWithCoords( cocos2d::CCPoint point, cocos2d::CCSprite *sprite )
{
	sprite->setPosition(point);

	b2BodyDef bodyDef;//定义刚体
	bodyDef.type = b2_dynamicBody;//使刚体能够在力的作用下运行，刚体有三种：静态的、运动的、动态的
	bodyDef.active = false;
	/*body->SetActive(true);*/
	bodyDef.position.Set( point.x/PTM_RATIO , point.y/PTM_RATIO );//设置刚体的初始位置
	bodyDef.userData = sprite;

	body = world->CreateBody( &bodyDef );
	b2CircleShape dynamicBox;
	dynamicBox.m_radius = sprite->getContentSize().width * sprite->getScale() / 2 /PTM_RATIO;//设置半径
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;//绑定形状
	fixtureDef.density = 0.8f;//设置密度
	fixtureDef.friction = 0.5f;//设置摩擦
	fixtureDef.isSensor = false;
	fixtureDef.restitution = 0.3f;
	body->CreateFixture( &fixtureDef );

}

void GameLayer::createBullet(float dt)
{
	bool flag = false;
	if (player->getNumOfShit(curType) == 0)
	{
		for (int i = 0;i < numOfType;i++)
		{
			if(player->getNumOfShit(i) != 0)
			{
				curType = i;
				flag = true;
				break;
			}
		}
		if(!flag)
 			curType = 0;
			//return;
	}
	
	shit = Shit::create();
	shit->setShitType(curType);
	this->addChild(shit,player->getZOrder(),shitTag);

	addNewSpriteWithCoords(ccpAdd(player->getPosition(),ccp(player->getContentSize().width / 2,-15)),(CCSprite *)shit);
}

void GameLayer::initExplosion(CCPoint location)
{
	particleSystem = CCParticleExplosion::create();  
	//particleSystem->setTexture(CCTextureCache::sharedTextureCache()->addImage("shit2.png"));
	particleSystem->setLife(0.1f);   //粒子生命时间
	particleSystem->setLifeVar(0.5f);  //生命系统紊乱值
	particleSystem->setDuration(0.5f);//发射器时间
	//particleSystem->setAutoRemoveOnFinish(true);

	ccColor4F startColor = {0.5f,1.0f,0.5f,1.0f};
	particleSystem->setStartColor(startColor);
	ccColor4F startColorVar = {0.5f,1.0f,0.5f,1.0f};
	particleSystem->setStartColorVar(startColorVar);
	particleSystem->setPosition(location); 
}

void GameLayer::setShitType( CCObject* pSender )
{
	CCMenuItem *item = (CCMenuItem *)pSender;
	curType = item->getTag();

	shit->setShitType(curType);
}


void GameLayer::gameLose()
{
	CCScene *pScene = GameEndScene::create()->displayFailResult();
	CCDirector::sharedDirector()->replaceScene(pScene);
}

void GameLayer::gameWin()
{
	CCScene *pScene = GameEndScene::create()->displayWinResult();
	CCDirector::sharedDirector()->replaceScene(CCTransitionProgressRadialCCW::create(0.5f,pScene));
}

void GameLayer::updateShitsNum(float dt)
{
	char str[20];
	for (unsigned int i = 0 ;i < labels->count();i++)
	{
		sprintf(str," X %d",player->getNumOfShit(i));
		CCLabelTTF *label = (CCLabelTTF *)labels->objectAtIndex(i);
		label->setString(str);
	}

}

void GameLayer::deleteAnimal( CCNode *pSender )
{
	Animal *animal = (Animal *)pSender;
	animal->removeFromParentAndCleanup(true);
	animals->removeObject(animal);

	if(player->getNumOfPig() == 0)
		gameLose();

}

void GameLayer::addAnimal( cocos2d::CCNode *pSender)
{
	Animal *animal = (Animal *)pSender;
	animal->moveToPig(ccpAdd(pigLoc,ccp(-30,0)));
}

void GameLayer::loadDataFromXml()
{
	TiXmlDocument* pDoc = new TiXmlDocument( XML_FILE );
	unsigned long nLength = 0;
	char* pBuff = (char*)cocos2d::CCFileUtils::sharedFileUtils()->getFileData(cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename(XML_FILE).c_str(),"rt", &nLength );
	pDoc->LoadMemory( pBuff, nLength );

	TiXmlElement *Root = pDoc->RootElement();  //根，<Rank>
	TiXmlElement *pFirE = Root->FirstChildElement("levels"); //叶子节点
	TiXmlElement *pLevels = pFirE->FirstChildElement("level");
	
	while(pLevels != NULL)
	{
		if (pLevels->ValueStr().compare("level") == 0)
		{
			int levelNum = atoi(pLevels->Attribute("levelNum"));
			if(levelNum == SelectLevelLayer::getLevelNum())
			{
				TiXmlElement *pData = pLevels->FirstChildElement();
				while (pData != NULL)
				{
					if (!pData->ValueStr().compare("NumOfWolf"))
						numOfAnimals[0] = atoi(pData->FirstChild()->Value());
					else if(!pData->ValueStr().compare("NumOfSnake"))
						numOfAnimals[1] = atoi(pData->FirstChild()->Value());
					else if(!pData->ValueStr().compare("NumOfEagle"))
						numOfAnimals[2] = atoi(pData->FirstChild()->Value());
					
					pData = pData->NextSiblingElement();
				}

			}
			
		}

		pLevels = pLevels->NextSiblingElement();		
	}

	delete pDoc;
}




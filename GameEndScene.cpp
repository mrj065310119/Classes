#include "data.h"
#include "SelectLevelScene.h"
#include "GameEndScene.h"
#include "GameEndLayer.h"

using namespace cocos2d;

// Initialization.
bool GameEndScene::init()
{
	bool bRect = false;
	do 
	{
		CC_BREAK_IF(!CCScene::init());
		bRect = true;
	} while (0);
	return bRect;
}

// Display the win result scene.
CCScene* GameEndScene::displayWinResult()
{
	unLockNextLevel();
	do 
	{
		// Initialize winLayer, and add it to the scene.
		CCLayer* winLayer = GameEndLayer::create()->generateWinLayer();
		CC_BREAK_IF(!winLayer);
		this->addChild(winLayer);
	} while (0);
	return this;
}

// Display the fail result scene.
CCScene* GameEndScene::displayFailResult()
{
	do 
	{
		// Initialize winLayer, and add it to the scene.
		CCLayer* failLayer = GameEndLayer::create()->generateFailLayer();
		CC_BREAK_IF(!failLayer);
		this->addChild(failLayer);
	} while (0);
	return this;
}

void GameEndScene::unLockNextLevel()
{
	TiXmlDocument* pDoc = new TiXmlDocument( XML_FILE );
	unsigned long nLength = 0;
	char* pBuff = (char*)cocos2d::CCFileUtils::sharedFileUtils()->getFileData(cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename(XML_FILE).c_str(),"rt", &nLength );
	pDoc->LoadMemory( pBuff, nLength );

	TiXmlElement *Root = pDoc->RootElement();  //根，<Rank>
	TiXmlElement *pFirE = Root->FirstChildElement("unlocks"); //叶子节点
	TiXmlElement *pUnLocks = pFirE->FirstChildElement();
	bool isNextLevelUnlock = false;  //下一关是否已经解锁
	while (pUnLocks != NULL)
	{
		//寻找unlock节点
		if(!pUnLocks->ValueStr().compare("unlock"))
		{
			int num = atoi(pUnLocks->FirstChild()->Value());
			if(num == SelectLevelLayer::getLevelNum() + 1)  //若下一关已经解锁，则无需解锁
			{
				isNextLevelUnlock = true;
				break;
			}
		}
		pUnLocks = pUnLocks->NextSiblingElement();
	}
	//解锁下一关
	if(!isNextLevelUnlock && SelectLevelLayer::getLevelNum() != 26)
	{
		TiXmlElement *pNewNode = new TiXmlElement("unlock");
		char str[10];
		sprintf(str,"%d",SelectLevelLayer::getLevelNum() + 1);
		TiXmlText *pValue = new TiXmlText(str);
		pNewNode->LinkEndChild(pValue);
		pFirE->InsertEndChild(*pNewNode);       //添加解锁关卡
		pDoc->SaveFile(XML_FILE);
	}
	delete pDoc;
}

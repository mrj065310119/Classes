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

	TiXmlElement *Root = pDoc->RootElement();  //����<Rank>
	TiXmlElement *pFirE = Root->FirstChildElement("unlocks"); //Ҷ�ӽڵ�
	TiXmlElement *pUnLocks = pFirE->FirstChildElement();
	bool isNextLevelUnlock = false;  //��һ���Ƿ��Ѿ�����
	while (pUnLocks != NULL)
	{
		//Ѱ��unlock�ڵ�
		if(!pUnLocks->ValueStr().compare("unlock"))
		{
			int num = atoi(pUnLocks->FirstChild()->Value());
			if(num == SelectLevelLayer::getLevelNum() + 1)  //����һ���Ѿ����������������
			{
				isNextLevelUnlock = true;
				break;
			}
		}
		pUnLocks = pUnLocks->NextSiblingElement();
	}
	//������һ��
	if(!isNextLevelUnlock && SelectLevelLayer::getLevelNum() != 26)
	{
		TiXmlElement *pNewNode = new TiXmlElement("unlock");
		char str[10];
		sprintf(str,"%d",SelectLevelLayer::getLevelNum() + 1);
		TiXmlText *pValue = new TiXmlText(str);
		pNewNode->LinkEndChild(pValue);
		pFirE->InsertEndChild(*pNewNode);       //��ӽ����ؿ�
		pDoc->SaveFile(XML_FILE);
	}
	delete pDoc;
}

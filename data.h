#ifndef _DATA_H
#define _DATA_H
#include "tinyxml.h"
#include "tinystr.h"

#define XML_FILE "setting.xml"

//PlayerͼƬ
static const char* nameOfPlayer = "farmer.png";

//Player plist pvr.czz�ļ�
static const char* farmerPlist = "farmerAction.plist";
static const char* farmerPvrczz = "farmerAction.pvr.ccz";

//��ͣ��ťͼƬ
static const char* nameOfPauseNormal = "pauseNormal.png";
static const char* nameOfPauseSelect = "startSelect.png";

//���水ťͼƬ
static const char* nameOfRestartNormal = "restartNormal.png";
static const char* nameOfRestartSelect = "restartSelect.png";

//ѡ�ذ�ťͼƬ
static const char* nameOfSelectLevelNormal = "levelsNormal.png";
static const char* nameOfSelectLevelSelect = "levelsSelect.png";

//Ѫ��ͼƬ
static const char* nameOfLifeLine = "lifeline.png";
static const char* nameOfLife = "life.png";

//shit����
static const int numOfType = 3;

//��������
static const int numOfAnimalType = 3;

//shitͼƬ
static const char* nameOfShit[] = {"shit1.png","shit2.png","shit3.png"};

//shit����
static const float shitPower[] = {0.5f,0.4f,0.8f};// The background of fail and win scene.


// The pigs image.
static const char* pigList = "pigs.plist";
static const char* pigImageList = "pigs.pvr.ccz";
//��ͷͼƬ
static const char* nameOfArrow[2] = {"arrow1.png","arrow2.png"};


// The background of the menu scene and game playing scene.
static const char* skyImage = "sky.png";
static const char* clouds[] = {"cloudPlay.png", "cloudOption.png", "cloudHelp.png", "cloudExit.png"};
static const char* sunImage = "sun.png";
static const char* treeImage = "tree.png";
static const char* groundImage = "ground.png";
static const char* selectLevelSceneBg = "selectLevelSceneBg.png";

// The image of characters.
static const char* pigs[] = {"pig1.png"};


// The images of main menu selections.
static const char* playButton = "play.png";
static const char* optionButton = "option.png";
static const char* exitButton = "exit.png";
static const char* helpButton = "help.png";

// The background of level menu layer.
static const char* levelBg[] = {"level0.png", "level1.png", "level2.png"};

// The icon of levels.
static const char* levelItemList = "levelIcon.plist";
static const char* levelItemImageList = "levelIcon.pvr.ccz";

// The background of level menu.
static const char* menuBackground = "menuBackground.png";

// The background of game scenes.
static const char* gameBackground[] = {"level0Background.png", 
	"level1Background.png", "level2Background.png"};


// The image of buttons.
static const char* replayButton = "replay.png";
static const char* levelsButton = "levels.png";
static const char* nextButtonNormal= "nextNormal.png";
static const char* nextButtonSelect= "nextSelect.png";


// The background of fail and win scene.
static const char* failBackground = "failBackground.png";
static const char* winBackground = "winBackground.png";


#endif 
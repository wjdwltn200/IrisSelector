// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <vector>
#include <map>
#include <commdlg.h>


#define ENEMYKINDNUMBER 20
#define LOC_MINIMAPX 720
#define LOC_MINIMAPY 720
#define PI 3.141592f

#define TILE_SIZEX 32
#define TILE_SIZEY 32

#define SAMPLE_COUNTX 8
#define SAMPLE_COUNTY 6

#define TILE_MAXCOUNTX 50
#define TILE_MAXCOUNTY 50

#define MAX_SPAWN_NUMBER 30


using namespace std;

enum TITEL
{
	GAME_START_SC, EDITOR_MODE_SC, OPTION_SC, CREATERS_SC, EXIT_SC, 
};

enum TERRAIN
{
	TR_GRASS, TR_WATER, TR_EARTH, TR_CEMENT, TR_WALL = 0
};

enum OBJECT
{
	OBJ_DOG = 1, OBJ_SKELETON = 2, OBJ_SQUID = 3
};

enum BULLET_MOVE_TYPE
{
	MOVE_NUM, ONE_LINE, CENTER_CENTRIFUGAL, MOVE_CENTRIFUGAL
};

enum BULLET_IMAGE_TYPE
{
	BULLET_IMAGE_NUM, COLOR_Y, COLOR_B, COLOR_P, COLOR_G, COLOR_R
};

enum BULLET_MOVE_ACT_TYPE
{
	BULLET_MOVE_ACT_NUM, SCALE_SIZE_UP
};

enum BULLET_SHOOT_TYPE
{
	BULLET_SHOOT_NUM, ONE_SHOOT, CUFF_SHOOT, LINE_SHOOT
};

enum BULLET_BOOM_TYPE
{
	BULLET_BOOM_NUM, MOUSE_POINT, ANGLE_LINE, ANGLE_REVERSE, ANGLE_BOUNCE, ANGLE_RANDOM
};

enum BULLET_MASTER_TYPE
{
	BULLET_MASTER_NUM, PLAYER, MONSTER, OBJECT
};

// 커밋
struct tagBulletInfo // 발사되는 블렛의 설정
{

	bool tIsAlive = true;
	int tBulletSetNum = 1;

	float tScale = 0.0f;
	float tScaleMax = tScale * 5.0f;
	float tRadius = 0.0f;
	float tExpRadius = 0.0f;
	float tAngle = 0.0f;
	float tRange = 50.0f;
	float tPosX = 0.0f;
	float tPosY = 0.0f;

	float tDmage = 10.0f;
	float tKnokBack = 20.0f;
	float tMoveSpeed = 0.0f;
	float tScatter = 0.0f;
	bool tBulletBoom = 0;

	int	tBoomType = BULLET_BOOM_TYPE::ANGLE_LINE;
	int tShootType = BULLET_SHOOT_TYPE::BULLET_SHOOT_NUM;
	int tMasterType = BULLET_MASTER_TYPE::PLAYER;
	int tMoveActType = BULLET_MOVE_ACT_TYPE::BULLET_MOVE_ACT_NUM;
	int tMoveType = BULLET_MOVE_TYPE::ONE_LINE;
	int tImageType = BULLET_IMAGE_TYPE::COLOR_Y;
};


struct tagMonInfo // 몬스터 설정
{

	bool tIsAlive = true;

	RECT m_rc;
	int	tMoveType;

	float tScale = 1.0f;
	float tScaleMax = tScale * 2.0f;
	float tRadius = 0.0f;
	
	int tFireCount = 0;
	int tFireDelay = 10;
	float tFireAngle = 0.0f;
	float tMoveAngle = 0.0f;
	float tPosX = 0.0f;
	float tPosY = 0.0f;

	float tUnKnokBack;
	float tMoveSpeed = 5.0f;

	float tHp = 0.0f;
	float tHpMax = tHp;
	
	float tWidth;
	float tHeight;
	float tDef;
	int tminGaugeInfo;
	int tmaxGaugeInfo;
	float tminGaugeSub;
	float tmaxGaugeSub;
	float tDamageSub;
	bool tTrance;
	float tHealing;
	int tHealingCount;
	int tIslife;
	bool tIsBoom = true; // 체력바 분기에 따른 몬스터 상태 폭발
	///////////////////////////////////////////////////스폰 타일 타입
	bool isActive; // 이 스폰타입이 살아있는지.
	int nSpawnCycle; // 주기
	int nSpawnOfNumber; // 한번에 나오는 유닛의 수
	int nCycleDecreaseNum; // 이 생성타일 주기가 줄어드는 시간 (또는 늘어나는 시간)
	int nTimetoComplete; // 이 생성타일이 파괴되는 시간
	int nAbilityType; // 몬스터의 능력변화
};


enum ITEM_SKILL_TYPE
{
	BULLET_SPEED_UP, BULLET_POWER_UP, BULLET_RANGE_UP, BULLET_SIZE_UP, BULLET_DELAY_DOWN, BULLET_SET_MAX_UP,
	BULLET_COLOR_Y, BULLET_COLOR_B, BULLET_COLOR_P, BULLET_COLOR_G,
	BULLET_ONE_SHOOT, BULLET_SECTOR_SHOOT, BULLET_CUFF_SHOOT,
	BULLET_SCALE_SIZE_UP,
	BULLET_ONE_LINE, BULLET_CENTER_CENTRIFUGAL, BULLET_MOVE_CENTRIFUGAL,
	PLAYER_MOVE_SPEED_UP, ITEM_SKILL_NUM
};
enum MONSTER_SUB
{
	MONSTER_SPEED_UP, MONSTER_POWER_UP, MONSTER_DEF_UP, MONSTER_ATT_UP, MONSTER_HP_HEALING,
	MONSTER_BOOM, MONSTER_RESURRECTION
};
enum MONSTER_MOVE
{
	MONSTER_FLY, MONSTER_WALK, MONSTER_RUN, MONSTER_CRAWL
};

struct tagItemInfo // 아이템 정보
{
	float tScale = 0.0f;
	float tRadius = 0.0f;

	int tTimer = 0;
	int tTimerMax = 0;
	//float tMoveSpeed = 0.0f;
	float posX = 0.0f;
	float posY = 0.0f;

	int tSkillType = ITEM_SKILL_TYPE::ITEM_SKILL_NUM;
	int tImageCurrX = 0;
	int tImageCurrY = 0;
	int tItemTimerAlpha = 0;

	int tItemNumber = 0;
	int tItemGrade = 0;
	string tItemName = "";
	string tItemTxt = "";
	string tItemOption = "";

	bool tIsGet = false;

	// 아이템 옵션
	// 블렛 영향 옵션
	bool tBulletType = 0;

	int tBulletSetNum = 0;
	float tRange = 0.0f;

	float tBulletScale = 0.0f;
	float tDmage = 0.0f;
	float tKnokBack = 0.0f;
	float tMoveSpeed = 0.0f;
	int tBulletBoom = 0;

	int	tBoomType = BULLET_BOOM_TYPE::ANGLE_LINE;
	int tShootType = BULLET_SHOOT_TYPE::BULLET_SHOOT_NUM;
	int tMasterType = BULLET_MASTER_TYPE::PLAYER;
	int tMoveActType = BULLET_MOVE_ACT_TYPE::BULLET_MOVE_ACT_NUM;
	int tMoveType = BULLET_MOVE_TYPE::ONE_LINE;
	int tImageType = BULLET_IMAGE_TYPE::COLOR_Y;

	// 플레이어 영향 옵션
	float tPlayerSpeed = 0.0f;
	int tBulletDelayCountMax = 0;
	float tCrossHairScaleMax = 0.0f;
	int tPlayerHpMax = 0;
	float tPlayerScale = 0.0f;
};

struct tagTile // 그려줄 타일의 정보
{
	TERRAIN terrain;
	int terrainFrameX; // 타일이 가지고 있는 지형정보
	int terrainFrameY;
	bool isMove;
	int SampleNum;

	int MonsterNumber; // 0~18(순서대로의 아이디값) // 20(FALSE값)

	//OBJECT object; // 오브젝트는 고유의 좌표를 가지므로 다른 스트럭트를 정의한다.
	//int objectFrameX; // 타일이 가지고 있는 오브젝트정보
	//int objectFrameY;
	RECT rc;
};

struct tagSpawnTile
{
	int nSPawnCycle;
	int nSPawnNumber;
	bool bIsActive;
	int nMonsterID;

};

struct tagSampleTile
{
	RECT rc;
	int frameX;
	int frameY;
	int SampleNum;
};



typedef struct tagFloatPoint
{
	float x;
	float y;

	tagFloatPoint() { x = 0; y = 0; }
	//tagFloatPoint(float _x, float _y) { x = _x; y = _y; }
} FPOINT;


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
//파일 경로 수정
//#include <shlwapi.h> #pragma comment(lib, "shlwapi")

#define SAFE_DELETE(p)	{ if (p) delete p; p = NULL; }

#define SYNTHESIZE(varType, varName, funcName)\
protected: varType varName;\
public: varType get##funcName() { return varName; }\
public: void set##funcName(varType var) { varName = var; }


#include "txtData.h"
#include "timeManager.h"
#include "keyManager.h"
#include "imageManager.h"
#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "sceneManager.h"
#include "utils.h"
#include "MapCamera.h"
#include "Camera.h"


typedef struct tagSaveData
{
	int	selected_player_id;
	int maxHP;
	int score;
	int gTileMaxCountX;
	int gTileMaxCountY;

} SAVE_DATA;
#define  WINDOW_SCREEN	// FULL_SCREEN, WINDOW_SCREEN, MAP_TOOL

#ifdef FULL_SCREEN
	#define WINSTARTX 0
	#define WINSTARTY 0
	#define WINSIZEX GetSystemMetrics(SM_CXSCREEN)
	#define WINSIZEY GetSystemMetrics(SM_CYSCREEN)
#elif defined MAP_TOOL
	#define WINSTARTX 50
	#define WINSTARTY 50
	#define WINSIZEX 1600
	#define WINSIZEY 800
#else
	#define WINSTARTX 50
	#define WINSTARTY 50
	#define WINSIZEX 800
	#define WINSIZEY 800
#endif





#define RANDOM randomFunction::getSingleton()
#define KEYMANAGER keyManager::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define TIMEMANAGER timeManager::getSingleton()
#define TXTDATA txtData::getSingleton()
#define SCENEMANAGER sceneManager::getSingleton()
#define CAMERA Camera::getSingleton()
#define MAPCAMERA MapCamera::getSingleton()

extern HINSTANCE	g_hInstance;
extern HWND			g_hWnd;
extern HFONT		g_hFont;
extern HFONT		g_OldFont;
extern SAVE_DATA	g_saveData;
extern POINT		g_ptMouse;

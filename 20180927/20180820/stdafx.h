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

using namespace std;

enum TITEL
{
	GAME_START_SC, EDITOR_MODE_SC, COLLECTION_SC, OPTION_SC, CREATERS_SC, EXIT_SC, 
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
	ONE_LINE, CENTER_CENTRIFUGAL, MOVE_CENTRIFUGAL, MOVE_NUM
};

enum BULLET_IMAGE_TYPE
{
	COLOR_Y, COLOR_B, COLOR_P, COLOR_G, IMAGE_NUM
};

enum BULLET_MASTER_TYPE
{
	PLAYER, MONSTER, OBJECT, MASTER_NUM
};

// 커밋
struct tagBulletInfo // 발사되는 블렛의 설정
{
	float tScale = 0.0f;
	float tRadius = 0.0f;
	float tExpRadius = 0.0f;
	float tRange = 0.0f;

	float tDmage = 0.0f;
	float tKnokBack = 0.0f;
	float tMoveSpeed = 0.0f;

	int tMasterType = BULLET_MASTER_TYPE::PLAYER;
	int tMoveType = BULLET_MOVE_TYPE::ONE_LINE;
	int tImageType = BULLET_IMAGE_TYPE::COLOR_Y;
};

struct tagTile // 그려줄 타일의 정보
{
	TERRAIN terrain;
	int terrainFrameX; // 타일이 가지고 있는 지형정보
	int terrainFrameY;
	bool isMove;

	//OBJECT object; // 오브젝트는 고유의 좌표를 가지므로 다른 스트럭트를 정의한다.
	//int objectFrameX; // 타일이 가지고 있는 오브젝트정보
	//int objectFrameY;
	RECT rc;
};
struct tagSampleTile
{
	RECT rc;
	int frameX;
	int frameY;

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


#include "txtData.h"
#include "timeManager.h"
#include "keyManager.h"
#include "imageManager.h"
#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "sceneManager.h"
#include "utils.h"

typedef struct tagSaveData
{
	int	selected_player_id;
	int maxHP;
	int score;
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

#define TILE_X	20
#define TILE_Y	20
#define SAMPLE_TILE_X 20
#define SAMPLE_TILE_Y 9


#define PI 3.141592f

#define SAFE_DELETE(p)	{ if (p) delete p; p = NULL; }

#define SYNTHESIZE(varType, varName, funcName)\
protected: varType varName;\
public: varType get##funcName() { return varName; }\
public: void set##funcName(varType var) { varName = var; }

#define RANDOM randomFunction::getSingleton()
#define KEYMANAGER keyManager::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define TIMEMANAGER timeManager::getSingleton()
#define TXTDATA txtData::getSingleton()
#define SCENEMANAGER sceneManager::getSingleton()

extern HINSTANCE	g_hInstance;
extern HWND			g_hWnd;
extern SAVE_DATA	g_saveData;
extern POINT		g_ptMouse;

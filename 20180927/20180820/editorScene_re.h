#pragma once
#include "scene.h"

class button;

#define MAX_TILECOUNTX 60 // 2400 
#define MAX_TILECOUNTY 60 // 2400

#define TILE_SIZEX 40
#define TILE_SIZEY 40

#define SAMPLE_COUNTX 5
#define SAMPLE_COUNTY 9

#define CAMERA_destX 277
#define CAMERA_destY 110
#define CAMARA_WIDTH 518 
#define CAMERA_HEIGHT 684
#define CAMERA_SPEED 7

enum EDITOR_STATE
{
	STATE_SETSIZE, STATE_MAP1, STATE_MAP2, STATE_MAP3, STATE_MAP4
};

enum MOUSE_STATE
{
	MOUSE_IDLE,
	MOUSE_UP,
	MOUSE_DOWN,
	MOUSE_NUM
};

struct tagCurrentCamera
{
	RECT m_rc;
	int m_nX;
	int m_nY;
	int m_nWidth;
	int m_nHeight;
};

class editorScene_re : public scene
{
private:
	EDITOR_STATE  m_editSt;
	MOUSE_STATE  m_mouseSt;

	tagTile		  m_pTiles[MAX_TILECOUNTX * MAX_TILECOUNTY];  // 그려줄 타일의 정보 // 실제로 구성이 되는 타일의 정보
	tagSampleTile m_pSampleTiles[SAMPLE_COUNTX * SAMPLE_COUNTY]; // 오른쪽의 타일정보들
	tagCurrentCamera m_Camera;
	//tagSampleTile m_pSampleObjs[SAMPLE_OBJ_X * SAMPLE_OBJ_Y];

	//RECT		  m_rcSelectedObj;
	RECT		  m_rcSelectedTile;
	bool		  m_isSel;


	// 초기 설정 (사이즈 체크)에 필요한 변수////
	image * m_pImg_SizeBox;
	image * m_pImg_Box5;
	image*  m_pCheckSize;

	button * m_pBtn800x;
	button * m_pBtn1600x;
	button * m_pBtn2000x;
	button * m_pBtn2400x;
	button * m_pBtnSizeCheck;

	static bool m_bIsSizeCheck;
	static int m_nMapSize;
	static int m_nPreviewNum;
	int m_nTileMaxCountX;
	int m_nTileMaxCountY;


	bool m_bTempTrigger;
	bool m_bWindowPrint;
	//////////////////////////////////

	// 맵에디터에서 필요한 변수 //
	HWND	m_hBtnSave;
	HWND	m_hBtnLoad;
	HWND	m_hBtnEraser;

	button * m_pBtnLspace;
	button * m_pBtnRspace;

	image* m_pTileSet[4]; // 총 4개
	image* m_pImg_Box1;
	image* m_pImg_Box2;
	image* m_pImg_Box3;
	image* m_pImg_Box4;
	image* m_pImg_BG;
	//////////////////////

public:

	// 버튼관련 전역변수들//
	friend void Func_MapSize1(void);
	friend void Func_MapSize2(void);
	friend void Func_MapSize3(void);
	friend void Func_MapSize4(void);
	friend void Func_MapCheck(void);
	friend void SpaceFunc_left(void);
	friend void SpaceFunc_right(void);
	////////////////////////

	void SetSize();
	void init_Setting();

	void ButtonEvent(HWND hWnd, UINT iMessage, WPARAM wParam);
	void MouseEvent();
	void CameraUpdate();
	void SaveEvent();
	void LoadEvent();
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);


	editorScene_re();
	~editorScene_re();
};


#pragma once
#include "scene.h"


class image;
class button;
class uiObject;

enum BUTTONSTATE
{
	BUTTON_IDLE,
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_NUM
};


#define ID_EDIT               100
#define ID_BUTTON_CONTROL     1000
#define ID_BUTTON_OK          1001

#define TILE_X_MapCount 20 // 최소크기로 생각한다. 실제 맵에 뿌려질때의 최대 블록갯수다.
#define TILE_Y_MapCount 20

#define TILE_SIZE_Preview 40
#define TILE_SIZE_Map 40

#define SAMPLE_X 5
#define SAMPLE_Y 8

// 헷갈리기 전에 정리
// 실제 맵에 뿌릴떄는 40x40크기로 뿌린다.
// Set 미리보기에서는 40x40크기로 나타난다.


class editorScene : public scene
{
private :

	image* m_pImg_SizeBox;
	image* m_pImg_Box1;
	image* m_pImg_Box2;
	image* m_pImg_Box3;
	image* m_pImg_Box4;
	image*  m_pImg_BG;

	button * m_pBtn800x;
	button * m_pBtn1600x;
	button * m_pBtn2000x;
	button * m_pBtn2400x;
	button * m_pBtnSizeCheck;
	image * m_pImg_Box5;

	button * m_pBtnLspace;
	button * m_pBtnRspace;


	image*	m_pTileSet1;
	image*	m_pTileSet2;
	image*	m_pTileSet3;
	image*	m_pTileSet4;

	image*  m_pCheckSize;

	image*	m_pObjSet;

	int m_nTile_MaxCountX;
	int m_nTile_MaxCountY;

	//tagTile m_pTiles[TILE_X_MapCount * TILE_Y_MapCount];
	tagSampleTile m_pSampleTiles[SAMPLE_X * SAMPLE_Y];
	RECT  m_rcSelectedTile;

	POINT m_Mouse; // 마우스좌표
	BUTTONSTATE btnState;
	bool m_isSel;
	bool m_bObjPrint;
	bool m_bWindowPrint;

	HWND	m_hBtnSave;
	HWND	m_hBtnLoad;
	HWND	m_hBtnEraser;

	tagTile * m_pTiles = new tagTile[800];

	//static bool m_bIsSizeCheck;
	//static int m_nMapSize;
	static int m_nPreviewNum;

public:
	void setMapSize(int mapSize) { m_nMapSize = mapSize; }
	int getMapSize() { return m_nMapSize; }

	friend void SpaceFunc_left(void);
	friend void SpaceFunc_right(void);
	friend void Func_MapSize1(void);
	friend void Func_MapSize2(void);
	friend void Func_MapSize3(void);
	friend void Func_MapSize4(void);
	friend void Func_MapCheck(void);

	void ButtonEvent(HWND hWnd, UINT iMessage, WPARAM wParam);
	void SaveEvent();
	void LoadEvent();
	void TileSetting();



	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	editorScene();
	~editorScene();
};


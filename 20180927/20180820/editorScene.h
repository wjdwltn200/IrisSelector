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

#define TILE_X_MapCount 40 // 최소크기로 생각한다. 실제 맵에 뿌려질때의 최대 블록갯수다.
#define TILE_Y_MapCount 40

#define TILE_SIZE_Preview 40
#define TILE_SIZE_Map 20

#define SAMPLE_X 5
#define SAMPLE_Y 8

// 헷갈리기 전에 정리
// 실제 맵에 뿌릴떄는 20x20크기로 뿌린다.
// Set 미리보기에서는 40x40크기로 나타난다.


class editorScene : public scene
{
private :

	HWND	m_hBtnSave;
	HWND	m_hBtnLoad;
	HWND	m_hBtnSelectTerrain;
	HWND	m_hBtnSelectObject;
	HWND	m_hBtnEraser;

	uiObject * m_pUiPopup;

	image* m_pImg_SizeBox;
	image* m_pImg_Box1;
	image* m_pImg_Box2;
	image* m_pImg_Box3;
	image* m_pImg_Box4;
	image*  m_pImg_BG;

	button * m_pBtnLspace;
	button * m_pBtnRspace;


	image*	m_pTileSet1;
	image*	m_pTileSet2;
	image*	m_pTileSet3;
	image*	m_pTileSet4;


	image*	m_pObjSet;

	tagTile m_pTiles[TILE_X_MapCount * TILE_Y_MapCount];
	tagSampleTile m_pSampleTiles[SAMPLE_X * SAMPLE_Y];
	RECT  m_rcSelectedTile;

	POINT m_Mouse; // 마우스좌표
	BUTTONSTATE btnState;
	bool m_isSel;

	bool m_bObjPrint;
	
	int m_nMapSize;

	static int isClick_left;
	static int isClick_right;
	static int m_nPreviewNum;

public:
	void setMapSize(int mapSize) { m_nMapSize = mapSize; }
	int getMapSize() { return m_nMapSize; }

	friend void SpaceFunc_left(void);
	friend void SpaceFunc_right(void);

	void SetSize();

	void Preview();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	editorScene();
	~editorScene();
};


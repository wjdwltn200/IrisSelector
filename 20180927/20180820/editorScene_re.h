#pragma once
#include "scene.h"
#include "singletonBase.h"

class button;


#define SAMPLE_COUNTX1 8
#define SAMPLE_COUNTY1 6

#define CAMERA_destX 260
#define CAMERA_destY 105
#define CAMARA_WIDTH 518 
#define CAMERA_HEIGHT 684
#define CAMERA_SPEED 5
#define MINIMAP_destX 10
#define MINIMAP_destY 110
#define MINIMAP_WIDTH 180
#define MINIMAP_HEIGHT 180

#define MAX_TILECOUNTX 60
#define MAX_TILECOUNTY 60

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
	int m_ninitY;
	int m_ninitX;
	RECT m_rc;
	int m_nX;
	int m_nY;
	int m_nWidth;
	int m_nHeight;
};

struct tagMiniMapSite
{
	RECT m_rc;
	float m_fX;
	float m_fY;
};

struct tagMiniMap
{
	RECT m_rc;
	tagMiniMapSite m_site;
	int m_nX;
	int m_nY;
	int m_nWidth;
	int m_nHeight;
};

//struct tagFixedCamera
//{
//	RECT m_rc;
//};

class editorScene_re : public scene
{
private:
	EDITOR_STATE  m_editSt;
	MOUSE_STATE  m_mouseSt;

	tagTile		  m_pTiles[MAX_TILECOUNTX * MAX_TILECOUNTY];  // 그려줄 타일의 정보 // 실제로 구성이 되는 타일의 정보
	tagSampleTile m_pSampleTiles[SAMPLE_COUNTX1 * SAMPLE_COUNTY1]; // 오른쪽의 타일정보들
	tagCurrentCamera m_Camera;
	tagMiniMap	     m_MiniMap;
	RECT FixedCamera;
	//tagSampleTile m_pSampleObjs[SAMPLE_OBJ_X * SAMPLE_OBJ_Y];

	//RECT		  m_rcSelectedObj;
	RECT		  m_rcSelectedTile;
	int		      m_rcSelectedTileSampleNum;
	float         m_fCameraSizeRate;
	float         m_fMiniMapSiteRate_Width;
	float         m_fMiniMapSiteRate_Height;

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

	int m_nLoadMapSIze;

	bool m_bTempTrigger;
	bool m_bWindowPrint;
	//////////////////////////////////

	int m_nMouseWheelState;

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

	//init//
	void SetSize();
	void init_Setting();

	// update//
	void MouseEvent();
	void CameraUpdate();
	void ButtonEvent(HWND hWnd, UINT iMessage, WPARAM wParam);
	void SaveEvent();
	void LoadEvent();
	void WheelEvent(int num, WPARAM wParam);

	int getCameraHeight() { return m_Camera.m_nHeight; }
	int getCameraWidth() { return m_Camera.m_nWidth; }

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);


	editorScene_re();
	~editorScene_re();
};


#pragma once
#include "scene.h"

#define TILE_SIZEX 40
#define TILE_SIZEY 40

#define SAMPLE_COUNTX 5
#define SAMPLE_COUNTY 9

#define TILE_MAXCOUNTX 60
#define TILE_MAXCOUNTY 60

enum tagMOUSE_STATE
{
	aMOUSE_IDLE,
	aMOUSE_UP,
	aMOUSE_DOWN,
	aMOUSE_NUM
};

enum tagSELECTED_TILE {
	tileset1, tileset2, tileset3, tileset4
};

enum tagSELECTED_SIZE {
	x800 = 800, x1600 = 1600, x2000 = 2000, x2400 = 2400
};

class editor : public scene
{
private:
	bool m_bIsSelectSize; // 메뉴창에서 선택가능
		
	
	tagTile		  m_pTiles[MAX_TILECOUNTX * MAX_TILECOUNTY];  // 그려줄 타일의 정보 // 실제로 구성이 되는 타일의 정보
	tagSampleTile m_pSampleTiles[SAMPLE_COUNTX * SAMPLE_COUNTY]; // 오른쪽의 타일정보들
	RECT m_rcSelectedTile;
	tagSELECTED_TILE st_selTile;
	tagSELECTED_SIZE st_selSize;
	tagMOUSE_STATE st_mouse;

	image* m_pTileSet[4]; // 총 4개
	image* m_pBox;

public:

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	editor();
	~editor();
};


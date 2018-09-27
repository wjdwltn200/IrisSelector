#pragma once
#include "scene.h"

class image;

class editorScene : public scene
{
private :
	HWND	m_hBtnSave;
	HWND	m_hBtnLoad;
	HWND	m_hBtnSelectTerrain;
	HWND	m_hBtnSelectObject;
	HWND	m_hBtnEraser;

	image*  m_pBG;
	image*	m_pTileSet;
	image*	m_pObjSet;

	tagTile m_pTiles[TILE_X * TILE_Y];
	tagSampleTile m_pSampleTiles[SAMPLE_TILE_X * SAMPLE_TILE_Y];
	RECT  m_rcSelectedTile;

	POINT m_Mouse; // ¸¶¿ì½ºÁÂÇ¥

	bool m_bObjPrint;
	

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	editorScene();
	~editorScene();
};


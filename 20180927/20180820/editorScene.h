#pragma once
#include "scene.h"

class editorScene : public scene
{
private :
	HWND	m_hBtnSave;
	HWND	m_hBtnLoad;
	HWND	m_hBtnSelectTerrain;
	HWND	m_hBtnSelectObject;
	HWND	m_hBtnEraser;

	image*	m_pTileSet;
	image*	m_pObjSet;

	tagTile m_pTiles[TILE_X * TILE_Y];
	

public:
	editorScene();
	~editorScene();
};

class editorScene
{
public:
	editorScene();
	~editorScene();
};


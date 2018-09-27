#pragma once
#include "scene.h"

class editorScene : public scene
{
private :
	HWND	m_hBtnSave;
	HWND	m_hBtnLoad;
	HWND	m_hBtnSelectTerrain;
	HWND	m_hBtnSelectObject;

public:
	editorScene();
	~editorScene();
};


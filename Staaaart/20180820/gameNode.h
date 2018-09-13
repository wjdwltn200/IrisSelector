#pragma once
#include "image.h"

class gameNode
{
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	image* getBackBuffer() { return NULL; }// m_pBackBuffer; Å×½ºÆ® 

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	gameNode();
	virtual ~gameNode();
};


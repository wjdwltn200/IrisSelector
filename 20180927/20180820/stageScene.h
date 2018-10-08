#pragma once
#include "scene.h"

class button;
class image;

class stageScene : public scene
{
private:

	tagTile		  m_pTiles[MAX_TILECOUNTX * MAX_TILECOUNTY];



	button*		  m_pButton1;
	button*       m_pButton2;

	image*		  m_pImage_BG1;
	image*        m_pImage_checkBox;
	image*		  m_pTileSet[4];

	int MapSize;

	static int buttonNum;
	static int buttonOK;

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	void LoadEvent();
	void FixedLoadEvent();

	friend void Func_button1(void);
	friend void Func_button2(void);

	stageScene();
	~stageScene();
};


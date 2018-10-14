#pragma once
#include "scene.h"


class button;
class image;
class PlayerCharacter;
class progressBar;
class bulletManger;
class effectManager;
class itemManager;
class monsterManger;
class animation;

class stageScene : public scene
{
private:
	tagTile		  m_pTiles[MAX_TILECOUNTX * MAX_TILECOUNTY];

	button*		  m_pButton1;
	button*       m_pButton2;

	image*		  m_pImage_BG1;
	image*        m_pImage_checkBox;
	image*		  m_pTileSet[4];

	int MiniMap_Ratio;
	int MapSize;
	bool m_bIsMiniMapOn;

	static int buttonNum;
	static int buttonOK;

	bool m_isTest;

	// 타이틀 헤더 이동
	struct buttonSelect
	{
		RECT	m_rc;
		float	m_fX;
		float	m_fY;
		int		carrFrameX;
		int		carrFrameY;
		float	m_moveSpeed;
		bool	m_isMovement;
	};
	PlayerCharacter* m_player;
	image* m_titleScene;
	image* m_button;
	buttonSelect m_tButtonInfo;
	bulletManger * m_pBulletMag;
	bulletManger * m_pBulletMagMons;
	itemManager * m_pItemMag;
	monsterManger * m_pMonsterMag;
	effectManager * m_pEffMagr;
	progressBar* m_pProgressBar;

	int m_buttonSetX;
	int m_buttonSetY;

public:
	HRESULT init();
	void release();



	void update();
	void KeyEvent();
	void MouseEvent();



	void render(HDC hdc);
	void LoadEvent();
	void FixedLoadEvent();

	void ColRc();

	bool getTileIsMove(int x) { return m_pTiles[x].isMove; }

	friend void Func_button1(void);
	friend void Func_button2(void);

	stageScene();
	~stageScene();
};


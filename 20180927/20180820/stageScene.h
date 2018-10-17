#pragma once
#include "scene.h"
#include "stdafx.h"
#include "soundManager.h"

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
	tagTile		  m_pTiles[TILE_MAXCOUNTX * TILE_MAXCOUNTY];

	button*		  m_pButton1;
	button*       m_pButton2;

	image*		  m_pImage_BG1;
	image*        m_pImage_checkBox;
	image*		  m_pTileSet[4];



	int MiniMap_Ratio;
	int MapSizeX;
	int MapSizeY;
	int m_nTileindex;
	bool m_bIsMiniMapOn;
	bool m_bIsCulling;
	bool m_bIsCameraTextOn;

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
	tagSpawnTile m_tSpawnTile;
	
	soundManager m_soundMag;

	tagSpawnTile SpawnTile;
	tagMonInfo Moninfo;

	int m_buttonSetX;
	int m_buttonSetY;
	int m_isCount;
	int m_SpawnCount;
	int m_SpawnWorldTime;
	bool m_isMonLvUp;

public:
	HRESULT init();
	void release();



	void update();
	void KeyEvent();
	void MouseEvent();



	void render(HDC hdc);
	void LoadEvent();
	void FixedLoadEvent();
	void MonSpawnCycle(int SpawnCycle, int SpawnOfNumber, int MonNumber, int CycleDecreaseNum,
		int TimetoComplete, int AbilityType, int AbilityCycle);

	void ColRc();
	bool getTileIsMove(int x) { return m_pTiles[x].isMove; }

	friend void Func_button1(void);
	friend void Func_button2(void);

	stageScene();
	~stageScene();
};


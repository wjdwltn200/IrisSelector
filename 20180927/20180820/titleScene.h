#pragma once
#include "scene.h"

class PlayerCharacter;
class bulletManger;
class effectManager;
class itemManager;
class monster;
class titleScene : public scene
{


private:
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
	itemManager * m_pItemMag;

	effectManager * m_pEffMagr;

	int m_buttonSetX;
	int m_buttonSetY;

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	void ColRc();

public:

	titleScene();
	~titleScene();
};


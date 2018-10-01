#pragma once
#include "scene.h"
<<<<<<< HEAD
#include "bulletManger.h"
=======
class PlayerCharacter;
>>>>>>> cfc2258d5f2c1532142e467a969fd2349bd1af92

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

<<<<<<< HEAD
	bulletManger * m_pBulletMag;
=======
>>>>>>> cfc2258d5f2c1532142e467a969fd2349bd1af92

	int m_buttonSetX;
	int m_buttonSetY;

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
public:

	titleScene();
	~titleScene();
};


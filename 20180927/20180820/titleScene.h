#pragma once
#include "scene.h"
<<<<<<< HEAD

#include "bulletManger.h"
=======
#include "bulletManger.h"
#include "effectManager.h"
>>>>>>> b0058aa65c4bd430f6f1c85977b9adcf24eae3e8

class PlayerCharacter;

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
	effectManager * m_pEffMagr;

	bulletManger * m_pBulletMag;
>>>>>>> b0058aa65c4bd430f6f1c85977b9adcf24eae3e8

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


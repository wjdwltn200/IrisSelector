#pragma once
#include "scene.h"
<<<<<<< HEAD

#include "bulletManger.h"
#include "bulletManger.h"
#include "effectManager.h"
=======
>>>>>>> 33ddf23458d77127ad2cc72b858e27e61b3544fb

class PlayerCharacter;
class bulletManger;
class effectManager;

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
	bulletManger * m_pBulletMag;

>>>>>>> 33ddf23458d77127ad2cc72b858e27e61b3544fb
	effectManager * m_pEffMagr;

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


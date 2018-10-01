#pragma once
#include "scene.h"

class titleScene : public scene
{


private:
	struct buttonSelect
	{
		RECT	m_rc;
		int		m_fX;
		int		m_fY;
		int		carrFrameX;
		int		carrFrameY;
		float	m_moveSpeed;
	};

	image* img_titleScene;
	image* img_button;
	buttonSelect	m_button;

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
public:

	titleScene();
	~titleScene();
};


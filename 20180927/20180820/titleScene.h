#pragma once
#include "scene.h"

class titleScene : public scene
{


private:
	image* m_titleScene;
	image* m_button;

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


#pragma once
#include "scene.h"

class titleScene : public scene
{


private:
	image * m_titleScene;


public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
public:

	titleScene();
	~titleScene();
};


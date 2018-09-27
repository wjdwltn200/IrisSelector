#pragma once
class titleScene
{


private:
	image * TitleScene;


public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	titleScene();
	~titleScene();
};


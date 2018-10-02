#pragma once
class editorScene;
class loadingScene;
class stageScene;
class titleScene;
class editorScene_Size;


class mainGame
{
private:
	// DC
	HDC hdc;

	// ¹é¹öÆÛ
	image * m_pBackBuffer;
	void setBackBuffer();

	char m_szText[128];

	editorScene_Size * m_pEditorScene_Size;
	editorScene * m_pEditorScene;
	loadingScene * m_pLoadingScene;
	stageScene * m_pStageScene;
	titleScene * m_pTitleScene;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	mainGame();
	~mainGame();
};


#pragma once
class animation;
class PlayerCharacter
{

private:
	image * img_player;
	image * img_leftRun;
	image * img_rightRun;

	RECT m_rc;
	float m_fX = WINSIZEX / 2;
	float m_fY = WINSIZEY / 2;

	float m_pSpeed = 5.0f;

	
	float m_currHpX;
	float m_currHpY;
	float m_MaxHp;
	


public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	PlayerCharacter();
	~PlayerCharacter();
};


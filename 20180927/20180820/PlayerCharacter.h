#pragma once
class animation;
class bulletManger;

#define BULLET_FIRST_DELAY 60


class PlayerCharacter
{

private:
	image * img_player;
	image * img_left_Run;
	image * img_right_Run;

	animation * ani_right_stay;
	animation * ani_left_stay;
	animation * ani_left_Run;
	animation * ani_right_Run;

	int m_count;
	int ani_stay_Curr[4];

	bool m_Direction;
	bool m_isRunState;
	bool m_isRunStart;
	int m_RunCount = 0;

	// 정지수 시작

	int m_bulletDelayCount;
	int	m_bulletDelayCountMax;

	// 정지수 끝
	

	//enum PLAYER_RUN { LEFT_RUN, RIGHT_RUN, DEFAULT };

	RECT m_rc;
	float m_fX = WINSIZEX / 2;
	float m_fY = WINSIZEY / 2;

	float m_Speed = 1.0f;

	
	float m_currHpX;
	float m_currHpY;
	float m_MaxHp;
	
	tagBulletInfo m_tBulletInfo;

	bulletManger** m_pBulletMag;


public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void setBulletMagPointer(bulletManger** bulletP) { m_pBulletMag = bulletP; }

	PlayerCharacter();
	~PlayerCharacter();
};


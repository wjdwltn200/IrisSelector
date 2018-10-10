#pragma once
class animation;
class bulletManger;

#define BULLET_FIRST_DELAY 60
#define CROSSHAIR_MAX_SCALE 5.0f
#define CROSSHAIR_MIN_SCALE 1.0f

#define BAES_HP 10

class PlayerCharacter
{

private:
	image * img_player;
	image * img_left_Run;
	image * img_right_Run;
	image * img_CrossHair;
	image * img_HpPoint[10];

	animation * ani_right_stay;
	animation * ani_left_stay;
	animation * ani_left_Run;
	animation * ani_right_Run;
	animation * ani_CrossHair;

	int m_count;
	int ani_stay_Curr[4];

	bool m_Direction;
	bool m_isRunState;
	bool m_isRunStart;
	int m_RunCount = 0;

	// 정지수 시작

	float m_fRadius;
	float m_fSpeed;
	float m_fCrossHairScale;
	float m_fCrossHairScaleMin;
	float m_fCrossHairScaleMax;

	int m_bulletDelayCount;
	int	m_bulletDelayCountMax;


	// 정지수 끝
	
	RECT m_rc;
	float m_fX = WINSIZEX / 2;
	float m_fY = WINSIZEY / 2;
	
	int m_currHp;
	int m_currHpMax;
	bool m_isAlive;
	
	tagBulletInfo m_tBulletInfo;
	tagBulletInfo * m_tBulletInfoPoint;
	tagBulletInfo m_tBulletInfoSub;
	tagBulletInfo * m_tBulletInfoSubPoint;

	bulletManger** m_pBulletMag;


public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void setBulletMagPointer(bulletManger** bulletP) { m_pBulletMag = bulletP; }

	void getItem(int itemInfo);
	float getRadius() { return m_fRadius; }

	RECT getRect() { return m_rc; }

	float getX() { return m_fX; }
	float getY() { return m_fY; }

	void PlayerDamage(int dam);

	void MoveActKeyInput();
	

	PlayerCharacter();
	~PlayerCharacter();
};


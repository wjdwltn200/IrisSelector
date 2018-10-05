#pragma once
class image;
class animation;
class bulletManger;

class bullet
{
private:
	image * m_pImg;
	animation * m_pAni;

	RECT	m_rc;
	int		m_ScaleCount;

	float	m_fX, m_fY;
	float	m_fAngle;
	float	m_fMoveAngle;
	float	m_fAngleRadius;
	int		tMoveTypeCount;

	bool	m_isAlive;

	bulletManger * m_pBulletMag;
	tagBulletInfo m_bulletInfo;
	tagBulletInfo * m_bulletInfoSub;



public:
	HRESULT init(const char * imageName, float posX, float posY, float angle, tagBulletInfo bulletInfo, tagBulletInfo* bulletInfoSub, bulletManger* bulletMagPoint = NULL);
	void release();
	void update();
	void render(HDC hdc);

	void movement();
	void moveTypeAct(int moveType);

	bool getIsAlive() { return m_isAlive; }
	void setIsAlive(bool alive) { m_isAlive = alive; }

	bool getIsBulletBoom() { return m_bulletInfo.tBulletBoom; }

	bullet();
	~bullet();
};


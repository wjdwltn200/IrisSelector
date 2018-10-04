#pragma once
class image;
class animation;

class bullet
{
private:
	image * m_pImg;
	animation * m_pAni;

	RECT	m_rc;
	float	m_fScale;
	float	m_fRadius;
	float	m_fSpeed;
	float	m_fX, m_fY;
	float	m_fRange, m_fExpRadius;
	float	m_fDmage;
	float	m_fKnockBack;
	float	m_fAngle;

	float	m_fMoveAngle;
	float	m_fAngleRadius;


	bool	m_isAlive;

	// 스트럭쳐
	int tMoveType;
	int	tMoveTypeCount;
	int	tImageType;

public:
	HRESULT init(const char * imageName, float posX, float posY, float angle, tagBulletInfo bulletInfo);
	void release();
	void update();
	void render(HDC hdc);

	void movement();
	void moveTypeAct(int moveType);

	bool getIsAlive() { return m_isAlive; }
	void setIsAlive(bool alive) { m_isAlive = alive; }

	bullet();
	~bullet();
};


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

	bool	m_isAlive;

public:
	HRESULT init(const char * imageName, float scale, float radius,
		float speed, float posX, float posY, float range, float expRadius, float dmage, float knokBack, float angle);
	void release();
	void update();
	void render(HDC hdc);

	void movement();

	bool getIsAlive() { return m_isAlive; }
	void setIsAlive(bool alive) { m_isAlive = alive; }

	bullet();
	~bullet();
};


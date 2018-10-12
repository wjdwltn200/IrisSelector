#pragma once
class animation;
class PlayerCharacter;
class bulletManger;
class PlayerCharacter;
class progressBar;

class monster
{
private:
	int m_moveTypeNum;
	int m_lifeCount;
	image * m_monsterType;
	animation * m_monsterMove;
	PlayerCharacter * m_player;
	progressBar * m_progressBar;

	tagBulletInfo m_tBulletInfo;
	tagBulletInfo * m_tBulletInfoPoint;
	tagBulletInfo m_tBulletInfoSub;
	tagBulletInfo * m_tBulletInfoSubPoint;

	bulletManger* m_pBulletMag;
	PlayerCharacter* m_PlayerCharPoint;

	tagMonInfo m_tMonInfo;
public:
	HRESULT init(const char * strKey, tagMonInfo monInfo, bulletManger* bulletP, PlayerCharacter* playerPoint);
	void release();
	void update();
	//void Move();
	void fireAtk();
	void Damge(float dam);
	void TypeSub(float minGague, float maxGauge, int minSubInfo, int maxSubInfo, bool isTrance, int life);
	void render(HDC hdc);

	tagMonInfo getMonInfo() { return m_tMonInfo; }
	void setAlive(bool Alive) { m_tMonInfo.tIsAlive = Alive; };
	monster();
	~monster();
};


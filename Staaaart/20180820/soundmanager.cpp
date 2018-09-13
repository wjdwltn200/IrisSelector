#include "stdafx.h"
#include "soundmanager.h"


soundmanager::soundmanager()
	: m_system(NULL)
	, m_sound(NULL)
	, m_channel(NULL)
{
}


soundmanager::~soundmanager()
{
}

HRESULT soundmanager::init()
{
	// 사운드 시스템 생성
	System_Create(&m_system);

	// 채널 수 설정
	m_system->init(TOTAL_SOUND_BUFFER, FMOD_INIT_NORMAL, 0);

	// 사운드, 채널 동적할당
	m_sound = new Sound*[TOTAL_SOUND_BUFFER];
	m_channel = new Channel*[TOTAL_SOUND_BUFFER];

	memset(m_sound, 0, sizeof(Sound*) * TOTAL_SOUND_BUFFER);
	memset(m_channel, 0, sizeof(Channel*) * TOTAL_SOUND_BUFFER);

	return S_OK;
}

void soundmanager::release()
{
	m_system->release();
}

void soundmanager::updata()
{
	m_system->update();
}

void soundmanager::addSound(string soundName, bool isBGM, bool isLoop)
{
	if (isLoop)
	{
		if (isBGM)
		{
			m_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &m_sound[m_mapSounds.size()]);
		}
		else
		{
			m_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &m_sound[m_mapSounds.size()]);
		}
	}
	else
	{
		m_system->createStream(soundName.c_str(), FMOD_DEFAULT, 0, &m_sound[m_mapSounds.size()]);
	}

	m_mapSounds.insert(make_pair(soundName, &m_sound[m_mapSounds.size()]));
}

void soundmanager::play(string soundName, float volume)
{
	int index = 0;
	for (auto p : m_mapSounds)
	{
		if (p.first == soundName)
		{
			m_system->playSound(FMOD_CHANNEL_FREE, m_sound[index], false, &m_channel[index]);

			m_channel[index]->setVolume(volume);
			break;
		}
		index++;
	}
}

void soundmanager::stop(string soundName)
{
	int index = 0;
	for (auto p : m_mapSounds)
	{
		if (p.first == soundName)
		{
			m_channel[index]->stop();
			break;
		}
		index++;
	}
}

void soundmanager::pause(string soundName)
{
	int index = 0;
	for (auto p : m_mapSounds)
	{
		if (p.first == soundName)
		{
			m_channel[index]->setPaused(true);
			break;
		}
		index++;
	}
}

void soundmanager::resume(string soundName)
{
	int index = 0;
	for (auto p : m_mapSounds)
	{
		if (p.first == soundName)
		{
			m_channel[index]->setPaused(false);
			break;
		}
		index++;
	}
}

bool soundmanager::isPlaying(string soundName)
{
	bool isPlay = false;
	int index = 0;
	for (auto p : m_mapSounds)
	{
		if (p.first == soundName)
		{
			m_channel[index]->isPlaying(&isPlay);
			break;
		}
		index++;
	}

	return isPlay;
}

bool soundmanager::isPause(string soundName)
{
	bool isPause = false;
	int index = 0;
	for (auto p : m_mapSounds)
	{
		if (p.first == soundName)
		{
			m_channel[index]->getPaused(&isPause);
			break;
		}
		index++;
	}

	return isPause;
}

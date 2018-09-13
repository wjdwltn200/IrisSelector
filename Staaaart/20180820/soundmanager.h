#pragma once
#include "singletonBase.h"

#include "inc/fmod.hpp"

#pragma comment(lib, "lib/fmodex_vc.lib")

#define EXTRA_CHANNEL_BUFFER	5
#define SOUND_BUFFER			10
#define TOTAL_SOUND_BUFFER		EXTRA_CHANNEL_BUFFER + SOUND_BUFFER

using namespace FMOD;

class soundmanager : public singletonBase<soundmanager>
{
private:
	FMOD::System*	m_system;
	FMOD::Sound**	m_sound;
	FMOD::Channel**	m_channel;

	map<string, FMOD::Sound**>	m_mapSounds;
	map<string, FMOD::Sound**>::iterator	m_iterSound;

	map<string, FMOD::Channel**>	m_mapChannel;
	map<string, FMOD::Channel**>::iterator	m_iterChannel;


public:
	HRESULT init();
	void release();
	void updata();

	void addSound(string soundName, bool isBGM, bool isLoop);
	void play(string soundName, float volume = 1.0f);	// 0.0f ~ 1.0f
	void stop(string soundName);
	void pause(string soundName);
	void resume(string soundName);

	bool isPlaying(string soundName);
	bool isPause(string soundName);

	soundmanager();
	~soundmanager();
};


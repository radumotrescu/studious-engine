#include "SoundManager.h"

namespace SE
{

	FMOD::System* SoundManager::m_system = nullptr;
	std::vector<FMOD::Channel*> SoundManager::m_channels;
	std::vector<SoundManager::Sound_ptr> SoundManager::m_sounds;

	auto SoundManager::init() -> void
	{
		//gc_initialize(0);
		//m_manager = gau_manager_create();
		//m_mixer = gau_manager_mixer(m_manager);

		void *extradriverdata = 0;
		const int MAX_NUMBER_OF_CHANNELS = 32;

		FMOD::System_Create(&m_system);

		m_system->init(MAX_NUMBER_OF_CHANNELS, FMOD_INIT_NORMAL, extradriverdata);

		for (int i = 0; i < MAX_NUMBER_OF_CHANNELS; i++)
			m_channels.push_back(nullptr);
	}

	auto SoundManager::add(const Sound_ptr sound) -> void
	{
		m_sounds.push_back(sound);
	}

	auto SoundManager::get(const std::string& name)->Sound_ptr
	{
		for (Sound_ptr sound : m_sounds)
		{
			if (sound->getName() == name)
				return sound;
		}
		return nullptr;
	}

	auto SoundManager::update() -> void
	{
		m_system->update();
	}

	auto SoundManager::clean() -> void
	{
		for (const auto& sound : m_sounds)
		{
			sound->release();
		}

		for (int i = 0; i < m_channels.size(); i++)
			delete m_channels[i];

		m_system->close();
		m_system->release();
	}
}
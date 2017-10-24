#include "Sound.h"
#include "SoundManager.h"

namespace SE
{
	Sound::Sound(const std::string& name, const std::string& filepath)
		: m_name(name), m_fileName(filepath)
	{
		SoundManager::m_system->createSound(filepath.c_str(), FMOD_DEFAULT, 0, &m_sound);
	}

	Sound::~Sound()
	{
	}

	auto Sound::play() -> void
	{
		if (!m_channel)
			m_channel = searchFreeChannel();
		m_sound->setMode(FMOD_LOOP_OFF);
		SoundManager::m_system->playSound(m_sound, 0, false, &m_channel);
	}

	auto Sound::loop() -> void
	{
		if (!m_channel)
			m_channel = searchFreeChannel();
		m_sound->setMode(FMOD_LOOP_NORMAL);
		SoundManager::m_system->playSound(m_sound, 0, false, &m_channel);
	}

	auto Sound::pause() const -> void
	{
		m_channel->setPaused(true);
	}

	auto Sound::stop() const -> void
	{
		m_channel->stop();
	}

	auto Sound::getName() const -> const std::string&
	{
		return m_name;
	}

		auto Sound::getFileName() const -> const std::string&
	{
		return m_fileName;
	}

		auto Sound::release() -> void
	{
		m_sound->release();
	}

		auto Sound::searchFreeChannel() const -> FMOD::Channel*
	{

		for (const auto channel : SoundManager::m_channels)
		{
			if (channel == nullptr)
				return channel;
		}
		throw("no channels found");
	}
}
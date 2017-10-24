#pragma once

#include <vector>
#include <fmod.hpp>
#include <memory>

#include "Sound.h"

#define GAU_THREAD_POLICY_MULTI 2

class SoundManager
{
private:
	SoundManager() { }

	typedef std::shared_ptr<Sound> Sound_ptr;

	friend class Sound;

	static FMOD::System *m_system;

	static std::vector<FMOD::Channel*> m_channels;
	static std::vector<Sound_ptr> m_sounds;
public:

	//this should be called first
	static auto init() -> void;

	//adds a sound
	static auto add(Sound_ptr sound) -> void;

	//returns a sound
	static auto get(const std::string& name)->Sound_ptr;

	//this should be called at each frame
	static auto update() -> void;

	//clears all sounds
	static auto clean() -> void;
};
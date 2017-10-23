#pragma once

#include <string>
#include<fmod.hpp>

//can play, loop, pause and stop a sound
//can load mp3 and wav files
//chooses a free channel
class Sound
{
private:
	std::string m_name;
	std::string m_fileName;

	FMOD::Sound *m_sound;
	FMOD::Channel *m_channel;

public:
	Sound(const std::string& name, const std::string& filepath);
	~Sound();

	
	auto play() -> void;
	auto loop() -> void;
	auto pause() -> void;
	auto stop() -> void;


	auto getName() const -> const std::string&;
	auto getFileName() const -> const std::string&;

private:
	auto searchFreeChannel()->FMOD::Channel*;
};
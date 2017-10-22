#include "SoundManager.h"

FMOD::System* SoundManager::m_system=nullptr;
std::vector<FMOD::Channel*> SoundManager::m_channels;
std::vector<SoundManager::Sound_ptr> SoundManager::m_sounds;

auto SoundManager::init() -> void
{
	//gc_initialize(0);
	//m_manager = gau_manager_create();
	//m_mixer = gau_manager_mixer(m_manager);

	void *extradriverdata = 0;
	const int MAX_NUMBER_OF_CHANNELS=32;

	FMOD::System_Create(&m_system);
	
	m_system->init(MAX_NUMBER_OF_CHANNELS, FMOD_INIT_NORMAL, extradriverdata);

	for (int i = 0; i < MAX_NUMBER_OF_CHANNELS; i++)
		m_channels.push_back(nullptr);
}

auto SoundManager::add(Sound_ptr sound) -> void
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
	//gau_manager_update(m_manager);
	m_system->update();
}

auto SoundManager::clean() -> void
{
	//for (int i = 0; i < m_sounds.size(); ++i)
	//	delete m_sounds[i];

	//gau_manager_destroy(m_manager);
	//gc_shutdown();


	for (int i = 0; i < m_channels.size(); i++)
		delete m_channels[i];

	m_system->close();
	m_system->release();
}


/*
minutul 34:15
in window.h - include "SoundManager.h"
in destructor clean
in constructor init 
pana la 35:27
*/

/*
39:09 create a function pointer to loop
in ga_internal.h in struct ga_Handle
void(*loop)() 
ce e mai sus e de fapt gresit 
40:47
void* sound;
*/

/*
de la minutul 43:28 in 23
inainte de while(!window) dupa #include "SoundManager"
SoundManager::add(new Sound("Evacuate", "Evacuate.wav");
SoundManager::get("Evacuate")->play();

*/

/*
de la minutul 49:51
sub while(!window.closed())
{
SoundManager::update();
exact mai sus de window.update(); frames++;
*/
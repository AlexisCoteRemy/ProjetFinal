#include "SoundManager.h"

void SoundManager::load(const std::string& name, const std::string& filename)
{
    sf::SoundBuffer buffer;

    buffer.loadFromFile(filename);

    _buffers[name] = buffer;

    _sounds[name].setBuffer(_buffers[name]);
}

void SoundManager::play(const std::string& name)
{
    if (_sounds.count(name))
    {
        _sounds[name].play();
    }
}

void SoundManager::setVolume(float volume)
{
    _volume = volume;

    if (_volume < 0.f)
    {
        _volume = 0.f;
    }
        
    if (_volume > 100.f)
    {
        _volume = 100.f;
    }

    for (std::map<std::string, sf::Sound>::iterator it = _sounds.begin(); it != _sounds.end(); ++it)
    {
        it->second.setVolume(_volume);
    }
}

float SoundManager::getVolume() const
{
    return _volume;
}

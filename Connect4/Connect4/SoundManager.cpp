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
    for (std::map<std::string, sf::Sound>::iterator it = _sounds.begin(); it != _sounds.end(); ++it)
    {
        it->second.setVolume(volume);
    }
}
#include "MusicManager.h"

void MusicManager::load(const std::string& filename)
{
    _music.openFromFile(filename);
    _music.setLoop(true);
}

void MusicManager::play()
{
    _music.play();
}

void MusicManager::stop()
{
    _music.stop();
}

void MusicManager::setVolume(float volume)
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

    _music.setVolume(_volume);
}

float MusicManager::getVolume() const
{
    return _volume;
}
#pragma once

#include <SFML/Audio.hpp>
#include <map>
#include <string>

class SoundManager
{
public:
    void load(const std::string& name, const std::string& filename);

    void play(const std::string& name);

    void setVolume(float volume);

    float getVolume() const;

private:
    std::map<std::string, sf::SoundBuffer> _buffers;
    std::map<std::string, sf::Sound> _sounds;

    float _volume;
};
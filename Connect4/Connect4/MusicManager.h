#pragma once

#include <SFML/Audio.hpp>
//cleaned

class MusicManager
{
public:
    void load(const std::string& filename);
    void play();
    void stop();

    void setVolume(float volume);
    float getVolume() const;

private:
    sf::Music _music;
    float _volume = 100.f;
};
#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class Resources
{
private:
    sf::SoundBuffer *attackSound, *skillSound;
    sf::Texture *texture;
    sf::Image *image, *image2;
public:
    Resources();
    ~Resources();
    void loadAttackSound(const std::string&);
    void loadSkillSound(const std::string&);
    void loadTexture(const std::string&);
    void loadImage(const std::string&);
    sf::SoundBuffer& getAttackSound();
    sf::SoundBuffer& getSkillSound();
    sf::Texture& getTexture();
    sf::Image& getImage();
};

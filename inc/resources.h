#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class Resources
{
private:
    sf::SoundBuffer attackSound;
    sf::SoundBuffer skillSound;
    sf::Texture texture;
    sf::Image image;
    sf::Image image2;

public:
    Resources();

    void loadAttackSound(const std::string&);
    void loadSkillSound(const std::string&);
    void loadTexture(const std::string&);
    void loadImage(const std::string&);
    void loadImage2(const std::string&);
    sf::SoundBuffer& getAttackSound();
    sf::SoundBuffer& getSkillSound();
    sf::Texture& getTexture();
    sf::Image& getImage();
    sf::Image& getImage2();
};

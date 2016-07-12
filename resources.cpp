#include "inc/resources.h"

Resources::Resources()
    : attackSound(),
      skillSound(),
      texture(),
      image(),
      image2()
{

}

sf::SoundBuffer& Resources::getAttackSound()
{
    return attackSound;
}

sf::SoundBuffer& Resources::getSkillSound()
{
    return skillSound;
}

sf::Texture& Resources::getTexture()
{
    return texture;
}

sf::Image& Resources::getImage()
{
    return image;
}

sf::Image& Resources::getImage2()
{
    return image2;
}

void Resources::loadAttackSound(const std::string &path)
{
    attackSound.loadFromFile(path);
}

void Resources::loadSkillSound(const std::string &path)
{
    skillSound.loadFromFile(path);
}

void Resources::loadTexture(const std::string &path)
{
    texture.loadFromFile(path);
}

void Resources::loadImage(const std::string &path)
{
    image.loadFromFile(path);
}

void Resources::loadImage2(const std::string &path)
{
    image2.loadFromFile(path);
}

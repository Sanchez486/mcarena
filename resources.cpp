#include "inc/resources.h"

Resources::Resources()
{
    attackSound = nullptr;
    skillSound = nullptr;
    texture = nullptr;
    image = nullptr;
}

Resources::~Resources()
{
    if (attackSound!=nullptr) delete attackSound;
    if (skillSound!=nullptr) delete attackSound;
    if (texture!=nullptr) delete attackSound;
    if (image!=nullptr) delete attackSound;
}

sf::SoundBuffer& Resources::getAttackSound()
{
    return *(attackSound);
}

sf::SoundBuffer& Resources::getSkillSound()
{
    return *(skillSound);
}

sf::Texture& Resources::getTexture()
{
    return *(texture);
}

sf::Image& Resources::getImage()
{
    return *(image);
}

void Resources::loadAttackSound(const std::string &path)
{
    if (attackSound!=nullptr) delete attackSound;
    attackSound = new sf::SoundBuffer;
    attackSound->loadFromFile(path);
}

void Resources::loadSkillSound(const std::string &path)
{
    if (skillSound!=nullptr) delete skillSound;
    skillSound = new sf::SoundBuffer;
    skillSound->loadFromFile(path);
}

void Resources::loadTexture(const std::string &path)
{
    if (texture!=nullptr) delete texture;
    texture = new sf::Texture;
    texture->loadFromFile(path);
}

void Resources::loadImage(const std::string &path)
{
    if (image!=nullptr) delete image;
    image = new sf::Image;
    image->loadFromFile(path);
}

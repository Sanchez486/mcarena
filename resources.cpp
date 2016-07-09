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
    if (skillSound!=nullptr) delete skillSound;
    if (texture!=nullptr) delete texture;
    if (image!=nullptr) delete image;
    if (image2!=nullptr) delete image2;
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

sf::Image& Resources::getImage2()
{
    return *(image2);
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

void Resources::loadImage2(const std::string &path)
{
    if (image2!=nullptr) delete image2;
    image2 = new sf::Image;
    image2->loadFromFile(path);
}

#include <utility>

#include <utility>

/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Created by lgregoire,
*/

#include "Entity.hpp"

Entity::Entity(size_t r, size_t g, size_t b, size_t a)
{
    Texture texture(r, g, b, a);

    _texture = texture;
}

Entity::Entity(std::string path)
{
    Texture texture(std::move(path));

    _texture = texture;
}

Entity::Entity(text_t text)
{
    Texture texture(std::move(text));

    _texture = texture;
}

Texture Entity::getTexture()
{
    return _texture;
}

vector2_t Entity::getPosition() const {
    return _pos;
}

vector2_t Entity::getSize() const {
    return _size;
}

int Entity::getAngle()
{
    return _angle;
}

int Entity::getDepth()
{
    return _depth;
}
void Entity::setTexture(Texture texture)
{
    _texture = texture;
}

void Entity::setPosition(vector2_t pos)
{
    _pos = pos;
}

void Entity::setAngle(int angle)
{
    _angle = angle;
}

void Entity::setDepth(int depth)
{
    _depth = depth;
}

void Entity::setSize(vector2_t size)
{
    _size = size;
}





#include <utility>

/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Created by lgregoire,
*/
#include "Texture.hpp"

Texture::Texture(size_t r, size_t g, size_t b, size_t a)
{
    _color = {r, g, b, a};
}

Texture::Texture(std::string path)
{
    _path = std::move(path);
}

Texture::Texture(text_t text)
{
    _text.string = text.string;
    _color = text._color;
}

void Texture::setText(std::string str)
{
    _text.string = str;
}

void Texture::setTexture(std::string path)
{
    _path = std::move(path);
}
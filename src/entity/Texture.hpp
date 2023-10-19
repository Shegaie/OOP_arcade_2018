/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Created by lgregoire,
*/
#ifndef ARCADE_TEXTURE_HPP
#define ARCADE_TEXTURE_HPP

#include <string>

struct color_t {
    size_t r = 0;
    size_t g = 0;
    size_t b = 0;
    size_t a = 0;
};

struct text_t {
    std::string string;
    color_t _color;
};

class Texture {
    public:
        Texture() = default;
        Texture(size_t, size_t , size_t , size_t);

        explicit Texture(std::string);
        Texture(text_t text);
        ~Texture() = default;
        void setText(std::string);
        void setTexture(std::string);
        std::string _path = "";
        color_t _color = {0, 0, 0, 255};
        text_t _text = {"", (color_t){0, 0, 0, 255}};
};

#endif //ARCADE_TEXTURE_HPP

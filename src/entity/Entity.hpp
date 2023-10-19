/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Created by lgregoire,
*/

#ifndef ARCADE_ENTITY_HPP
#define ARCADE_ENTITY_HPP

#include "Texture.hpp"
#include <stddef.h>
#include <string>

struct vector2_t {
    float x;
    float y;
};

class Entity {
    public:
        Entity() = default;
        ~Entity() = default;
        Entity(size_t, size_t, size_t, size_t);
        explicit Entity(std::string path);
        explicit Entity(text_t text);

        Texture getTexture();
        vector2_t getPosition() const;
        vector2_t getSize() const;
        int getAngle();
        int getDepth();

        void setTexture(Texture texture);
        void setPosition(vector2_t);
        void setSize(vector2_t);
        void setAngle(int);
        void setDepth(int);

        std::string _menuMetaData = "";
        Texture _texture;
    protected:
    private:
        vector2_t _pos = {0, 0};
        vector2_t _size = {1, 1};
        int _angle = 0;
        int _depth = 0;
};

#endif //ARCADE_ENTITY_HPP

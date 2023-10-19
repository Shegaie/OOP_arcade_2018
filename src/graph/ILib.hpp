/*
** EPITECH PROJECT, 2022
** cpp_rush3_2018
** File description:
** Created by lgregoire,
*/
#ifndef CPP_RUSH3_2018_IGLIB_HPP
#define CPP_RUSH3_2018_IGLIB_HPP

#include "Entity.hpp"
#include <vector>
#include <map>

class ILib {
    public:
        typedef enum event {up, left, down, right, enter, escape, next_lib, prev_lib, next_game, prev_game, changeMenuModule, restart, menu, help, none} event;

        //window method
        virtual void initWindow() = 0;
        virtual void destroyWindow() = 0;
        virtual bool isWindowOpen() = 0;
        virtual void refreshWindow() = 0;

        //input method
        virtual event getEvent() = 0;

        //sprite and texture
        virtual bool getTexture(Entity entity) = 0;
        virtual void draw(Entity) = 0;
};

#endif //CPP_RUSH3_2018_IGLIB_HPP

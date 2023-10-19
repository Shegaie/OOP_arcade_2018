/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Created by lgregoire,
*/
#ifndef ARCADE_IGAME_HPP
#define ARCADE_IGAME_HPP

#include "ILib.hpp"

class IGame {
    public:
        virtual void init(std::string username) = 0;
        virtual bool refresh(ILib::event) = 0;
        virtual std::vector<Entity> getEntities() = 0;
};

#endif //ARCADE_IGAME_HPP

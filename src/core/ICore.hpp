/*
** EPITECH PROJECT, 2022
** cpp_rush3_2018
** File description:
** Created by lgregoire,
*/
#ifndef CPP_RUSH3_2018_IGRAPH_HPP
#define CPP_RUSH3_2018_IGRAPH_HPP

#include "ILib.hpp"
#include <vector>



class ICore {
    public:
        typedef enum swap {previous, next} swap;
        virtual void start(std::string libName) = 0;
        virtual void loadLib(std::string libName) = 0;
        virtual void closeLib() = 0;
        virtual void swapLib(swap way) = 0;
        virtual bool handleCoreInput(ILib::event event, bool canChangeGame) = 0;
        virtual void draw(std::vector<Entity>) = 0;

        virtual void loadGame(std::string gameName) = 0;
        virtual void closeGame() = 0;
        virtual void swapGame(swap way) = 0;
};

#endif //CPP_RUSH3_2018_IGRAPH_HPP

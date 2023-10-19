/*
** EPITECH PROJECT, 2022
** cpp_rush3_2018
** File description:
** Created by lgregoire,
*/
#ifndef CPP_RUSH3_2018_GRAPH_HPP
#define CPP_RUSH3_2018_GRAPH_HPP

#include <string>
#include <dirent.h>
#include <vector>
#include "ICore.hpp"
#include "IGame.hpp"

class Core : public ICore {
    public:
        Core();
        void getLibs();
        void getGames();
        void start(std::string libname) override;
        void loadLib(std::string libname) override;
        void closeLib() override;
        void swapLib(ICore::swap way) override;
        bool handleCoreInput(ILib::event event, bool canChangeGame) override;
        void draw(std::vector<Entity>) override;
        void loadGame(std::string gameName) override;
        void closeGame() override;
        void swapGame(swap way) override;
        void menuStart();
        void getScoresInFile(std::string fileName);
    private:
        std::string userName = "AAA";
        ILib *_lib = nullptr;
        IGame *_game = nullptr;
        std::vector<std::string> _libList;
        std::vector<std::string> _gameList;
        std::string _currLibName;
        std::string _currGameName;
        void *_handleLib;
        void *_handleGame;
        std::map<std::string, std::string> _scores;

    std::vector<Entity> setEntities();
    bool handleMenuInput(Entity &selector, ILib::event event,
        std::vector<Entity> buttonList, int &userNameModule,
        std::vector<Entity> &userNameElement
    );

    void draw_menu(const std::vector<Entity> &buttonList,
        const Entity &selector, const Entity &wallpaper,
        std::vector<Entity> userNameElement, int userNameModule
    );
};

#endif //CPP_RUSH3_2018_GRAPH_HPP

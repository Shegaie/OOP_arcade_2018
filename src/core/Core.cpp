/*
** EPITECH PROJECT, 2022
** cpp_rush3_2018
** File description:
** Created by lgregoire,
*/
#include "Core.hpp"
#include <iostream>
#include <dlfcn.h>
#include <regex>
#include <zconf.h>
#include <fstream>
#include <stdlib.h>

Core::Core()
{
    getLibs();
    getGames();
}

void Core::getGames()
{
    DIR *dir;
    struct dirent *ent;
    std::string gameso("games/");

    if ((dir = opendir ("./games/")) != nullptr) {
        while ((ent = readdir (dir)) != nullptr) {
            std::string s (ent->d_name);
            if (std::regex_match(ent->d_name, std::regex("lib_arcade_[A-Za-z0-9]+\\.so"))) {
                _gameList.push_back(gameso + ent->d_name);
                gameso = "games/";
                std::cout << "found game: " << ent->d_name << std::endl;
            }
        }
        closedir (dir);
    } else {
        perror("");
        exit(EXIT_FAILURE);
    }
}

void Core::getLibs()
{
    DIR *dir;
    struct dirent *ent;
    std::string libso("lib/");

    if ((dir = opendir ("./lib/")) != nullptr) {
        while ((ent = readdir (dir)) != nullptr) {
            std::string s (ent->d_name);
            if (std::regex_match(ent->d_name, std::regex("lib_arcade_[A-Za-z0-9]+\\.so"))) {
                _libList.push_back(libso + ent->d_name);
                libso = "lib/";
            }
        }
        closedir (dir);
    } else {
        perror("");
        exit(EXIT_FAILURE);
    }
}

void Core::start(std::string libname)
{
    ILib::event event;
    std::vector<Entity> entityList;

    loadLib(libname);
    _lib->initWindow();
    menuStart();
    while (_lib->isWindowOpen()) {
        event = _lib->getEvent();
        if (!handleCoreInput(event, true))
            continue;
        _game->refresh(event);
        entityList = _game->getEntities();
        draw(entityList);
        _lib->refreshWindow();
    }
}

void Core::loadLib(std::string libname)
{
    typedef ILib *call_t();
    std::string libname_save = libname;
    void *handle = dlopen((!libname.rfind("./", 0) ? &libname.insert(0, "./")[0] : &libname[0]), RTLD_LAZY);
    call_t *pMaker;
    void *creator;

    if(handle == nullptr)
    {
        std::cerr << "dlopen : "<< dlerror() << std::endl;
        exit(EXIT_FAILURE);
    }
    creator = dlsym(handle, "entryPoint");
    if (creator == nullptr)
    {
        std::cerr << "dlsym : " << dlerror() << std::endl;
        exit(EXIT_FAILURE);
    }
    pMaker = (call_t *)creator;
    _lib = pMaker();
    _handleLib = handle;
    _currLibName = libname_save;
}

void Core::swapLib(swap way)
{
    std::string new_lib;
    for (int i = 0; i < (int)_libList.size(); i++) {
        if (_currLibName == _libList[i] && way == ICore::next)
            new_lib = _libList[(i == (int)_libList.size() - 1 ? 0 : i + 1)];
        else if (_currLibName == _libList[i] && way == ICore::previous)
            new_lib = _libList[(i == 0 ? (int)_libList.size() - 1 : i - 1)];
    }
    _lib->destroyWindow();
    closeLib();
    loadLib(new_lib);
    _lib->initWindow();
}


void Core::closeLib()
{
    dlclose(_handleLib);
    _lib = nullptr;
}

bool Core::handleCoreInput(ILib::event event, bool canChangeGame)
{
    switch (event) {
        case ILib::escape:
            _lib->destroyWindow();
            return false;
        case ILib::next_lib:
            swapLib(ICore::next);
            break;
        case ILib::prev_lib:
            swapLib(ICore::previous);
            break;
        case ILib::next_game:
            if (canChangeGame)
                swapGame(ICore::next);
            break;
        case ILib::prev_game:
            if (canChangeGame)
                swapGame(ICore::previous);
            break;
        case ILib::restart:
            closeGame();
            loadGame(_currGameName);
        _game->init(userName);
            break;
        case ILib::menu:
            if (canChangeGame)
                menuStart();
            break;
        default :
            //std::cout << event << std::endl;
            break;
    }
    return true;
}

void Core::draw(std::vector<Entity> entityList)
{
    for (auto &entity : entityList)
        _lib->draw(entity);
}

void Core::loadGame(std::string gameName)
{
    typedef IGame *call_t();
    std::string libGame_save = gameName;
    void *handle = dlopen((!gameName.rfind("./", 0) ? &gameName.insert(0, "./")[0] : &gameName[0]), RTLD_LAZY);
    call_t *pMaker;
    void *creator;

    if(handle == nullptr)
    {
        std::cerr << "dlopen : "<< dlerror() << std::endl;
        exit(EXIT_FAILURE);
    }
    creator = dlsym(handle, "entryPoint");
    if (creator == nullptr)
    {
        std::cerr << "dlsym : " << dlerror() << std::endl;
        exit(EXIT_FAILURE);
    }
    pMaker = (call_t *)creator;
    _game = pMaker();
    _handleGame = handle;
    _currGameName = libGame_save;
}

void Core::closeGame()
{
    dlclose(_handleGame);
    _game = nullptr;
}

void Core::swapGame(ICore::swap way)
{
    std::string new_game;

    for (int i = 0; i < (int)_gameList.size(); i++) {
        if (_currGameName == _gameList[i] && way == ICore::next)
            new_game = _gameList[(i == (int)_gameList.size() - 1 ? 0 : i + 1)];
        else if (_currGameName == _gameList[i] && way == ICore::previous)
            new_game = _gameList[(i == 0 ? (int)_gameList.size() - 1 : i - 1)];
    }
    closeGame();
    loadGame(new_game);
    _game->init(userName);
}

void Core::menuStart()
{
    getScoresInFile(".score");
    ILib::event event;
    int userNameModule = -1;
    std::vector<Entity> buttonList = setEntities();
    Entity selector(0, 0, 0, 100);
    Entity wallpaper("./src/assets/menu.png");
    std::vector<Entity> userNameElement(3);

    userNameElement[0] = Entity ((text_t){"A", (color_t){255, 255, 255, 255}});
    userNameElement[0].setPosition((vector2_t){920, 540});
    userNameElement[1] = Entity ((text_t){"A", (color_t){255, 255, 255, 255}});
    userNameElement[1].setPosition((vector2_t){940, 540});
    userNameElement[2] = Entity ((text_t){"A", (color_t){255, 255, 255, 255}});
    userNameElement[2].setPosition((vector2_t){960, 540});
    selector.setPosition((vector2_t){550, 300});
    selector.setSize((vector2_t){200, 100});
    while (_lib->isWindowOpen()) {
        event = _lib->getEvent();
        if (handleMenuInput(selector, event, buttonList, userNameModule, userNameElement) || !handleCoreInput(
            event, false))
            break;
        draw_menu(buttonList, selector, wallpaper, userNameElement,
            userNameModule);
        userName = userNameElement[0].getTexture()._text.string + userNameElement[1].getTexture()._text.string + userNameElement[2].getTexture()._text.string;
        _lib->refreshWindow();
    }
}

void Core::draw_menu(const std::vector<Entity> &buttonList,
    const Entity &selector, const Entity &wallpaper,
    std::vector<Entity> userNameElement, int userNameModule
)
{
    std::vector<Entity> otherElement;

    otherElement.push_back(wallpaper);
    otherElement.emplace_back(0, 0, 0, 255);
    otherElement[1].setPosition((vector2_t){830, 480});
    otherElement[1].setSize((vector2_t){170, 100});
    otherElement.emplace_back((text_t){"Press N:", (color_t){255, 255, 255, 255}});
    otherElement[2].setPosition((vector2_t){850, 500});
    for (auto a : userNameElement)
        otherElement.push_back(a);
    draw(otherElement);


    draw(buttonList);

    otherElement.clear();
    if (userNameModule == -1)
        otherElement.push_back(selector);
    else {
        Entity underScore((text_t){"_", (color_t){255, 255, 255, 255}});
        vector2_t underScorePos = userNameElement[userNameModule].getPosition();
        underScorePos.y += 5;
        underScore.setPosition(underScorePos);
        otherElement.push_back(underScore);
    }
    draw(otherElement);
}

std::vector<Entity> Core::setEntities()
{
    std::string tmp_str;
    std::vector<Entity> entityList;
    Entity button;
    Entity text;
    Entity score;
    float y = 0;

    for (const auto &i : _libList) {
        button = Entity(0, 255, 0, 255);
        button.setPosition((vector2_t){550, 300 + y});
        button.setSize((vector2_t){200, 100});
        button._menuMetaData = i;
        tmp_str = i;
        tmp_str = tmp_str.substr(15);
        tmp_str = tmp_str.substr(0, tmp_str.size() - 3);
        text = Entity((text_t){tmp_str, (color_t){0, 0, 0, 255}});
        text.setPosition((vector2_t){550 + 75, 300 + y + 25});
        text.setSize((vector2_t){200, 100});
        entityList.push_back(button);
        entityList.push_back(text);
        y += 150;
    }
    y = 0;
    for (const auto &i : _gameList) {
        button = Entity(255, 51, 51, 255);
        button.setPosition((vector2_t){550 * 2, 300 + y});
        button.setSize((vector2_t){200, 100});
        button._menuMetaData = i;
        tmp_str = i;
        tmp_str = tmp_str.substr(17);
        tmp_str = tmp_str.substr(0, tmp_str.size() - 3);
        text = Entity((text_t){tmp_str, (color_t){0, 0, 0, 255}});
        text.setPosition((vector2_t){550 * 2 + 50, 300 + y + 25});
        text.setSize((vector2_t){200, 100});
        entityList.push_back(button);
        entityList.push_back(text);
        if (_scores.count(tmp_str)) {
            score = Entity((text_t){_scores[tmp_str], (color_t){0, 0, 30, 255}});
            score.setPosition((vector2_t){550 * 2 + 50, 300 + y + 75});
            score.setSize((vector2_t){200, 100});
            entityList.push_back(score);
        }
        y += 150;
    }
    return entityList;
}

Entity onWhichButton(vector2_t selectorPos, std::vector<Entity> buttonList)
{
    Entity tmp;

    for (Entity i : buttonList) {
        if (i.getPosition().x == selectorPos.x && i.getPosition().y == selectorPos.y) {
            tmp = i;
            return tmp;
        }
    }
    return tmp;
}

bool Core::handleMenuInput(Entity &selector, ILib::event event,
    std::vector<Entity> buttonList, int &userNameModule,
    std::vector<Entity> &userNameElement
)
{
    Entity selected;
    if (event == ILib::changeMenuModule)
        userNameModule = (userNameModule == -1 ? 0 : -1);
    if (event == ILib::enter && userNameModule != -1) {
        (userNameModule == 2 ? userNameModule = -1 : userNameModule++);
        return false;
    }
    if (event == ILib::help) {
        std::cout << "keymap" << std::endl;
    }
    ILib::event events[] = {
            ILib::right,
            ILib::left,
            ILib::up,
            ILib::down,
    };
    vector2_t positions[] = {
            {selector.getPosition().x + 550, selector.getPosition().y},
            {selector.getPosition().x - 550, selector.getPosition().y},
            {selector.getPosition().x, selector.getPosition().y - 150},
            {selector.getPosition().x, selector.getPosition().y + 150}
    };
    int i = 0;
    if (userNameModule != -1) {
        char c = userNameElement[userNameModule].getTexture()._text.string[0];
        color_t WHITE = {255, 255, 255, 255};
        if (event == ILib::up) {
            c = static_cast<char>(c + 1 > 'Z' ? 'A' : c + 1);
            userNameElement[userNameModule].setTexture(
                Texture((text_t){std::string(1, c), WHITE}));
        } else if (event == ILib::down) {
            c = static_cast<char>(c - 1 < 'A' ? 'Z' : c - 1);
            userNameElement[userNameModule].setTexture(
                Texture((text_t){std::string(1, c), WHITE}));
        } else if (event == ILib::left)
            userNameModule -= (userNameModule == 0 ? 0 : 1);
        else if (event == ILib::right)
            userNameModule += (userNameModule == 2 ? 0 : 1);
    } else {
        for (const auto &_event : events) {
            if (event == _event &&
                !onWhichButton(positions[i], buttonList)._menuMetaData.empty())
                selector.setPosition(positions[i]);
            i++;
        }
        if (event == ILib::enter) {
            selected = onWhichButton(selector.getPosition(), buttonList);
            if (!selected._menuMetaData.empty()) {
                if (strstr(&selected._menuMetaData[0], "game")) {
                    loadGame(selected._menuMetaData);
                    _game->init(userName);
                    return true;
                } else if (strstr(&selected._menuMetaData[0], "lib")) {
                    _lib->destroyWindow();
                    closeLib();
                    loadLib(selected._menuMetaData);
                    _lib->initWindow();
                }
            }
        }
    }
    return false;
}

void Core::getScoresInFile(std::string fileName)
{
    std::string line;
    std::ifstream myfile(fileName);

    if (myfile) {
        while (getline(myfile, line)) {
            std::string gameName = line.substr(0, line.find(':'));
            std::string score = line.substr(line.find(':') + 1);
            std::cout << gameName << std::endl;
            _scores[gameName] = score;
        }
        myfile.close();
    }
}
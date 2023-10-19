/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Created by lgregoire,
*/

#include <iostream>
#include "nibbler.hpp"
#include <random>
#include <chrono>
#include <thread>
#include <fstream>
#include <cstring>
#include <stdlib.h>

void nibbler::create_map(std::vector<std::string> _map, std::vector<Entity> *_grid, Entity *_head)
{
    int j = 0;
    float OFFSET_X = 20;
    float y = 20;

    for (int i = 0; i != static_cast<int>(_map.size()); i++) {
        for (int n = 0; n != _map[i].size(); n++) {
            float x = n * WALL_SIZE + OFFSET_X;
            if (_map[i][n] == '#') {
                Entity wall(0, 102, 102, 255);
                wall.setPosition((vector2_t) {x, y});
                wall.setSize((vector2_t) {WALL_SIZE, WALL_SIZE});
                (*_grid).push_back(wall);
            } else if (_map[i][n] == '$') {
                (*_head).setPosition((vector2_t) {x, y});
            }
            j++;
        }
        y += WALL_SIZE;
    }
}

static void set_map_pos_and_size(std::vector<std::string> _map, vector2_t *_map_pos, vector2_t *_map_size)
{
    float height = 0;
    float width = 0;
    (*_map_pos) = {20, 20};
    for (height = 0; height != static_cast<int>(_map.size()); height++)
        for (width = 0; width != _map[height].size(); width++);
    (*_map_size) = {width, height};
}

void nibbler::init(std::string username)
{
    std::string score = "score : ";
    std::string highscore = "high score : ";
    _username = username;
    _highscore = getHighScore(".score");
    _head = Entity("./src/game/nibbler/assets/ship_up.png");
    _head.setPosition((vector2_t){1920 / 2 - _head.getSize().x / 2, 1080 / 2 - _head.getSize().y / 2});
    _head.setSize({0.3, 0.3});
    _score = 0;
    _score_print = Entity((text_t){score.append(std::to_string(_score)), (color_t){255, 255, 255, 255}});
    _score_print.setPosition((vector2_t){1650, 100});
    _score_print.setSize((vector2_t){100, 100});
    _highscore_print = Entity((text_t){highscore.append(std::to_string(_highscore)), (color_t){255, 255, 255, 255}});
    _highscore_print.setPosition((vector2_t){1300, 100});
    _highscore_print.setSize((vector2_t){100, 100});
    _infos = Entity((text_t){"Warning: a red gum\nmeans a random tail growth!\n\nYour goal is to obtain\n20.000 pts!", (color_t){255, 255, 255, 255}});
    _infos.setPosition({1300, 200});
    _infos.setSize({200, 200});
    std::vector<std::string> map = {{"#########################"},
                                    {"#                       #"},
                                    {"#                       #"},
                                    {"#                       #"},
                                    {"#                       #"},
                                    {"#                       #"},
                                    {"#       $               #"},
                                    {"#                       #"},
                                    {"#                       #"},
                                    {"#                       #"},
                                    {"#                       #"},
                                    {"#                       #"},
                                    {"#                       #"},
                                    {"#                       #"},
                                    {"#                       #"},
                                    {"#                       #"},
                                    {"#                       #"},
                                    {"#                       #"},
                                    {"#########################"},
    };
    create_map(map, &_grid, &_head);
    set_map_pos_and_size(map, &_map_pos, &_map_size);
    _gum = Entity(0, 255, 0, 255);
    _gum.setSize({10, 10});
    std::srand(time(nullptr));
    reset_gum();
    float cruiser_size = 1.0;
    _destroyer_up = Entity("./src/game/nibbler/assets/destroyer_up.png");
    _destroyer_up.setSize({cruiser_size, cruiser_size});
    _destroyer_down = Entity("./src/game/nibbler/assets/destroyer_down.png");
    _destroyer_down.setSize({cruiser_size, cruiser_size});
    _cruiser_up = Entity("./src/game/nibbler/assets/cruiser_up.png");
    _cruiser_up.setSize({cruiser_size, cruiser_size});
    _cruiser_down = Entity("./src/game/nibbler/assets/cruiser_down.png");
    _cruiser_down.setSize({cruiser_size, cruiser_size});
}

static int randInt(int Min, int Max)
{
    return random() % (Max + 1 - Min) + Min;
}

void nibbler::reset_gum()
{
    isGumSpecial = randInt(1, 10) == 1;
    if (isGumSpecial) {
        _gum = Entity(255, 0, 0, 255);
        _gum.setSize({10, 10});
    } else {
        _gum = Entity(0, 255, 0, 255);
        _gum.setSize({10, 10});
    }
    _gum.setPosition((vector2_t){
        static_cast<float>(randInt(static_cast<int>(_map_pos.x + (WALL_SIZE * 2)), static_cast<int>(_map_pos.x + _map_size.x * WALL_SIZE - (WALL_SIZE * 2)))),
        static_cast<float>(randInt(static_cast<int>(_map_pos.y + (WALL_SIZE * 2)), static_cast<int>(_map_pos.y + _map_size.y * WALL_SIZE - (WALL_SIZE * 2))))
    });
}

void nibbler::grow_tail()
{
    ILib::event directions[] = {
            ILib::up,
            ILib::right,
            ILib::down,
            ILib::left
    };
    std::string directions_str[] = {
            "up",
            "right",
            "down",
            "left"
    };
    if (static_cast<int>(_tail.size()) > 0) {
        vector2_t vectors[] = {
                {(*(_tail.end() - 1)).entity.getPosition().x, (*(_tail.end() - 1)).entity.getPosition().y + 40},
                {(*(_tail.end() - 1)).entity.getPosition().x - 40, (*(_tail.end() - 1)).entity.getPosition().y},
                {(*(_tail.end() - 1)).entity.getPosition().x, (*(_tail.end() - 1)).entity.getPosition().y - 40},
                {(*(_tail.end() - 1)).entity.getPosition().x + 40, (*(_tail.end() - 1)).entity.getPosition().y}
        };
        int i = 0;
        for (const auto& direction: directions) {
            if (direction == (*(_tail.end() - 1)).dir) {
                std::string path = "src/game/nibbler/assets/tail_" + directions_str[i] + ".png";
                tail_part_t new_tail;
                new_tail.dir = direction;
                new_tail.entity = Entity(path);
                new_tail.entity.setSize({0.3, 0.3});
                new_tail.entity.setPosition(vectors[i]);
                _tail.push_back(new_tail);
                return;
            }
            i++;
        }
    } else {
        vector2_t vectors[] = {
                {_head.getPosition().x, _head.getPosition().y + 40},
                {_head.getPosition().x - 40, _head.getPosition().y},
                {_head.getPosition().x, _head.getPosition().y - 40},
                {_head.getPosition().x + 40, _head.getPosition().y}
        };
        int i = 0;
        for (const auto &direction: directions) {
            if (direction == _dir) {
                std::string path = "src/game/nibbler/assets/tail_" + directions_str[i] + ".png";
                tail_part_t new_tail;
                new_tail.dir = direction;
                new_tail.entity = Entity(path);
                new_tail.entity.setSize({0.3, 0.3});
                new_tail.entity.setPosition(vectors[i]);
                _tail.push_back(new_tail);
                return;
            }
            i++;
        }
    }
}

void nibbler::check_gum()
{
    vector2_t head_position = _head.getPosition();
    vector2_t gum_position = _gum.getPosition();
    vector2_t head_size = {50, 50};

    if (gum_position.x > head_position.x && gum_position.x < head_position.x + head_size.x &&
    gum_position.y > head_position.y && gum_position.y < head_position.y + head_size.y) {
        _score += 100;
        _score_print._texture._text.string = "score : " + std::to_string(_score);
        if (isGumSpecial) {
            int randomNbr = randInt(2, 4);
            for (int i = 0; i < randomNbr; i++) {
                grow_tail();
            }
        } else {
            grow_tail();
        }
        reset_gum();
    }
}

void nibbler::move_tail_part(tail_part_t *tail_part, tail_part_t *next_tail_part)
{
    int i = 0;
    ILib::event events[] = {
            ILib::up,
            ILib::right,
            ILib::down,
            ILib::left
    };
    vector2_t vectors[] = {
            {(*tail_part).entity.getPosition().x, (*tail_part).entity.getPosition().y - SHIP_SPEED},
            {(*tail_part).entity.getPosition().x + SHIP_SPEED, (*tail_part).entity.getPosition().y},
            {(*tail_part).entity.getPosition().x, (*tail_part).entity.getPosition().y + SHIP_SPEED},
            {(*tail_part).entity.getPosition().x - SHIP_SPEED, (*tail_part).entity.getPosition().y}
    };

    //---------------turn_pos-------------------
    i = 0;
    if ((*tail_part).entity.getPosition().x == (*next_tail_part).turn_pos.x && (*tail_part).entity.getPosition().y == (*next_tail_part).turn_pos.y) {
        (*tail_part).turn_pos = (*tail_part).entity.getPosition();
        std::string directions_str[] = {
                "up",
                "right",
                "down",
                "left"
        };
        for (const auto &direction: events) {
            if ((*tail_part).dir == direction) {
                i = i <= 0 ? 3 : i - 1;
                std::string path = "src/game/nibbler/assets/tail_" + directions_str[i] + ".png";
                (*tail_part).entity = Entity(path);
                (*tail_part).entity.setSize({0.3, 0.3});
                (*tail_part).dir = (*next_tail_part).dir;
                break;
            }
            i++;
        }
    }

    //----------------Mouvement-------------------
    i = 0;
    for (const auto& direction: events) {
        if ((*tail_part).dir == direction) {
            (*tail_part).entity.setPosition(vectors[i]);
        }
        i++;
    }

}

void nibbler::handle_tail()
{
    for (auto tail_part = _tail.begin(); tail_part != _tail.end(); ++tail_part) {
        int index = std::distance(_tail.begin(), tail_part);
        if (index == 0) {
            tail_part_t head;
            head.entity = _head;
            head.dir = _dir;
            head.turn_pos = _head_turn_pos;
            move_tail_part(&(*tail_part), &head);
        } else {
            move_tail_part(&(*tail_part), &_tail[index - 1]);
        }
    }
}

bool nibbler::check_fail()
{
    vector2_t head_position = _head.getPosition();
    for (const auto &i: _grid) {
        vector2_t wall_position = i.getPosition();
        vector2_t wall_size = i.getSize();
        if (head_position.x + 40 >= wall_position.x
            && head_position.x < wall_position.x + wall_size.x
            && head_position.y + 40 >= wall_position.y
            && head_position.y < wall_position.y + wall_size.y) {
            return true;
        }
    }

    for (auto i = _tail.begin(); i != _tail.end(); ++i) {
        int index = std::distance(_tail.begin(), i);
        if (index > 1) {
            vector2_t tail_position = (*i).entity.getPosition();
            vector2_t tail_size = (*i).entity.getSize();
            if (head_position.x + 40 >= tail_position.x
                && head_position.x < tail_position.x + tail_size.x
                && head_position.y + 40 >= tail_position.y
                && head_position.y < tail_position.y + tail_size.y) {
                return true;
            }
        }
    }
    return false;
}

bool nibbler::check_win()
{
    return _score > 20000;
}

void nibbler::handle_cruisers()
{
    float cruiser_speed = 1.0;
    if (_cruiser_up.getPosition().y < -1000) {
        _cruiser_up.setPosition({1300, 1500});
    }
    if (_destroyer_down.getPosition().y > 3000) {
        _destroyer_down.setPosition({1400, -2000});
    }
    _cruiser_up.setPosition({1300, _cruiser_up.getPosition().y - cruiser_speed});
    _destroyer_down.setPosition({1400, _destroyer_down.getPosition().y + cruiser_speed});
}

bool nibbler::refresh(ILib::event event)
{
    _highscore = getHighScore(".score");
    _highscore_print._texture._text.string = "high score : " + std::to_string(_highscore);
    if (_score >= _highscore)
        rewriteHighScore(".score");
    if (check_fail()) {
        //LE JOUEUR A PERDU
        _infos = Entity({"You've lost... Try again!", (color_t){255, 255, 255, 255}});
        return true;
    }
    if (check_win()) {
        //LE JOUEUR A GAGNÉ
        _infos = Entity({"You've won!", (color_t){255, 255, 255, 255}});
        return true;
    }
    ILib::event events[] = {
            ILib::up,
            ILib::right,
            ILib::down,
            ILib::left
    };
    vector2_t vectors[] = {
            {_head.getPosition().x, _head.getPosition().y - SHIP_SPEED},
            {_head.getPosition().x + SHIP_SPEED, _head.getPosition().y},
            {_head.getPosition().x, _head.getPosition().y + SHIP_SPEED},
            {_head.getPosition().x - SHIP_SPEED, _head.getPosition().y}
    };
    std::string ship_paths[] = {
            "./src/game/nibbler/assets/ship_up.png",
            "./src/game/nibbler/assets/ship_right.png",
            "./src/game/nibbler/assets/ship_down.png",
            "./src/game/nibbler/assets/ship_left.png"
    };
    float distanceX = std::abs((_head.getPosition().x) - _head_turn_pos.x);
    float distanceY = std::abs(_head.getPosition().y - _head_turn_pos.y);
    if ((distanceX > 40 || distanceY > 40) && (event == ILib::left || event == ILib::right)) {
        int next_event_idx = 0;
        switch (_dir) {
            case ILib::right:
                next_event_idx = event == ILib::right ? 2 : 0;
                break;
            case ILib::left:
                next_event_idx = event == ILib::right ? 0 : 2;
                break;
            case ILib::up:
                next_event_idx = event == ILib::right ? 1 : 3;
                break;
            case ILib::down:
                next_event_idx = event == ILib::right ? 3 : 1;
                break;
        }
        _dir = events[next_event_idx];
        _head_turn_pos = _head.getPosition();
        _head = Entity(ship_paths[next_event_idx]);
        _head.setSize({0.3, 0.3});
    }
    int i = 0;
    for (const auto &_event: events) {
        if (_dir == _event) {
            _head.setPosition(vectors[i]);
        }
        i++;
    }
    check_gum();
    handle_tail();
    handle_cruisers();
    return true;
}

std::vector<Entity> nibbler::getEntities()
{
    std::vector<Entity> entities;

    for (const auto& i:_grid)
        entities.push_back(i);
    for (const auto& i:_tail)
        entities.push_back(i.entity);
    entities.push_back(_gum);
    entities.push_back(_head);
    entities.push_back(_destroyer_down);
    entities.push_back(_cruiser_up);
    entities.push_back(_score_print);
    entities.push_back(_highscore_print);
    entities.push_back(_infos);

    return entities;
}

int nibbler::getHighScore(std::string path)
{
    std::string line;
    std::ifstream myfile(path);

    if (myfile) {
        while (getline(myfile, line)) {
            if (line.find("nibbler:") != std::string::npos) {
                line = line.substr(line.find(':') + 1);
                return (atoi(line.substr(line.find(':') + 1).c_str()));
            }
        }
        myfile.close();
    }
    return (0);
}

void nibbler::rewriteHighScore(std::string path)
{
    std::string line;
    std::ifstream myfile(path);
    std::vector<std::string> fileContent;
    int lineIndex = -1;
    int i = 0;

    if (myfile) {
        while (getline(myfile, line)) {
            if (line.find("nibbler:") != std::string::npos) {
                lineIndex = i;
            }
            i++;
            fileContent.push_back(line);
        }
        myfile.close();
    }
    if (lineIndex != -1) {
        std::string newLine = "nibbler:" + _username + ":" + std::to_string(_score) + "\n";
        fileContent[lineIndex] = newLine;
        std::fstream ofs;
        ofs.open(path, std::ios::out | std::ios::trunc);
        for (const auto &a: fileContent)
            ofs << a;
        ofs.close();
    }
}

extern "C" {
nibbler *entryPoint()
{
    return new nibbler();
}
}

/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Created by lgregoire,
*/
#ifndef ARCADE_PACMAN_HPP
#define ARCADE_PACMAN_HPP

#include "IGame.hpp"
#include <ctime>

#define OFFSET_X 100
#define OFFSET_Y 25
#define WALL_SIZE 40
#define POINT_SIZE 6
#define PAD 0.5
#define PAC_SIZE 30

class pacman : public IGame
{
public:
    void init(std::string username) override;
    bool refresh(ILib::event event) override;
    std::vector<Entity> getEntities() override;
    void check_balls();
    void create_map(std::vector<std::string> _map);
private:
    Entity _pacman;
    Entity _pacman_up;
    Entity _pacman_down;
    Entity _pacman_left;
    Entity _score_print;
    Entity _highscore_print;
    Entity _win;
    ILib::event _dir;
    ILib::event _dir_ghost;
    std::vector<Entity> _ghosts;
    std::vector<Entity> _walls;
    std::vector<Entity> _balls;
    std::vector<Entity> _superballs;
    std::vector<Entity> _tp;
    std::clock_t _timer;
    std::string _username;
    int _highscore;
    int _score;
    int _isstrong;
    int _pac_dir;

    void set_pac_pos(vector2_t);
    void move_ghosts();
    void rewriteHighScore(std::string path);
    int getHighScore(std::string path);
};

#endif //ARCADE_PACMAN_HPP

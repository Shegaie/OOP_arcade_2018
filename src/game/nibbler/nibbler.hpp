 /*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Created by lgregoire,
*/

#ifndef ARCADE_NIBBLER_HPP
#define ARCADE_NIBBLER_HPP

#include "IGame.hpp"
#include <chrono>

typedef struct tail_part_s {
    Entity entity;
    ILib::event dir;
    vector2_t turn_pos;
} tail_part_t;
class nibbler : public IGame {
public:
    void init(std::string username) override;
    bool refresh(ILib::event event) override;
    std::vector<Entity> getEntities() override;
private:
    std::vector<tail_part_t> _tail;
    void create_map(std::vector<std::string> _map, std::vector<Entity> *_grid, Entity *_head);
    void check_gum();
    void reset_gum();
    void grow_tail();
    void handle_tail();
    void handle_cruisers();
    void move_tail_part(tail_part_t *tail_part, tail_part_t *next_tail_part);
    bool check_fail();
    bool check_win();
    void rewriteHighScore(std::string path);
    bool isGumSpecial = false;
    float SHIP_SPEED = 2 ;
    vector2_t _map_pos;
    vector2_t _map_size;
    Entity _gum;
    Entity _head;
    vector2_t _head_turn_pos;
    float WALL_SIZE = 49;
    Entity _score_print;
    Entity _highscore_print;
    ILib::event _dir = ILib::up;
    int _score;
    std::vector<Entity> _grid;
    Entity _destroyer_up;
    Entity _destroyer_down;
    Entity _cruiser_up;
    Entity _cruiser_down;
    Entity _infos;
    int _highscore;
    std::string _username;

    int getHighScore(std::string path);
};

#endif //ARCADE_NIBBLER_HPP


/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Created by lgregoire,
*/

#include <iostream>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>
#include <fstream>
#include "pacman.hpp"

void pacman::create_map(std::vector<std::string> _map)
{
    int j = 0;
    float y = OFFSET_Y;

    for (int i = 0; i != 24; i++) {
		for (int n = 0; n != 29; n++) {
            float x = n * WALL_SIZE + OFFSET_X;
            if (_map[i][n] == '#') {
                Entity wall(0, 102, 205, 255);
                wall.setPosition((vector2_t){x, y});
                wall.setSize((vector2_t){WALL_SIZE, WALL_SIZE});
                _walls.push_back(wall);
            }
            else if (_map[i][n] == '.') {
                Entity ball(255, 255, 255, 255);
                ball.setPosition((vector2_t){x + 15, y + 15});
                ball.setSize((vector2_t){POINT_SIZE, POINT_SIZE});
                _balls.push_back(ball);
            }
            else if (_map[i][n] == 'P') {
                Entity superballs(255, 0, 102, 255);
                superballs.setPosition((vector2_t){x + 15, y + 15});
                superballs.setSize((vector2_t){POINT_SIZE, POINT_SIZE});
                _superballs.push_back(superballs);
            }
            else if (_map[i][n] == 'X') {
                Entity wall(0, 0, 0, 0);
                wall.setPosition((vector2_t){x + 15, y + 15});
                wall.setSize((vector2_t){WALL_SIZE, WALL_SIZE});
                _tp.push_back(wall);
            }
            else if (_map[i][n] == 'G') {
                Entity ghost("./src/game/pacman/assets/ghost_red.png");
                ghost.setPosition((vector2_t){x + 15, y + 15});
                ghost.setSize((vector2_t){2, 2});
                _ghosts.push_back(ghost);
            }
            else if (_map[i][n] == '$') {
                _pacman.setPosition((vector2_t){x, y});
                _pacman_up.setPosition((vector2_t){x, y});
            }
            j++;
		}
		y += WALL_SIZE;
	}
}

void pacman::init(std::string username)
{
    _timer = std::clock();
    std::string score = "score : ";
    std::string highscore = "high score : ";
    _username = username;
    _pacman = Entity("./src/game/pacman/assets/pacman.png");
    _pacman.setSize((vector2_t){0.6, 0.6});
    _pacman_up = Entity("./src/game/pacman/assets/pacman_up.png");
    _pacman_up.setSize((vector2_t){0.6, 0.6});
    _pacman_down = Entity("./src/game/pacman/assets/pacman_down.png");
    _pacman_down.setSize((vector2_t){0.6, 0.6});
    _pacman_left = Entity("./src/game/pacman/assets/pacman_left.png");
    _pacman_left.setSize((vector2_t){0.6, 0.6});
    _score = 0;
    _score_print = Entity((text_t){score.append(std::to_string(_score)), (color_t){255, 255, 255, 255}});
    _score_print.setPosition((vector2_t){1650, 100});
    _score_print.setSize((vector2_t){100, 100});
    _highscore_print = Entity((text_t){score.append(std::to_string(_highscore)), (color_t){255, 255, 255, 255}});
    _highscore_print.setPosition((vector2_t){1300, 100});
    _highscore_print.setSize((vector2_t){100, 100});
    _win = Entity((text_t){score.append("    You Win !"), (color_t){255, 255, 255, 255}});
    _win.setPosition((vector2_t){500, 500});
    _win.setSize((vector2_t){500, 500});
    std::vector<std::string> map =
           {{"############################"},
            {"#............##............#"},
            {"#.####.#####.##.#####.####.#"},
            {"#P####.#####.##.#####.####P#"},
            {"#..........................#"},
            {"#.####.##.########.##.####.#"},
            {"#......##....##....##......#"},
            {"######.##### ## #####.######"},
            {"     #.##          ##.#     "},
            {"     #.## ###--### ##.#     "},
            {"######.## # HHHH # ##.######"},
            {"X     .   # HHGH #   .     X"},
            {"######.## # HHHH # ##.######"},
            {"     #.## ######## ##.#     "},
            {"     #.##    $     ##.#     "},
            {"######.## ######## ##.######"},
            {"#............##............#"},
            {"#.####.#####.##.#####.####.#"},
            {"#P..##................##..P#"},
            {"###.##.##.########.##.##.###"},
            {"#......##....##....##......#"},
            {"#.##########.##.##########.#"},
            {"#..........................#"},
            {"############################"}
            };
    create_map(map);
}

void pacman::set_pac_pos(vector2_t vector)
{
    _pacman.setPosition(vector);
    _pacman_up.setPosition(vector);
    _pacman_left.setPosition(vector);
    _pacman_down.setPosition(vector);
}

static bool check_cols(vector2_t vector, std::vector<Entity> _walls)
{

    for (Entity i:_walls)
        if (vector.x + (PAC_SIZE - PAD) >= i.getPosition().x
            && vector.x < i.getPosition().x + i.getSize().x
            && vector.y + (PAC_SIZE - PAD) >= i.getPosition().y
            && vector.y < i.getPosition().y + i.getSize().y)
                return false;
    return true;
}

int check_cols_balls(std::vector<Entity> *_balls, Entity _pacman, int _score)
{
    int n = 0;

    for (Entity i:(*_balls)) {
        if (_pacman.getPosition().x + (PAC_SIZE - PAD) >= i.getPosition().x
            && _pacman.getPosition().x < i.getPosition().x + i.getSize().x
            && _pacman.getPosition().y + (PAC_SIZE - PAD) >= i.getPosition().y
            && _pacman.getPosition().y < i.getPosition().y + i.getSize().y) {
                (*_balls).erase((*_balls).begin() + n);
                _score += 10;
            }
        n++;
    }
    return (_score);
}

void pacman::check_balls()
{
    std::string score = "score : ";
    _score = check_cols_balls(&_balls, _pacman, _score);
    _score_print._texture._text.string = score.append(std::to_string(_score));
    _isstrong = check_cols_balls(&_superballs, _pacman, _isstrong);
    if (!check_cols(_pacman.getPosition(), _tp) && _pacman.getPosition().x > 1000)
        set_pac_pos((vector2_t){160, 470});
    if (!check_cols(_pacman.getPosition(), _tp) && _pacman.getPosition().x < 1000)
         set_pac_pos((vector2_t){1140, 470});
}

void pacman::move_ghosts()
{
    int i = 0;
    ILib::event events[] = {
            ILib::right,
            ILib::left,
            ILib::down,
            ILib::up
    };
    vector2_t vectors[] = {
            {_ghosts[0].getPosition().x + 40, _ghosts[0].getPosition().y},
            {_ghosts[0].getPosition().x - 40, _ghosts[0].getPosition().y},
            {_ghosts[0].getPosition().x, _ghosts[0].getPosition().y + 40},
            {_ghosts[0].getPosition().x, _ghosts[0].getPosition().y - 40}
    };
    int r = std::rand() % 4;
    for (const ILib::event &_event : events) {
        if (events[r] == _event && check_cols(vectors[i], _walls)) {
            _ghosts[0].setPosition(vectors[i]);
            _dir_ghost = events[r];
        }
        if (_dir_ghost == _event && check_cols(vectors[i], _walls))
            _ghosts[0].setPosition(vectors[i]);
        i++;
    }
}

bool pacman::refresh(ILib::event event)
{
    int i = 0;
    _highscore = getHighScore(".score");
    _highscore_print._texture._text.string = "high score : " + std::to_string(_highscore);
    if (_score >= _highscore)
        rewriteHighScore(".score");
    ILib::event events[] = {
            ILib::right,
            ILib::left,
            ILib::down,
            ILib::up
    };
    vector2_t vectors[] = {
            {static_cast<float>(_pacman.getPosition().x + PAD), _pacman.getPosition().y},
            {static_cast<float>(_pacman.getPosition().x - PAD), _pacman.getPosition().y},
            {_pacman.getPosition().x,
                static_cast<float>(_pacman.getPosition().y + PAD)},
            {_pacman.getPosition().x,
                static_cast<float>(_pacman.getPosition().y - PAD)}
    };
    for (const ILib::event &_event : events) {
        if (event == _event && check_cols(vectors[i], _walls)) {
            set_pac_pos(vectors[i]);
            _dir = event;
        }
        if (_dir == _event && check_cols(vectors[i], _walls))
            set_pac_pos(vectors[i]);
        i++;
    }
    check_balls();
    if (std::clock() > _timer) {
        move_ghosts();
        _timer += 400000;
    }
    if (_balls.empty()) {
        std::this_thread::sleep_for (std::chrono::seconds(1));
        init(_username);
    }
    return true;
}


std::vector<Entity> pacman::getEntities()
{
    std::vector<Entity> entities;

    for (auto i:_walls)
        entities.push_back(i);
    for (auto i:_balls)
        entities.push_back(i);
    for (auto i:_superballs)
        entities.push_back(i);
    for (auto i:_tp)
        entities.push_back(i);
    for (auto i:_ghosts)
        entities.push_back(i);
    entities.push_back(_score_print);
    entities.push_back(_highscore_print);
    if (_dir == ILib::right)
        entities.push_back(_pacman);
    else if (_dir == ILib::up)
        entities.push_back(_pacman_up);
    else if (_dir == ILib::down)
        entities.push_back(_pacman_down);
    else if (_dir == ILib::left)
        entities.push_back(_pacman_left);
    if (_balls.size() == 1)
        entities.push_back(_win);
    return entities;
}

int pacman::getHighScore(std::string path)
{
    std::string line;
    std::ifstream myfile(path);

    if (myfile) {
        while (getline(myfile, line)) {
            if (line.find("pacman:") != std::string::npos) {
                line = line.substr(line.find(':') + 1);
                return (atoi(line.substr(line.find(':') + 1).c_str()));
            }
        }
        myfile.close();
    }
    return (0);
}

void pacman::rewriteHighScore(std::string path)
{
    std::string line;
    std::ifstream myfile(path);
    std::vector<std::string> fileContent;
    int lineIndex = -1;
    int i = 0;

    if (myfile) {
        while (getline(myfile, line)) {
            if (line.find("pacman:") != std::string::npos) {
                lineIndex = i;
            }
            i++;
            fileContent.push_back(line);
        }
        myfile.close();
    }
    if (lineIndex != -1) {
        std::string newLine = "pacman:" + _username + ":" + std::to_string(_score) + "\n";
        fileContent[lineIndex] = newLine;
        std::fstream ofs;
        ofs.open(path, std::ios::out | std::ios::trunc);
        for (const auto &a: fileContent)
            ofs << a << std::endl;
        ofs.close();
    }
}

extern "C" {
pacman *entryPoint()
{
    return new pacman();
}
}

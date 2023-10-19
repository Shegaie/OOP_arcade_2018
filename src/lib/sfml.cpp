/*
** EPITECH PROJECT, 2022
** cpp_rush3_2018
** File description:
** Created by lgregoire,
*/

#include <dirent.h>
#include <cstring>
#include <regex>
#include "sfml.hpp"

void sfml::initWindow()
{
    _window.create(sf::VideoMode(1920, 1080), "Arcade (SFML)");
    _font.loadFromFile("./src/assets/ARCADE_R.TTF");
}

bool sfml::isWindowOpen()
{
	return _window.isOpen();
}

void sfml::destroyWindow()
{
	_window.close();
}

ILib::event sfml::getEvent()
{
    sf::Event event{};
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            return (escape);
        } else if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::L)
                return (next_lib);
            else if (event.key.code == sf::Keyboard::K)
                return (prev_lib);
            else if (event.key.code == sf::Keyboard::I)
                return (prev_game);
            else if (event.key.code == sf::Keyboard::O)
                return (next_game);
            else if (event.key.code == sf::Keyboard::N)
                return (changeMenuModule);
            else if (event.key.code == sf::Keyboard::R)
                return (restart);
            else if (event.key.code == sf::Keyboard::H)
                return (help);
            else if (event.key.code == sf::Keyboard::P)
                return (menu);
        }
        else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape)
                return (escape);
            else if (event.key.code == sf::Keyboard::Up)
                return (up);
            else if (event.key.code == sf::Keyboard::Left)
                return (left);
            else if (event.key.code == sf::Keyboard::Down)
                return (down);
            else if (event.key.code == sf::Keyboard::Right)
                return (right);
            else if (event.key.code == sf::Keyboard::Enter)
                return (enter);
        }
    }
    return (none);
}

void sfml::draw(Entity entity)
{
    if (getTexture(entity)) {
        sf::Sprite sprite;
        sf::Texture texture;
        sprite.setTexture(textureMap[entity.getTexture()._path]);
        sprite.setScale(entity.getSize().x, entity.getSize().y);
        sprite.setPosition(entity.getPosition().x, entity.getPosition().y);
        _window.draw(sprite);
    } else if (!entity.getTexture()._text.string.empty()) {
        sf::Text text;
        color_t entity_color = entity.getTexture()._color;
        sf::Color textColor = {
                static_cast<sf::Uint8>(entity_color.r),
                static_cast<sf::Uint8>(entity_color.g),
                static_cast<sf::Uint8>(entity_color.b),
                static_cast<sf::Uint8>(entity_color.a)
        };
        text.setFont(_font);
        text.setString(entity.getTexture()._text.string);
        text.setPosition(entity.getPosition().x, entity.getPosition().y);
        text.setCharacterSize(16);
        text.setFillColor(textColor);
        _window.draw(text);
    } else {
        sf::RectangleShape rect;
        rect.setSize(sf::Vector2f(entity.getSize().x, entity.getSize().y));
        rect.setFillColor(sf::Color(
            static_cast<sf::Uint8>(entity.getTexture()._color.r),
            static_cast<sf::Uint8>(entity.getTexture()._color.g),
            static_cast<sf::Uint8>(entity.getTexture()._color.b),
            static_cast<sf::Uint8>(entity.getTexture()._color.a)
        ));
        rect.setPosition(entity.getPosition().x, entity.getPosition().y);
        _window.draw(rect);
    }
}

void sfml::refreshWindow()
{
    _window.display();
    _window.clear(sf::Color::Black);
}

bool sfml::getTexture(Entity entity)
{
    sf::Texture texture;

    if (!entity.getTexture()._path.empty()) {
        if (textureMap.find(entity.getTexture()._path) == textureMap.end()) {
            texture.loadFromFile(entity.getTexture()._path);
            textureMap[entity.getTexture()._path] = texture;
        }
        return true;
    }
    return false;
}

extern "C" {
sfml *entryPoint()
{
    return new sfml();
}
}
/*
** EPITECH PROJECT, 2019
** OOP_arcade_2018
** File description:
** sdl
*/

#include <iostream>
#include "sdl.hpp"

void sdl::initWindow()
{
	SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    SDL_CreateWindowAndRenderer(1920, 1080, 0, &_window, &_renderer);
    SDL_SetWindowTitle(_window, "Arcade (SDL)");
    SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);
    TTF_Init();
    _font = TTF_OpenFont("./src/assets/ARCADE_R.TTF", 16);
	_isOpen = true;
}

bool sdl::isWindowOpen()
{
	return _isOpen;
}

void sdl::destroyWindow()
{
	_isOpen = false;
	SDL_DestroyWindow(_window);
    SDL_Quit();
}

ILib::event sdl::getEvent()
{
    SDL_Event event;
    const SDL_Keycode keys[] = {
            SDLK_ESCAPE,
            SDLK_UP,
            SDLK_LEFT,
            SDLK_DOWN,
            SDLK_RIGHT
    };
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return (escape);
        } else if (event.type == SDL_KEYUP ) {
            if (event.key.keysym.scancode == SDL_SCANCODE_L)
                return (next_lib);
            if (event.key.keysym.scancode == SDL_SCANCODE_K)
                return (prev_lib);
            if (event.key.keysym.scancode == SDL_SCANCODE_O)
                return (next_game);
            if (event.key.keysym.scancode == SDL_SCANCODE_I)
                return (prev_game);
            if (event.key.keysym.scancode == SDL_SCANCODE_N)
                return (changeMenuModule);
            if (event.key.keysym.scancode == SDL_SCANCODE_R)
                return (restart);
            if (event.key.keysym.scancode == SDL_SCANCODE_P)
                return (menu);
            if (event.key.keysym.scancode == SDL_SCANCODE_H)
                return (help);
            if (event.key.keysym.scancode == SDL_SCANCODE_RETURN)
                return (enter);
        } else if (event.type == SDL_KEYDOWN) {
            const ILib::event keycodes[] = {
                    escape,
                    up,
                    left,
                    down,
                    right
            };
            int i = 0;
            for (const SDL_Keycode &key : keys) {
                if (event.key.keysym.sym == key)
                    return (keycodes[i]);
                i++;
            }
        }
    }
    return (none);
}

void sdl::draw(Entity entity)
{
    if (getTexture(entity)) {
        SDL_Surface *surface = textureMap[entity.getTexture()._path];
        SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, surface);
        SDL_Rect dest = {static_cast<int>(entity.getPosition().x), static_cast<int>(entity.getPosition().y),
                         static_cast<int>(surface->w * entity.getSize().x),
                         static_cast<int>(surface->h * entity.getSize().y)};
        SDL_RenderCopy(_renderer, texture, nullptr, &dest);
    } else if (!entity.getTexture()._text.string.empty()) {
        color_t entity_color = entity.getTexture()._color;
        SDL_Color textColor = {
                static_cast<Uint8>(entity_color.r),
                static_cast<Uint8>(entity_color.g),
                static_cast<Uint8>(entity_color.b),
                static_cast<Uint8>(entity_color.a)
        };
        SDL_Surface* textSurface = TTF_RenderText_Solid(_font, entity.getTexture()._text.string.c_str(), textColor);
        SDL_Texture* text = SDL_CreateTextureFromSurface(_renderer, textSurface);
        SDL_Rect dest = {static_cast<int>(entity.getPosition().x), static_cast<int>(entity.getPosition().y), textSurface->w, textSurface->h};
        SDL_RenderCopy(_renderer, text, nullptr, &dest);
    } else {
        SDL_SetRenderDrawColor(_renderer,
                               static_cast<Uint8>(entity.getTexture()._color.r),
                               static_cast<Uint8>(entity.getTexture()._color.g),
                               static_cast<Uint8>(entity.getTexture()._color.b),
                               static_cast<Uint8>(entity.getTexture()._color.a));
        SDL_Rect dest = {static_cast<int>(entity.getPosition().x), static_cast<int>(entity.getPosition().y), static_cast<int>(entity.getSize().x), static_cast<int>(entity.getSize().y)};
        SDL_RenderFillRect(_renderer, &dest);
        SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
    }
}

void sdl::refreshWindow()
{
    SDL_RenderPresent(_renderer);
    SDL_RenderClear(_renderer);
}

bool sdl::getTexture(Entity entity)
{
    SDL_Surface *surface;
    if (!entity.getTexture()._path.empty()) {
        if (textureMap.find(entity.getTexture()._path) == textureMap.end()) {
            surface = IMG_Load(entity.getTexture()._path.c_str());
            textureMap[entity.getTexture()._path] = surface;
        }
        return true;
    }
    return false;
}

extern "C" {
sdl *entryPoint()
{
    return new sdl();
}
}
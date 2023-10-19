/*
** EPITECH PROJECT, 2022
** cpp_rush3_2018
** File description:
** Created by lgregoire,
*/

#ifndef CPP_RUSH3_2018_FOO_HPP
#define CPP_RUSH3_2018_FOO_HPP

#include "ILib.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <vector>

class sdl : public ILib {
    public:
		void initWindow() override;
		bool isWindowOpen() override;
		void destroyWindow() override;
        void refreshWindow() override;
    	event getEvent() override;
		void draw(Entity) override;
		bool getTexture(Entity entity) override;

	private:
		bool _isOpen;
		SDL_Window *_window;
		SDL_Renderer *_renderer;
		TTF_Font* _font;
		std::map<std::string, SDL_Surface *> textureMap;
};

#endif //CPP_RUSH3_2018_FOO_HPP

/*
** EPITECH PROJECT, 2019
** OOP_arcade_2018
** File description:
** caca
*/

#ifndef CACA_HPP_
    #define CACA_HPP_

#include "ILib.hpp"
#include "caca.h"
#include <string.h>
#include <stdlib.h>
#include <Imlib2.h>

struct image
{
    char *pixels;
    unsigned int w, h;
    struct caca_dither *dither;
};

class caca : public ILib
{
public:
		void initWindow() override;
		bool isWindowOpen() override;
		void destroyWindow() override;
		event getEvent() override;
        void draw(Entity) override;
		bool getTexture(Entity entity) override;
        void refreshWindow() override;
    private:
        caca_display_t *_display;
        caca_canvas_t *_canvas;
        caca_font_t *_font;
        bool _isOpen;
        std::map<std::string, struct image *> textureMap;
};

#endif /* !CACA_HPP_ */

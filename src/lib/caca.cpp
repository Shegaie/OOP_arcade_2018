/*
** EPITECH PROJECT, 2019
** OOP_arcade_2018
** File description:
** caca
*/

#include "caca.hpp"
#include <cstdio>
#include <iostream>

static struct image *load_image(char const * name)
{
    auto im = static_cast<struct image *>(malloc(sizeof(struct image)));
	unsigned int depth, bpp, r_mask, g_mask, b_mask, a_mask;
	Imlib_Image image = imlib_load_image(name);
	if(!image)
	{
		free(im);
		return nullptr;
	}
	imlib_context_set_image(image);
	im->pixels = (char *)imlib_image_get_data_for_reading_only();
	im->w = static_cast<unsigned int>(imlib_image_get_width());
	im->h = static_cast<unsigned int>(imlib_image_get_height());
	r_mask = 0x00ff0000;
	g_mask = 0x0000ff00;
	b_mask = 0x000000ff;
	a_mask = 0xff000000;
	bpp = 32;
	depth = 4;
	im->dither = caca_create_dither(bpp, im->w, im->h, depth * im->w, r_mask, g_mask, b_mask, a_mask);
	if(!im->dither)
	{
		imlib_free_image();
		free(im);
		return nullptr;
	}

	return im;
}

static void unload_image(struct image *im)
{
	imlib_free_image();
	free(im);
}

void caca::initWindow()
{
    _font = caca_load_font(caca_get_font_list()[0], 0);
    _canvas = caca_create_canvas(1920 / (caca_get_font_width(_font) + 1), 1080 / (caca_get_font_height(_font) + 1));
	_display = caca_create_display(_canvas);
	caca_set_display_title(_display, "Arcade (Libcaca)");
	caca_set_display_time(_display, 1);
	_isOpen = true;
}

bool caca::isWindowOpen()
{
	return _isOpen;
}

void caca::destroyWindow()
{
	_isOpen = false;
    /*for (auto const& mapComponent : textureMap)
        unload_image(mapComponent.second);*/
    caca_free_font(_font);
    caca_free_display(_display);
    caca_free_canvas(_canvas);
}

ILib::event caca::getEvent()
{
	caca_event_t event;
	caca_get_event(_display, CACA_EVENT_ANY, &event, 1);
	int key;

	if (caca_get_event_type(&event) & CACA_EVENT_KEY_RELEASE)
	{
		key = caca_get_event_key_ch(&event);
	    char keys[] = {
	            'l',
	            'k',
	            'i',
	            'o',
	            'n',
	            'r',
	            'p',
	            'h',
	            27,
	            13
	    };
	    ILib::event events[] = {
	            next_lib,
	            prev_lib,
	            prev_game,
	            next_game,
	            changeMenuModule,
	            restart,
	            menu,
	            help,
	            escape,
	            enter
	    };
        int i = 0;
        for (const char &_key : keys) {
            if (key == _key)
                return (events[i]);
            i++;
        }
	}
	else if (caca_get_event_type(&event) & CACA_EVENT_KEY_PRESS)
	{
		key = caca_get_event_key_ch(&event);
        int keys[] = {
                273,
                274,
                275,
                276
        };
        ILib::event events[] = {
                up,
                down,
                left,
                right
        };
        int i = 0;
        for (const int &_key : keys) {
            if (key == _key)
                return (events[i]);
            i++;
        }
	}
	return (none);
}

static uint16_t convertToArgb(color_t color)
{
    return static_cast<uint16_t>((color.b / 16) | ((color.g / 16) << 4) | ((color.r / 16) << 8) | ((color.a / 16) << 12));
}

void caca::draw(Entity entity)
{
	struct image *i;
	vector2_t entityPosition = entity.getPosition();
	vector2_t entitySize = entity.getSize();
	int fontWidth = caca_get_font_width(_font);
    int fontHeight = caca_get_font_height(_font);
    if (getTexture(entity)) {
        i = textureMap[entity.getTexture()._path];
        caca_dither_bitmap(_canvas,
                           static_cast<int>(entityPosition.x / fontWidth), /* x */
                           static_cast<int>(entityPosition.y / fontHeight), /* y */
                           static_cast<int>((i->w / fontWidth * entitySize.x) < 7 ? (i->w / fontWidth * entitySize.x) * 2 : (i->w / fontWidth * entitySize.x)), /* width */
                           static_cast<int>((i->h / fontHeight * entitySize.y) < 7 ? (i->h / fontHeight * entitySize.y) * 2 : (i->h / fontHeight * entitySize.y)), /* height */
                           i->dither,
                           i->pixels);
    } else if (!entity.getTexture()._text.string.empty()) {
        caca_set_color_ansi(_canvas, CACA_WHITE, CACA_TRANSPARENT);
        caca_put_str(_canvas,
                     static_cast<int>(entityPosition.x / fontWidth), /* x */
                     static_cast<int>(entityPosition.y / fontHeight), /* y */
                     (entity.getTexture()._text.string.c_str())
        );
    } else {
        color_t color = entity.getTexture()._color;
        caca_set_color_argb(_canvas, 0x0000, convertToArgb(color));
        caca_fill_box(_canvas,
                      static_cast<int>(entityPosition.x / fontWidth), /* x */
                      static_cast<int>(entityPosition.y / fontHeight), /* y */
                      static_cast<int>(entitySize.x / fontWidth), /* width */
                      static_cast<int>(entitySize.y / fontHeight), /* height */
                      ' ');
    }
}

void caca::refreshWindow()
{
	caca_refresh_display(_display);
	caca_set_color_ansi(_canvas, CACA_BLACK, CACA_BLACK);
	caca_clear_canvas(_canvas);
}

bool caca::getTexture(Entity entity)
{
    struct image *image;
    if (!entity.getTexture()._path.empty()) {
        if (textureMap.find(entity.getTexture()._path) == textureMap.end()) {
            image = load_image(entity.getTexture()._path.c_str());
            textureMap[entity.getTexture()._path] = image;
        }
        return true;
    }
    return false;
}

extern "C" {
caca *entryPoint()
{
    return new caca();
}
}
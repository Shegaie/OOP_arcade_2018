/*
** EPITECH PROJECT, 2022
** cpp_rush3_2018
** File description:
** Created by lgregoire,
*/
#ifndef CPP_RUSH3_2018_FEE_HPP
#define CPP_RUSH3_2018_FEE_HPP

#include "ILib.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

class sfml : public ILib
{
    public:
		void initWindow() override;
		bool isWindowOpen() override;
        void destroyWindow() override;
        void refreshWindow() override;
    	event getEvent() override;
		void draw(Entity) override;
		bool getTexture(Entity entity) override;

	sf::RenderWindow _window;
	private:
		std::map<std::string, sf::Texture> textureMap;
		sf::Font _font;
};

#endif //CPP_RUSH3_2018_FEE_HPP

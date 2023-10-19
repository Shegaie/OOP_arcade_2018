/*
** EPITECH PROJECT, 2019
** OOP_arcade_2018
** File description:
** main
*/

#include <stdio.h>
#include <iostream>
#include "Core.hpp"

void core(char *args[]);

void printUsage()
{
	std::cerr
	<<"USAGE\n"
	<< "\t./arcade library_name\n\n"
	<< "DESCRIPTION\n"
	<< "\t library_name\tThe path of the library you want to start the program with"
	<< std::endl;
}

int main(int argc, char **argv)
{
    Core core;

	if (argc != 2) {
		printUsage();
		return (84);
	}
	core.start(static_cast<std::string>(argv[1]));
}
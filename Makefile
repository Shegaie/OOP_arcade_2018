##
## EPITECH PROJECT, 2017
## Makefile
## File description:
## Makefile
##


SRC_DIR		=	./src/

LIB_DIR		=	./lib/

GAME_DIR	=	./games/

CALCUL_DIR	=	$(SRC_DIR)calcul/

SRC_LIB_DIR	=	$(SRC_DIR)lib/

GRPH_DIR	=	$(SRC_DIR)graph/

CORE_DIR	=	$(SRC_DIR)core/

SRC_GAME_DIR	=	$(SRC_DIR)game/

ENTITY_DIR	=	$(SRC_DIR)entity/


SRC		=	$(SRC_DIR)main.cpp					\
			$(CORE_DIR)Core.cpp					\
			$(ENTITY_DIR)Entity.cpp				\
			$(ENTITY_DIR)Texture.cpp			\

NAME	=	arcade

NAME_G1	=	./games/lib_arcade_pacman.so

NAME_G2	=	./games/lib_arcade_nibbler.so

SRC_G1	=	$(SRC_GAME_DIR)pacman/pacman.cpp	\
			$(ENTITY_DIR)Entity.cpp				\
			$(ENTITY_DIR)Texture.cpp

SRC_G2	=	$(SRC_GAME_DIR)nibbler/nibbler.cpp	\
			$(ENTITY_DIR)Entity.cpp				\
			$(ENTITY_DIR)Texture.cpp

NAME_L1	=	$(LIB_DIR)lib_arcade_sfml.so

NAME_L2	=	$(LIB_DIR)lib_arcade_sdl.so

NAME_L3	=	$(LIB_DIR)lib_arcade_caca.so

SRC_L1		=	$(SRC_LIB_DIR)sfml.cpp			\
				$(ENTITY_DIR)Entity.cpp			\
				$(ENTITY_DIR)Texture.cpp

SRC_L2		=	$(SRC_LIB_DIR)sdl.cpp			\
				$(ENTITY_DIR)Entity.cpp			\
				$(ENTITY_DIR)Texture.cpp

SRC_L3		=	$(SRC_LIB_DIR)caca.cpp			\
				$(ENTITY_DIR)Entity.cpp			\
				$(ENTITY_DIR)Texture.cpp

OBJ	=	$(SRC:.cpp=.o)

LDFLAGS	=	-ldl -lsfml-graphics -lsfml-window -lsfml-system -lSDL2 -lSDL2_image -lSDL2_ttf -lcaca -lcaca++ -lImlib2

CXXFLAGS	=	-Wall -Wextra -I$(GRPH_DIR) -I$(CORE_DIR) -I$(ENTITY_DIR) -I$(CALCUL_DIR)


all:	$(NAME)

$(NAME):	$(OBJ) games $(OBJ) graphicals core

core:	$(OBJ)
	g++ $(OBJ) -o $(NAME) $(CXXFLAGS) $(LDFLAGS)

games:
	g++ -shared -fPIC -o $(NAME_G1) $(SRC_G1) -I$(GRPH_DIR) -I$(CORE_DIR) -I$(ENTITY_DIR) -I$(SRC_GAME_DIR)pacman/ -I$(CALCUL_DIR)
	g++ -shared -fPIC -o $(NAME_G2) $(SRC_G2) -I$(GRPH_DIR) -I$(CORE_DIR) -I$(ENTITY_DIR) -I$(SRC_GAME_DIR)nibbler/ -I$(CALCUL_DIR)

graphicals:
	g++ -shared -fPIC -o $(NAME_L1) $(SRC_L1) -I$(GRPH_DIR) -I$(CORE_DIR) -I$(ENTITY_DIR) -I$(CALCUL_DIR)
	g++ -shared -fPIC -o $(NAME_L2) $(SRC_L2) -I$(GRPH_DIR) -I$(CORE_DIR) -I$(ENTITY_DIR) -I$(CALCUL_DIR)
	g++ -shared -fPIC -o $(NAME_L3) $(SRC_L3) -I$(GRPH_DIR) -I$(CORE_DIR) -I$(ENTITY_DIR) -I$(CALCUL_DIR)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -rf $(NAME) $(NAME_L1) $(NAME_L2) $(NAME_G1) $(NAME_G2)

re:	fclean all

debug: CXXFLAGS += -g
debug: re

.PHONY: games

#Command to build lib.so
#g++ -shared -fPIC -o lib_arcade_sfml.so lib/fee.cpp

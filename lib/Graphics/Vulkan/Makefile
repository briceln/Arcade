##
## EPITECH PROJECT, 2018
## Arcade
## File description:
## Makefile for SFML shared Library
##

NAME	=	lib_arcade_vulkan.so

CXX		=	g++

RM		=	rm -f

SRCS	=	./Vulkan.cpp	\
			./extern.cpp	\

OBJS	=	$(SRCS:.cpp=.o)

CXXFLAGS	=	-W -Wall -Wextra -fPIC -shared -std=c++14
LDFLAGS		=	-lvulkan `pkg-config --cflags glfw3` `pkg-config --libs glfw3` -lGL -lm -lXrandr -lXi -lX11 -lXxf86vm -lpthread

WARN_COLOR	=	\033[0;33m
COM_COLOR	=	\033[0;34m
OBJ_COLOR	=	\033[0;36m
OK_COLOR	=	\033[0;32m
ERROR_COLOR	=	\033[0;31m
NO_COLOR	=	\033[m
OK_STRING	=	"[OK]"
WARN_STRING	=	"[WARNING]"

all: $(NAME)

%.o: %.cpp
		@printf "[\033[0;32mcompiled\033[0m] % 70s\n" $< | tr ' ' '.'
		@$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $<


$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)
	mv $(NAME) ../../
	@printf "$(OK_COLOR)% 55s % 25s$(NO_COLOR)\n\n" "[BUILD] $(NAME)" "" | tr ' ' '-'

clean:
ifneq ($(shell find -name '*.o'),)
	@printf "[$(ERROR_COLOR)REMOVE$(NO_COLOR)] % 70s\n" "OBJECT FILE ($(NAME))" | tr ' ' '.'
	@$(RM) $(OBJS)
else
	@printf "[$(WARN_COLOR)NONE$(NO_COLOR)] % 72s\n" "OBJECT FILE ($(NAME))" | tr ' ' '.'
endif

fclean: clean
	@printf "[$(ERROR_COLOR)REMOVE$(NO_COLOR)] % 70s\n" "$(NAME)" | tr ' ' '.'
	@$(RM) ../../$(NAME)

re: fclean all

.PHONY: all clean fclean re
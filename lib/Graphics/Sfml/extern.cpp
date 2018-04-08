/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by asianpw,
*/

#include "../../../inc/IDisplay.hpp"
#include "../../../inc/Sfml.hpp"

extern "C" IDisplay	*create_object(size_t w, size_t h)
{
	return new SfmlDisplay(w, h);
}

extern "C" void	destroy_object(IDisplay *object)
{
	delete object;
}

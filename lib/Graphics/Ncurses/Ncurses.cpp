//
// EPITECH PROJECT, 2021
// cpp_arcade
// File description:
// Created by asianpw,
//

#include <ncurses.h>
#include <unistd.h>
#include <iostream>
#include "../../../inc/Ncurses.hpp"

NcursesDisplay::NcursesDisplay(size_t w, size_t h)
{
	(void)w;
	(void)h;
	allEvent.insert({arcade::UP, KEY_UP});
	allEvent.insert({arcade::DOWN, KEY_DOWN});
	allEvent.insert({arcade::LEFT, KEY_LEFT});
	allEvent.insert({arcade::RIGHT, KEY_RIGHT});
	allEvent.insert({arcade::ENTER, KEY_ENTER});
	allEvent.insert({arcade::ESCAPE, 27});
	initscr();
	cbreak();
	keypad(stdscr, true);
	nodelay(stdscr, true);
}

NcursesDisplay::~NcursesDisplay()
{
	clear();
	refresh();
	endwin();
}


bool	NcursesDisplay::Display()
{
	refresh();
	return (false);
}

bool	NcursesDisplay::isOpen()
{
	return true;
}

bool	NcursesDisplay::isKey()
{
	currentKey = getch();
	return currentKey != ERR;
}

bool	NcursesDisplay::GetKey(arcade::TypeEvent typeEvent, std::string const &type)
{
	if (typeEvent == arcade::WINDOW)
		return false;
	for (auto const &it : allEvent) {
		if (it.first == type && it.second == currentKey) {
			currentKey = ERR;
			return true;
		}
	}
	return false;
}

void	NcursesDisplay::destroyWindow()
{
	endwin();
}

bool NcursesDisplay::loadText(std::map<std::string, Texture> const &text)
{
	for (auto const &it : text) {
		if (!it.second.isFile && it.second.display) {
			mvprintw(it.second.position.y % LINES, it.second.position.x % COLS, "%s", it.second.path.c_str());
		}
	}
	return true;
}

bool NcursesDisplay::loadTexture(std::map<std::string, Texture> const &texture)
{
	clear();
	for (auto const &it : texture) {
		if (it.second.isFile && it.second.display && it.second.similar != ' ')
			mvprintw(it.second.position.y % LINES, it.second.position.x % COLS, "%c", it.second.similar);
	}
	return false;
}

void NcursesDisplay::changeLibrary(std::string const &path)
{
	change = true;
	newLibraryPath = path;
}

bool NcursesDisplay::getChange() const
{
	return change;
}

void NcursesDisplay::setChange(bool state)
{
	change = state;
}

const std::string &NcursesDisplay::getLibraryPath() const
{
	return newLibraryPath;
}

const std::string &NcursesDisplay::getNewGamePath() const
{
	return newGamePath;
}

void NcursesDisplay::setNewGamePath(std::string const &path)
{
	newGamePath = path;
}

bool NcursesDisplay::getSwitchScene() const
{
	return switchScene;
}

void NcursesDisplay::setSwitchScene(bool state)
{
	switchScene = state;
}

bool NcursesDisplay::loadMap(std::vector<std::vector<char>> const &map)
{
	int	y = 0;
	int	x = 0;

	for (auto const &line : map) {
		x = 0;
		for (auto const &character : line) {
			mvprintw(x, y, "%c", character);
			x += 1;
		}
		y += 1;
	}
	return false;
}

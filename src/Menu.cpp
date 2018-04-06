/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by asianpw,
*/

#include <iostream>
#include <dirent.h>
#include <cstring>
#include <algorithm>
#include "../inc/utils.hpp"
#include "Menu.hpp"
#include "../inc/Texture.hpp"
#include "../inc/GameLoader.hpp"
#include "../inc/ArcadeException.hpp"

void	listFiles(const char* path, std::vector<std::string> &list)
{
	DIR		*dirFile = opendir(path);
	struct dirent	*hFile;

	if (dirFile)
	{
		while ((hFile = readdir( dirFile )) != nullptr) {
			if ((hFile->d_name[0] == '.')) continue;
			if (strstr(hFile->d_name, ".so"))
				list.emplace_back(hFile->d_name);
		}
		closedir(dirFile);
	}
}

void	init_text(char const *dir, std::vector<std::string> &list, std::map<std::string, Texture> &text, Position &pos)
{
	size_t	count = 0;

	listFiles(dir, list);
	for (auto const &current : list) {
		text.insert({current, createTexture(current, count == 0, pos.x, pos.y)});
		createTexture(current, count == 0, pos.x, pos.y);
		count += 1;
	}
}

Menu::Menu()
{
	Position	pos = {arcade::WIDTH / 2 - 100, 100};

	time = 0;
	init_text(arcade::GRAPHICSDIR, graphicLib, menuText, pos);
	pos.y = 200;
	init_text(arcade::GAMESDIR, gamesLib, menuText, pos);
	menuText.insert({"press", createTexture(PRESS, true, arcade::WIDTH / 2, 500)});
	menuTexture.insert({"cursor", createTexture("./res/menu_cursor.png", true, 140, 100)});
	menuTexture.insert({"0", createTexture("./res/menu_wallpaper.jpeg", true, 0, 0)});
	menuTexture.insert({"champi", createTexture("./res/menu_champi.png", true, 80, 160)});
	menuTexture.insert({"mario", createTexture("./res/menu_mario.png", true, 0, 130)});
	current = &graphicLib;
}

void	Menu::sceneEvent(IDisplay *display)
{
	auto	it = current->begin();

	if (display->GetKey(arcade::WINDOW, arcade::CLOSE))
		display->destroyWindow();
	if (display->GetKey(arcade::KEYBOARD, arcade::ESCAPE))
		display->destroyWindow();
	if (display->GetKey(arcade::KEYBOARD, arcade::UP)) {
		if (menuTexture["cursor"].position.y == 200) {
			menuTexture["cursor"].position.y = 100;
			current = &graphicLib;
		}
	}
	if (display->GetKey(arcade::KEYBOARD, arcade::DOWN)) {
		if (menuTexture["cursor"].position.y == 100) {
			menuTexture["cursor"].position.y = 200;
			current = &gamesLib;
		}
	}
	if (display->GetKey(arcade::KEYBOARD, arcade::LEFT)) {
		while (it != current->end()) {
			if (it != current->begin() && menuText[*it].display) {
				menuText[*it].display = false;
				menuText[*--it].display = true;
				if (current == &graphicLib)
					display->changeLibrary(menuText[*it].path);
				break;
			}
			it++;
		}
	}
	if (display->GetKey(arcade::KEYBOARD, arcade::RIGHT)) {
		while (it != current->end()) {
			if (it != current->end() - 1 && menuText[*it].display) {
				menuText[*it].display = false;
				menuText[*++it].display = true;
				if (current == &graphicLib)
					display->changeLibrary(menuText[*it].path);
				break;
			}
			it++;
		}
	}
	if (display->GetKey(arcade::KEYBOARD, arcade::ENTER)) {
		for (auto const &game : gamesLib) {
			if (menuText[game].display) {
				display->setSwitchScene(true);
				display->setNewGamePath(arcade::GAMESDIR + game);
			}
		}
	}
}

void	Menu::compute()
{
	if (time == 10) {
		menuText["press"].display = !menuText["press"].display;
		time = 0;
	}
	menuTexture["champi"].position.x += 2;
	menuTexture["mario"].position.x += 2;
	if (menuTexture["champi"].position.x > (int)(arcade::WIDTH + 20))
		menuTexture["champi"].position.x = -20;
	if (menuTexture["mario"].position.x > (int)(arcade::WIDTH + 20))
		menuTexture["mario"].position.x = -20;
	time += 1;
}

std::map<std::string, Texture> Menu::getText() const
{
	return menuText;
}

std::map<std::string, Texture> Menu::getTexture() const
{
	return menuTexture;
}

std::vector<std::vector<char>> Menu::getMap() const
{
	return menuMap;
}

//
// EPITECH PROJECT, 2021
// cpp_arcade
// File description:
// Created by asianpw,
//

#ifndef CPP_ARCADE_UTILS_HPP
#define CPP_ARCADE_UTILS_HPP

#include <cstdint>
#include <vector>
#include <string>

namespace arcade {
	enum TypeEvent {
		WINDOW,
		JOYSTICK,
		KEYBOARD,
		MOUSE
	};

	static const char	ESCAPE[] = "ESCAPE";
	static const char	CLOSE[] = "CLOSE";
	static const char	UP[] = "UP";
	static const char	DOWN[] = "DOWN";
	static const char	LEFT[] = "LEFT";
	static const char	RIGHT[] = "RIGHT";
}

bool checkFileExist(std::string const &) noexcept;

#endif //CPP_ARCADE_UTILS_HPP

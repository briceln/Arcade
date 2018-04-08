//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// Nibbler.cpp
//

#include <vector>
#include <iostream>
#include "Nibbler.hpp"
#include "NibblerScene.hpp"

Nibbler::Nibbler()
{
	this->name = "Nibbler";
	this->description = "";
}

std::string	const&Nibbler::getDescription() const
{
	return description;
}

std::string	const&Nibbler::getName() const
{
	return name;
}

IScene	*Nibbler::start()
{
	return new NibblerScene();
}
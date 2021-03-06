//
// EPITECH PROJECT, 2018
// PacmanScene
// File description:
// source file
//

#include "PacmanScene.hpp"
#include <chrono>
#include <iostream>
#include "../../../inc/Time.hpp"

void    PacmanScene::print_map()
{
	std::cout<<"*******************************************************"<<std::endl;
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 26; j++)
			std::cout<<pacmanMap[i][j];
	std::cout<<"*******************************************************"<<std::endl;
}

PacmanScene::PacmanScene() : pacmanMap(WIDTH, std::vector<char>(HEIGHT))
{
	size_t  x = 0;
	size_t  y = 0;

	createMap();
	SetCharacters();
	score = 0;
	nbr_food = get_nbrfood();
	PacmanText.insert({"score_value", {std::to_string(score), ' ', false, true, {150, 550}}});
	PacmanText.insert({"title", {"Score :", ' ', false, true, {20, 550}}});
	PacmanText.insert({"food_value", {std::to_string(nbr_food), ' ', false, true, {540, 550}}});
	PacmanText.insert({"title_food", {"Remaining food :", ' ', false, true, {240, 550}}});
    PacmanText.insert({"title_life", {"Life : ", ' ', false, true, {610, 550}}});
    PacmanText.insert({"life_value", {std::to_string(life), ' ', false, true, {690, 550}}});
	for (auto const &line : pacmanMap) {
		x = 0;
		for (auto const &block : line) {
			if (block == '*')
				PacmanTexture.insert({"wall" + std::to_string(y) + std::to_string(x), (Texture){"./res/wall_nibbler.png", ' ',  true, true, {(int)(x * WIDTH_TEXTURE), (int)(y * HEIGHT_TEXTURE)}}});
			else if (block == 'G')
				PacmanTexture.insert({"player", {"./res/pacman_right.jpg", ' ',  true, true, {(int)(x * WIDTH_TEXTURE), (int)(y * HEIGHT_TEXTURE)}}});
			else if (block == 'o')
				PacmanTexture.insert({"food" + std::to_string(y) + std::to_string(x), (Texture){"./res/food_pacman.png", ' ',  true, true, {(int)(x * WIDTH_TEXTURE), (int)(y * HEIGHT_TEXTURE)}}});
			else if (block == 'B')
				PacmanTexture.insert({"gosht2", {"./res/pink.jpg", ' ',  true, true, {(int)(x * WIDTH_TEXTURE), (int)(y * HEIGHT_TEXTURE)}}});
			else if (block == 'C')
				PacmanTexture.insert({"gosht3", {"./res/pink.jpg", ' ', true, true, {(int)(x * WIDTH_TEXTURE), (int)(y * HEIGHT_TEXTURE)}}});
			x = x + 1;
		}
		y = y + 1;
	}
}

void    PacmanScene::SetCharacters(void)
{
	player.x = 8;
	player.y = 13;
	gosht2.x = 9;
	gosht2.y = 13;
	gosht3.x = 10;
	gosht3.y = 12;
	pacmanMap[gosht2.x][gosht2.y] = 'B';
	pacmanMap[gosht3.x][gosht3.y] = 'C';
	pacmanMap[player.x][player.y] = 'G';
}

std::map<std::string, Texture>  PacmanScene::getTexture() const
{
	return PacmanTexture;
}

std::map<std::string, Texture>  PacmanScene::getText() const
{
	return PacmanText;
}

void    PacmanScene::sceneEvent(IDisplay *display)
{
	if (display->GetKey(arcade::KEYBOARD, arcade::CLOSE)) {
		display->destroyWindow();
	}
	if (display->GetKey(arcade::KEYBOARD, arcade::ESCAPE)) {
		display->destroyWindow();
	}
	if (display->GetKey(arcade::KEYBOARD, arcade::LEFT)) {
		way = 0;
		if (loose == true || win == true) {
			PacmanText.insert({"goMenu", {"Press Enter to go to the menu", ' ', false, true, {200, 340}}});
			exit(0);
		}
		Move_left();
		PacmanTexture.erase("player");
		PacmanTexture.insert({"player", {"./res/pacman_left.jpg", ' ',  true, true, {(int)(player.y * WIDTH_TEXTURE), (int)(player.x * HEIGHT_TEXTURE)}}});
	}
	if (display->GetKey(arcade::KEYBOARD, arcade::RIGHT)) {
		way = 1;
		if (loose == true || win == true) {
		    PacmanText.insert({"goMenu", {"Press Enter to go to the menu", ' ', false, true, {200, 340}}});
		    exit(0);
		}
		Move_right();
		PacmanTexture.erase("player");
		PacmanTexture.insert({"player", {"./res/pacman_right.jpg", ' ',  true, true, {(int)(player.y * WIDTH_TEXTURE), (int)(player.x * HEIGHT_TEXTURE)}}});
	}
	if (display->GetKey(arcade::KEYBOARD, arcade::UP)) {
		way = 2;
		if (loose == true || win == true) {
			exit(0);
		}
		Move_up();
		PacmanTexture.erase("player");
		PacmanTexture.insert({"player", {"./res/pacman_up.jpg", ' ',  true, true, {(int)(player.y * WIDTH_TEXTURE), (int)(player.x * HEIGHT_TEXTURE)}}});
	}
	if (display->GetKey(arcade::KEYBOARD, arcade::DOWN)) {
		way = 3;
		Move_down();
		PacmanTexture.erase("player");
		PacmanTexture.insert({"player", {"./res/pacman_down.jpg", ' ',  true, true, {(int)(player.y * WIDTH_TEXTURE), (int)(player.x * HEIGHT_TEXTURE)}}});
	}
}

void    PacmanScene::Move_right(void)
{
	if (pacmanMap[player.x][player.y + 1] == '*')
		return;
	if (pacmanMap[player.x][player.y + 1] == 'o') {
		score += 10;
		nbr_food--;
		PacmanTexture.erase("food" + std::to_string(player.x) + std::to_string(player.y + 1));
		PacmanText["score_value"].path = std::to_string(score);
		PacmanText["food_value"].path = std::to_string(nbr_food);
	}
	player.y++;

	PacmanTexture["player"].position.x += WIDTH_TEXTURE;
	if (pacmanMap[player.x][player.y] == 'B' || pacmanMap[player.x][player.y] == 'C') {
        life--;
		pacmanMap[player.x][player.y] = ' ';
		player.x = 8;
		player.y = 13;
		pacmanMap[player.x][player.y] = 'G';
        PacmanTexture.erase("player");
        PacmanTexture.insert({"player", {"./res/pacman_right.jpg", ' ',  true, true, {(int)(player.y * WIDTH_TEXTURE), (int)(player.x * HEIGHT_TEXTURE)}}});
	}
	if (nbr_food == 0) {
		PacmanText.insert({"lost", {"You Won", ' ', false, true, {300, 280}}});
		win = true;
	}
	pacmanMap[player.x][player.y] = 'G';
	pacmanMap[player.x][player.y - 1] = ' ';
}

void    PacmanScene::Move_left(void)
{
	if (pacmanMap[player.x][player.y - 1] == '*')
		return;
	if (pacmanMap[player.x][player.y - 1] == 'o') {
		score += 10;
		nbr_food--;
		PacmanTexture.erase("food" + std::to_string(player.x) + std::to_string(player.y - 1));
		PacmanText["score_value"].path = std::to_string(score);
		PacmanText["food_value"].path = std::to_string(nbr_food);
	}
	player.y--;

	PacmanTexture["player"].position.x -= WIDTH_TEXTURE;
	if (pacmanMap[player.x][player.y] == 'C' || pacmanMap[player.x][player.y] == 'B') {
		life--;
		pacmanMap[player.x][player.y] = ' ';
		player.x = 8;
		player.y = 13;
		pacmanMap[player.x][player.y] = 'G';
        PacmanTexture.erase("player");
        PacmanTexture.insert({"player", {"./res/pacman_right.jpg", ' ',  true, true, {(int)(player.y * WIDTH_TEXTURE), (int)(player.x * HEIGHT_TEXTURE)}}});
	}
	if (nbr_food == 0) {
		PacmanText.insert({"lost", {"You Won", ' ', false, true, {300, 280}}});
		win = true;
	}
	pacmanMap[player.x][player.y] = 'G';
	pacmanMap[player.x][player.y + 1] = ' ';
}

void    PacmanScene::Move_up(void)
{
	if (pacmanMap[player.x - 1][player.y] == '*')
		return;
	if (pacmanMap[player.x - 1][player.y] == 'o') {
		score += 10;
		nbr_food--;
		PacmanTexture.erase("food" + std::to_string(player.x - 1) + std::to_string(player.y));
		PacmanText["score_value"].path = std::to_string(score);
		PacmanText["food_value"].path = std::to_string(nbr_food);
	}
	player.x--;

	PacmanTexture["player"].position.y -= HEIGHT_TEXTURE;
	if (pacmanMap[player.x][player.y] == 'C' || pacmanMap[player.x][player.y] == 'B') {
        life--;
		pacmanMap[player.x][player.y] = ' ';
		player.x = 8;
		player.y = 13;
		pacmanMap[player.x][player.y] = 'G';
        PacmanTexture.erase("player");
        PacmanTexture.insert({"player", {"./res/pacman_right.jpg", ' ',  true, true, {(int)(player.y * WIDTH_TEXTURE), (int)(player.x * HEIGHT_TEXTURE)}}});
	}
	if (nbr_food == 0) {
		PacmanText.insert({"lost", {"You Won", ' ', false, true, {300, 280}}});
		win = true;
	}
	pacmanMap[player.x][player.y] = 'G';
	pacmanMap[player.x + 1][player.y] = ' ';
}

void    PacmanScene::Move_down(void)
{
	if (pacmanMap[player.x + 1][player.y] == '*' || player.x > 20)
		return;
	if (pacmanMap[player.x + 1][player.y] == 'o') {
		score += 10;
		nbr_food--;
		PacmanTexture.erase("food" + std::to_string(player.x + 1) + std::to_string(player.y));
		PacmanText["score_value"].path = std::to_string(score);
		PacmanText["food_value"].path = std::to_string(nbr_food);
	}
	player.x++;

	PacmanTexture["player"].position.y += HEIGHT_TEXTURE;
	if (pacmanMap[player.x][player.y] == 'C' || pacmanMap[player.x][player.y] == 'B') {
        life--;
		pacmanMap[player.x][player.y] = ' ';
		player.x = 8;
		player.y = 13;
		pacmanMap[player.x][player.y] = 'G';
        PacmanTexture.erase("player");
        PacmanTexture.insert({"player", {"./res/pacman_right.jpg", ' ',  true, true, {(int)(player.y * WIDTH_TEXTURE), (int)(player.x * HEIGHT_TEXTURE)}}});
	}
	if (nbr_food == 0) {
		PacmanText.insert({"lost", {"You Won", ' ', false, true, {300, 280}}});
		win = true;
	}
	pacmanMap[player.x][player.y] = 'G';
	pacmanMap[player.x - 1][player.y] = ' ';
}

int PacmanScene::get_nbrfood(void)
{
	nbr_food = 0;
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 26; j++) {
			if (pacmanMap[i][j] == 'o')
				nbr_food++;
		}
	}
	return nbr_food;
}

void    PacmanScene::compute(void)
{
	long now = getCurrentTime();

	if (now - currentTime > 250) {
		GoshtMove2();
		GoshtMove3();
		if (way == 0)
			Move_left();
		else if (way == 1)
			Move_right();
		else if (way == 2)
			Move_up();
		else if (way == 3)
			Move_down();
        PacmanText["life_value"].path = std::to_string(life);
		if (life < 0) {
			PacmanText.insert({"lost", {"Game Over", ' ', false, true, {300, 280}}});
			loose = true;
		}
		currentTime = now;
	}
}

void    PacmanScene::createMap(void)
{
	pacmanMap.resize(HEIGHT, std::vector<char>(WIDTH));
	pacmanMap = {{'\n','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*'},
                 {'\n','*','o','o','*','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','*','o','o','*'},
                 {'\n','*','o','o','*','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','*','o','o','*'},
                 {'\n','*','o','o','*','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','*','o','o','*'},
                 {'\n','*','o','o','*','o','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','o','*','o','o','*'},
                 {'\n','*','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','*'},
                 {'\n','*','o','*','*','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','*','*','o','*'},
                 {'\n','*','o','*','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','*','o','*'},
                 {'\n','*','o','*','o','o','*','*','o','*','*','*',' ',' ',' ','*','*','*','o','o','*','*','o','*','o','*'},
                 {'\n','*','o','o','o','o','o','o','o','*',' ',' ',' ',' ',' ',' ',' ','*','o','o','o','o','o','o','o','*'},
                 {'\n','*','o','o','o','o','o','o','o','*',' ',' ',' ',' ',' ',' ',' ','*','o','o','o','o','o','o','o','*'},
                 {'\n','*','o','o','o','o','o','o','o','*',' ',' ',' ',' ',' ',' ',' ','*','o','o','o','o','o','o','o','*'},
                 {'\n','*','o','*','o','o','*','*','o','*','*','*','*','*','*','*','*','*','o','o','*','*','o','*','o','*'},
                 {'\n','*','o','*','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','*','o','*'},
                 {'\n','*','o','*','*','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','*','*','o','*'},
                 {'\n','*','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','*'},
                 {'\n','*','o','o','*','o','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','o','*','o','o','*'},
                 {'\n','*','o','o','*','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','*','o','o','*'},
                 {'\n','*','o','o','*','o','o','o','o','o','o',' ','o','o','o','o','o','o','o','o','o','o','*','o','o','*'},
                 {'\n','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*'}};
}

std::vector<std::vector<char>>  PacmanScene::getMap() const
{
	return pacmanMap;
}

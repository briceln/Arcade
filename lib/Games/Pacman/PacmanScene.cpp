//
// EPITECH PROJECT, 2018
// PacmanScene
// File description:
// source file
//

#include "PacmanScene.hpp"

PacmanScene::PacmanScene() : pacmanMap(HEIGHT, std::vector<char>(WIDTH))
{
	size_t  x = 0;
	size_t  y = 0;

	createMap();
	SetCharacters();
	for (auto const &line : pacmanMap) {
		x = 0;
		for (auto const &block : line) {
			if (block == '*')
				PacmanTexture.insert({"block" + std::to_string(y) + std::to_string(x), (Texture){"./res/wall_nibbler.png", ' ',  true, true, {(int)(x * WIDTH_TEXTURE), (int)(y * HEIGHT_TEXTURE)}}});
			else if (block == 'G')
				PacmanTexture.insert({"block" + std::to_string(y) + std::to_string(x), (Texture){"./res/player_pacman.png", ' ',  true, true, {(int)(x * WIDTH_TEXTURE), (int)(y * HEIGHT_TEXTURE)}}});
			else if (block == 'o')
				PacmanTexture.insert({"block" + std::to_string(y) + std::to_string(x), (Texture){"./res/food_pacman.png", ' ',  true, true, {(int)(x * WIDTH_TEXTURE), (int)(y * HEIGHT_TEXTURE)}}});
			else if (block == 'E')
				PacmanTexture.insert({"block" + std::to_string(y) + std::to_string(x), (Texture){"./res/Ghosts_pacman.png", ' ',  true, true, {(int)(x * WIDTH_TEXTURE), (int)(y * HEIGHT_TEXTURE)}}});
			x = x + 1;
		}
		y = y + 1;
	}
}

void    PacmanScene::SetCharacters(void)
{
	gosht1.x = 9;
	gosht1.y = 12;
	gosht2.x = 9;
	gosht2.y = 13;
	gosht3.x = 10;
	gosht3.y = 12;
	gosht4.x = 10;
	gosht4.y = 13;
	pacmanMap[gosht1.x][gosht1.y] = 'E';
	pacmanMap[gosht2.x][gosht2.y] = 'E';
	pacmanMap[gosht3.x][gosht3.y] = 'E';
	pacmanMap[gosht4.x][gosht4.y] = 'E';
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
		if (&move == &dir.right || &move == &dir.left)
			return;
		else
			move = dir.left;
	}
	if (display->GetKey(arcade::KEYBOARD, arcade::RIGHT)) {
		if (&move == &dir.right || &move == &dir.left)
			return;
		else
			move = dir.right;
	}
	if (display->GetKey(arcade::KEYBOARD, arcade::UP)) {
		if (&move == &dir.up || &move == &dir.down)
			return;
		else
			move = dir.up;
	}
	if (display->GetKey(arcade::KEYBOARD, arcade::DOWN)) {
		if (&move == &dir.up || &move == &dir.down)
			return;
		else
			move = dir.down;
	}
}

void     PacmanScene::PlayerMove(void)
{
	// TO DO PLAYER MOVEMENT //
}

void     PacmanScene::PlayerEatFood(void)
{
	// TO DO ACTION OF PALYER'S EATING //
}

void    PacmanScene::GoshtMove(void)
{
	// TO DO MOVEMENT OF GOSHTS //
	int  d;

	d = rand()%(3) + 1 - 1;
	pacmanMap[gosht1.x][gosht1.y] = ' ';
	if (d == LEFT)
		pacmanMap[gosht1.x + dir.left.x][gosht1.y + dir.left.y] = 'E';
	else if (d == RIGHT)
		pacmanMap[gosht1.x + dir.right.x][gosht1.y + dir.right.y] = 'E';
	else if (d == UP)
		pacmanMap[gosht1.x + dir.up.x][gosht1.y + dir.up.y] = 'E';
	else if (d == DOWN)
		pacmanMap[gosht1.x + dir.down.x][gosht1.y + dir.down.y] = 'E';
}

void    PacmanScene::compute(void)
{
	// TO DO ia of the goshts //
	//srand(time(NULL));
	//GoshtMove();
}

void    PacmanScene::createMap()
{
	pacmanMap.resize(WIDTH, std::vector<char>(HEIGHT));
	pacmanMap = {{'\n','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*'},
		     {'\n','*','o','o','*','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','*','o','o','*'},
		     {'\n','*','o','o','*','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','*','o','o','*'},
		     {'\n','*','o','o','*','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','*','o','o','*'},
		     {'\n','*','o','o','*','o','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','o','*','o','o','*'},
		     {'\n','*','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','*'},
		     {'\n','*','o','*','*','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','*','*','o','*'},
		     {'\n','*','o','*','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','*','o','*'},
		     {'\n','*','o','*','o','o','*','*','o','*','*','*',' ','G',' ','*','*','*','o','o','*','*','o','*','o','*'},
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

std::vector<std::vector<char>>   PacmanScene::getMap() const
{
	return (pacmanMap);
}

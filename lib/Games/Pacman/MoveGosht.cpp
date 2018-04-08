//
// Created by j-f on 08/04/18.
//

#include "PacmanScene.hpp"

void    PacmanScene::GoshtMove3(void)
{
    int 	dir;

    srand(time(NULL));
    dir = rand()%3;
    if (dir == 0) {
        if (pacmanMap[gosht3.x][gosht3.y - 1] == 'o')
            pacmanMap[gosht3.x][gosht3.y] = 'o';
        else if (pacmanMap[gosht3.x][gosht3.y - 1] == 'G') {
            PacmanText.insert({"lost", {"Game Over", ' ', false, true, {300, 280}}});
            loose = true;
        }
        else if (pacmanMap[gosht3.x][gosht3.y - 1] == ' ')
            pacmanMap[gosht3.x][gosht3.y] = ' ';
        else if (pacmanMap[gosht3.x][gosht3.y - 1] == 'B')
            pacmanMap[gosht3.x][gosht3.y] = 'B';
        else if (pacmanMap[gosht3.x][gosht3.y - 1] == '*')
            goto choosed_direction;
        PacmanTexture["gosht3"].position.x -= WIDTH_TEXTURE;
        gosht3.y = gosht3.y - 1;
        pacmanMap[gosht3.x][gosht3.y] = 'C';
    }
    else if (dir == 1) {
        if (pacmanMap[gosht3.x][gosht3.y + 1] == 'o')
            pacmanMap[gosht3.x][gosht3.y] = 'o';
        else if (pacmanMap[gosht3.x][gosht3.y + 1] == ' ')
            pacmanMap[gosht3.x][gosht3.y] = ' ';
        else if (pacmanMap[gosht3.x][gosht3.y + 1] == 'B')
            pacmanMap[gosht3.x][gosht3.y] = 'B';
        else if (pacmanMap[gosht3.x][gosht3.y + 1] == 'G') {
            PacmanText.insert({"lost", {"Game Over", ' ', false, true, {300, 280}}});
            loose = true;
        }
        else if (pacmanMap[gosht3.x][gosht3.y + 1] == '*')
            goto choosed_direction;
        PacmanTexture["gosht3"].position.x += WIDTH_TEXTURE;
        gosht3.y = gosht3.y + 1;
        pacmanMap[gosht3.x][gosht3.y] = 'C';
    }
    else if (dir == 2) {
        if (pacmanMap[gosht3.x - 1][gosht3.y] == 'o')
            pacmanMap[gosht3.x][gosht3.y] = 'o';
        else if (pacmanMap[gosht3.x - 1][gosht3.y] == ' ')
            pacmanMap[gosht3.x][gosht3.y] = ' ';
        else if (pacmanMap[gosht3.x - 1][gosht3.y] == 'B')
            pacmanMap[gosht3.x][gosht3.y] = 'B';
        else if (pacmanMap[gosht3.x - 1][gosht3.y] == 'G') {
            PacmanText.insert({"lost", {"Game Over", ' ', false, true, {300, 280}}});
            loose = true;
        }
        else if (pacmanMap[gosht3.x - 1][gosht3.y] == '*')
            goto choosed_direction;
        PacmanTexture["gosht3"].position.y -= HEIGHT_TEXTURE;
        gosht3.x = gosht3.x - 1;
        pacmanMap[gosht3.x][gosht3.y] = 'C';
    }
    else if (dir == 3) {
        if (pacmanMap[gosht3.x + 1][gosht3.y] == 'o')
            pacmanMap[gosht3.x][gosht3.y] = 'o';
        else if (pacmanMap[gosht3.x + 1][gosht3.y] == ' ')
            pacmanMap[gosht3.x][gosht3.y] = ' ';
        else if (pacmanMap[gosht3.x + 1][gosht3.y] == 'B')
            pacmanMap[gosht3.x][gosht3.y] = 'B';
        else if (pacmanMap[gosht3.x + 1][gosht3.y] == 'G') {
            PacmanText.insert({"lost", {"Game Over", ' ', false, true, {300, 280}}});
            loose = true;
        }
        else if (pacmanMap[gosht3.x + 1][gosht3.y] == '*')
            goto choosed_direction;
        PacmanTexture["gosht3"].position.y += HEIGHT_TEXTURE;
        gosht3.x = gosht3.x + 1;
        pacmanMap[gosht3.x][gosht3.y] = 'C';
    }
    choosed_direction:
        dir = rand()%(3);
}

void    PacmanScene::GoshtMove2(void)
{
    int 	dir;

    srand(time(NULL));
    dir = rand()%3;
    if (dir == 0) {
        if (pacmanMap[gosht2.x][gosht2.y - 1] == 'o')
            pacmanMap[gosht2.x][gosht2.y] = 'o';
        else if (pacmanMap[gosht2.x][gosht2.y - 1] == ' ')
            pacmanMap[gosht2.x][gosht2.y] = ' ';
        else if (pacmanMap[gosht2.x][gosht2.y - 1] == 'C')
            pacmanMap[gosht2.x][gosht2.y] = 'C';
        else if (pacmanMap[gosht2.x][gosht2.y - 1] == 'G') {
            PacmanText.insert({"lost", {"Game Over", ' ', false, true, {300, 280}}});
            loose = true;
        }
        else if (pacmanMap[gosht2.x][gosht2.y - 1] == '*')
            goto choosed_direction;
        PacmanTexture["gosht2"].position.x -= WIDTH_TEXTURE;
        gosht2.y = gosht2.y - 1;
        pacmanMap[gosht2.x][gosht2.y] = 'B';
    }
    else if (dir == 1) {
        if (pacmanMap[gosht2.x][gosht2.y + 1] == 'o')
            pacmanMap[gosht2.x][gosht2.y] = 'o';
        else if (pacmanMap[gosht2.x][gosht2.y + 1] == ' ')
            pacmanMap[gosht2.x][gosht2.y] = ' ';
        else if (pacmanMap[gosht2.x][gosht2.y + 1] == 'C')
            pacmanMap[gosht2.x][gosht2.y] = 'C';
        else if (pacmanMap[gosht2.x][gosht2.y + 1] == 'G') {
            PacmanText.insert({"lost", {"Game Over", ' ', false, true, {300, 280}}});
            loose = true;
        }
        else if (pacmanMap[gosht2.x][gosht2.y + 1] == '*')
            goto choosed_direction;
        PacmanTexture["gosht2"].position.x += WIDTH_TEXTURE;
        gosht2.y = gosht2.y + 1;
        pacmanMap[gosht2.x][gosht2.y] = 'B';
    }
    else if (dir == 2) {
        if (pacmanMap[gosht2.x - 1][gosht2.y] == 'o')
            pacmanMap[gosht2.x][gosht2.y] = 'o';
        else if (pacmanMap[gosht2.x - 1][gosht2.y] == ' ')
            pacmanMap[gosht2.x][gosht2.y] = ' ';
        else if (pacmanMap[gosht2.x - 1][gosht2.y] == 'C')
            pacmanMap[gosht2.x][gosht2.y] = 'C';
        else if (pacmanMap[gosht2.x - 1][gosht2.y] == 'G') {
            PacmanText.insert({"lost", {"Game Over", ' ', false, true, {300, 280}}});
            loose = true;
        }
        else if (pacmanMap[gosht2.x - 1][gosht2.y] == '*')
            goto choosed_direction;
        PacmanTexture["gosht2"].position.y -= HEIGHT_TEXTURE;
        gosht2.x = gosht2.x - 1;
        pacmanMap[gosht2.x][gosht2.y] = 'B';
    }
    else if (dir == 3) {
        if (pacmanMap[gosht2.x + 1][gosht2.y] == 'o')
            pacmanMap[gosht2.x][gosht2.y] = 'o';
        else if (pacmanMap[gosht2.x + 1][gosht2.y] == ' ')
            pacmanMap[gosht2.x][gosht2.y] = ' ';
        else if (pacmanMap[gosht2.x + 1][gosht2.y] == 'C')
            pacmanMap[gosht2.x][gosht2.y] = 'C';
        else if (pacmanMap[gosht2.x + 1][gosht2.y] == 'G') {
            PacmanText.insert({"lost", {"Game Over", ' ', false, true, {300, 280}}});
            loose = true;
        }
        else if (pacmanMap[gosht2.x + 1][gosht2.y] == '*')
            goto choosed_direction;
        PacmanTexture["gosht2"].position.y += HEIGHT_TEXTURE;
        gosht2.x = gosht2.x + 1;
        pacmanMap[gosht2.x][gosht2.y] = 'B';
    }
    choosed_direction:
        dir = rand()%(3);
}
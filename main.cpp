#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

int i, j, height = 20, width = 20;
int gameover, score;
int x, y, fruitx, fruity, flag;
int tailX[100], tailY[100]; // Arrays para almacenar la posición de la cola de la serpiente
int nTail = 0; // Longitud inicial de la serpiente

void setup()
{
    gameover = 0;

    x = height / 2;
    y = width / 2;

    while (1) {
        fruitx = rand() % 20;
        if (fruitx != 0)
            break;
    }

    while (1) {
        fruity = rand() % 20;
        if (fruity != 0)
            break;
    }

    score = 0;
}

void draw()
{
    system("cls");
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
                printf("#");
            else {
                int isTail = 0;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == i && tailY[k] == j) {
                        printf("0");
                        isTail = 1;
                    }
                }
                if (!isTail) {
                    if (i == x && j == y)
                        printf("0");
                    else if (i == fruitx && j == fruity)
                        printf("*");
                    else
                        printf(" ");
                }
            }
        }
        printf("\n");
    }

    printf("score = %d", score);
    printf("\n");
    printf("press X to quit the game");
}

void input()
{
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            flag = 1;
            break;
        case 's':
            flag = 2;
            break;
        case 'd':
            flag = 3;
            break;
        case 'w':
            flag = 4;
            break;
        case 'x':
            gameover = 1;
            break;
        }
    }
}

void logic()
{
    Sleep(100); // Sleep for 100 milliseconds

    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (flag) {
    case 1:
        y--;
        break;
    case 2:
        x++;
        break;
    case 3:
        y++;
        break;
    case 4:
        x--;
        break;
    default:
        break;
    }

    if (x < 0 || x > height - 1 || y < 0 || y > width - 1)
        gameover = 1;

    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y)
            gameover = 1;
    }

    if (x == fruitx && y == fruity) {
        while (1) {
            fruitx = rand() % 20;
            if (fruitx != 0)
                break;
        }

        while (1) {
            fruity = rand() % 20;
            if (fruity != 0)
                break;
        }

        score += 10;
        nTail++; // Aumentar la longitud de la serpiente
    }
}

int main()
{
    setup();

    while (!gameover) {
        draw();
        input();
        logic();
    }

    return 0;
}

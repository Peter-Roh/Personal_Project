#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define PAUSE 112
#define ESC 27
#define MAP_X 30
#define MAP_Y 20

void title(void);
void reset(void);
void draw_map(void);
void move(int dir);
void pause(void);
void game_over(void);
void food(void);
void check_food(void);
void check_level_up(void);
void item(void);

int x[100], y[100];
int food_x, food_y;
int item_x, item_y;
int length;
int speed;
int level = 1;
int score;
int cnt = 0;
int cnt2 = 0;
int best_score = 0;
int last_score = 0;
int dir;
int key;
int level_up_on = 0;

void gotoxy(int x, int y, char* s)
{
    COORD pos = {2*x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    printf("%s", s);
}

typedef enum {NOCURSOR, SOLIDCURSOR, NORMALCURSOR} CURSOR_TYPE;

void setcursortype(CURSOR_TYPE c)
{
     CONSOLE_CURSOR_INFO CurInfo;
 
     switch (c) {
     case NOCURSOR:
          CurInfo.dwSize = 1;
          CurInfo.bVisible = FALSE;
          break;
     case SOLIDCURSOR:
          CurInfo.dwSize = 100;
          CurInfo.bVisible = TRUE;
          break;
     case NORMALCURSOR:
          CurInfo.dwSize = 20;
          CurInfo.bVisible = TRUE;
          break;
     }

     SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&CurInfo);
}

void title(void)//첫 화면
{
    int i, j;

    while (kbhit()) getch();

    draw_map();
    for(i = 3; i < MAP_Y + 1; i++)
    {
        for(j = 4; j < MAP_X + 2; j++) gotoxy(j,i,"  ");
    }

    gotoxy((MAP_X/2) - 4, 7, "+--------------------------+");
    gotoxy((MAP_X/2) - 4, 8, "|        S N A K E         |");
    gotoxy((MAP_X/2) - 4, 9, "+--------------------------+");

    gotoxy((MAP_X/2) - 4, 11, " < PRESS ANY KEY TO START > ");

    gotoxy((MAP_X/2) - 4, 13, "   ◇ ←,→,↑,↓ : Move    ");
    gotoxy((MAP_X/2) - 4, 14, "   ◇ P : Pause             ");  
    gotoxy((MAP_X/2) - 4, 15, "   ◇ ESC : Quit              ");

    while(1)
    {
        if(kbhit())
        {
            key = getch();
            if(key == ESC) exit(0);
            else break;
        }

        gotoxy((MAP_X/2) - 4, 11, " < PRESS ANY KEY TO START > ");
        Sleep(400);
        gotoxy((MAP_X/2) - 4, 11, "                            ");
        Sleep(400);
    }
    reset();
}

void reset(void)//초기화
{
    int i;
    system("cls");
    draw_map();
    while (kbhit()) getch();
    
    dir = LEFT;
    speed = 100;
    length = 5;
    score = 0;
    level = 1;
    level_up_on = 0;
    cnt = -1;
    cnt2 = 0;
    for(i = 0; i < length; i++)
    {
        x[i] = MAP_X / 2 + i;
        y[i] = MAP_Y / 2;
        gotoxy(x[i] + 3, y[i] + 2, "ㅇ");
    }
    gotoxy(x[0] + 3, y[0] + 2,"◇");
    food();
}

void draw_map(void)//테두리 그리기
{
    int i, j;
    for(i = 0; i < MAP_X; i++)
    {
        gotoxy(i + 3, 2, "■");
    }
    for(i = 3; i < MAP_Y + 1; i++)
    {
        gotoxy(3, i, "■");
        gotoxy(MAP_X + 2, i, "■");
    }
    for(i = 0; i < MAP_X; i++)
    {
        gotoxy(i + 3, MAP_Y + 1, "■");
    }
}

void move(int dir)//뱀 머리 이동
{
    int i;

    if(x[0] == food_x && y[0] == food_y)
    {
        score += 10;
        food();

        length++;
        x[length - 1] = x[length - 2];
        y[length - 1] = y[length - 2];

        if(cnt2 == 3 && length > 6) item();
    }
    if(x[0] == item_x && y[0] == item_y)
    {
        gotoxy(x[length - 1] + 3, y[length - 1] + 2, "  ");
        gotoxy(x[length - 2] + 3, y[length - 2] + 2, "  ");
        gotoxy(x[length - 3] + 3, y[length - 3] + 2, "  ");

        length -= 3;
        cnt2 = 0;
    }
    if(x[0] == 0 || x[0] == MAP_X - 1 || y[0] == 0 || y[0] == MAP_Y - 1)
    {
        game_over();
        return;
    }
    for(i = 1; i < length; i++)
    {
        if(x[0] == x[i] && y[0] == y[i])
        {
            game_over();
            return;
        }
    }

    gotoxy(x[length - 1] + 3, y[length - 1] + 2, "  ");
    for(i = length - 1; i > 0; i--)
    {
        x[i] = x[i - 1];
        y[i] = y[i - 1];
    }
    gotoxy(x[0] + 3, y[0] + 2, "ㅇ");
    if(dir == LEFT) --x[0];
    if(dir == RIGHT) ++x[0];
    if(dir == UP) --y[0];
    if(dir == DOWN) ++y[0];
    gotoxy(x[i] + 3, y[i] + 2, "◇");
}

void pause(void)//일시정지
{
    while(1)
    {
        if(key == PAUSE)
        {
            gotoxy((MAP_X/2) - 6, 2, "< PAUSE : PRESS ANY KEY TO RESUME > ");
            Sleep(400);
            gotoxy((MAP_X/2) - 6, 2,"                                    ");
            Sleep(400);
        }
        else
        {
            draw_map();
            return;
        }
        if(kbhit())
        {
                do
                {
                    key=getch();
                }
                while(key == 224);
        }
    }
}

void game_over(void)//게임 오버
{
    gotoxy((MAP_X/2) - 3, 7, "+----------------------+");
    gotoxy((MAP_X/2) - 3, 8, "|      GAME OVER..     |");
    gotoxy((MAP_X/2) - 3, 9, "+----------------------+");
    gotoxy((MAP_X/2) - 3, 10, " YOUR SCORE : ");
    printf("%d", last_score = score);

    gotoxy((MAP_X/2) - 4, 14, " Press any keys to restart.. ");

    if(score > best_score)
    {
        best_score = score;
        gotoxy((MAP_X/2) - 1, 12, "☆ BEST SCORE ☆");
    }
    Sleep(500);
        while (kbhit()) getch();
    key = getch();
    title();
}

void food(void)//먹이 생성
{
    int i;
    int food_crush_on = 0;
    int r = 0;

    gotoxy(3, MAP_Y + 2, " YOUR SCORE: ");
    printf("%3d, LAST SCORE: %3d, BEST SCORE: %3d", score, last_score, best_score);

    while(1)
    {
        food_crush_on = 0;
        srand((unsigned)time(NULL) + r);
        food_x = (rand() % (MAP_X - 2)) + 1;
        food_y = (rand() % (MAP_Y - 2)) + 1;

        for(i = 0; i < length; i++)
        {
            if(food_x == x[i] && food_y == y[i])
            {
                food_crush_on = 1;
                r++;
                break;
            }
        }

        if(food_crush_on == 1) continue;

        gotoxy(food_x + 3, food_y + 2, "☆");
        cnt++;
        cnt2++;
        check_food();
        break;
    }
}

void item(void)//뱀 길이 줄여주는 아이템
{
    int i;
    int item_crush_on = 0;
    int r = 0;

    while(1)
    {
        item_crush_on = 0;
        srand((unsigned)time(NULL) + r);
        item_x = (rand() % (MAP_X - 2)) + 1;
        item_y = (rand() % (MAP_Y - 2)) + 1;

        for(i = 0; i < length; i++)
        {
            if(item_x == x[i] && item_y == y[i])
            {
                item_crush_on = 1;
                r++;
                break;
            }
            if(food_x == item_x && food_y == item_y)
            {
                item_crush_on = 1;
                r++;
                break;
            }
        }

        if(item_crush_on == 1) continue;

        gotoxy(item_x + 3, item_y + 2, "♡");
        break;
    }
}

void check_food(void)//속도 조절
{
    if(cnt == level * 5)
    {
        level++;
        level_up_on = 1;
    }

    switch(level)
    {
        case 2:
            speed -= 4;
            break;
        case 3:
            speed -= 4;
            break;
        case 4:
            speed -= 4;
            break;
        case 5:
            speed -= 3;
            break;
        case 6:
            speed -= 3;
            break;
        case 7:
            speed -= 3;
            break;
        case 8:
            speed -= 2;
            break;
        case 9:
            speed -= 2;
            break;
        case 10:
            speed -= 2;
            break;
    }
}

void check_level_up(void)//레벨 업 효과
{
    if(level_up_on == 1)
    {
        gotoxy((MAP_X) + 8, 7, "☆LEVEL UP!☆");
        gotoxy((MAP_X) + 8, 8, "☆SPEED UP!☆");
        Sleep(350);
        gotoxy((MAP_X) + 8, 7, "            ");
        gotoxy((MAP_X) + 8, 8, "            ");
    }

    level_up_on = 0;
}

int main()
{
    setcursortype(NOCURSOR);
    title();

    while(1)
    {
        if(kbhit()) do{key = getch();} while(key == 224);
        Sleep(speed);

        switch(key)
        {
            case LEFT:
            case RIGHT:
            case UP:
            case DOWN:
                if((dir == LEFT && key != RIGHT) || (dir == RIGHT && key != LEFT) || (dir == UP && key != DOWN) || (dir == DOWN && key != UP))
                    dir = key;
                key = 0;
            break;
            case PAUSE:
                pause();
            break;
            case ESC:
                exit(0);
        }
        move(dir);
        gotoxy(MAP_X + 3, 7, " LEVEL : "); printf("%d", level);
        gotoxy(MAP_X + 3, 8, " GOAL  : "); printf("%d", level * 5);
        check_level_up();
    }
}
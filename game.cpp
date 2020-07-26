#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <ctime>
#include "wall.h"
#include "snake.h"
#include "food.h"
#include <conio.h>
#include <Windows.h>

using namespace std;

void gotoxy(HANDLE hOut, int x, int y)
{
	COORD pos;
	pos.X = x;             //横坐标
	pos.Y = y;            //纵坐标
	SetConsoleCursorPosition(hOut, pos);
}
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//定义显示器句柄变量

int main() {
	//添加随机数种子
	srand((unsigned int)time(NULL));

	//是否死亡提示
	bool isDead = false;

	//
	char preKey = NULL;

	Wall wall;
	wall.initWall();
	wall.drawWall();

	Food food(wall);
	food.setFood();

	Snake snake(wall, food);
	snake.initSnake();

// 	snake.move('w');
// 	snake.move('w');
// 	snake.move('a');


	gotoxy(hOut, 0, Wall::ROW);
	cout << "得分：" << snake.getScore() << "分" << endl;


	//接受用户的输入
	while (!isDead) {
			
		char key = _getch();

		//判断 如果是第一次按了 左键 才不能激活游戏
		//判断 上一次 移动方向
		if (preKey == NULL && key == snake.LEFT) {
			continue;
		}

		do {
			if (key == snake.UP || key == snake.DOWN || key == snake.LEFT || key == snake.RIGHT) {

				//判断本次的按键是否与上次冲突
				if (key == snake.LEFT && preKey == snake.RIGHT ||
					key == snake.RIGHT && preKey == snake.LEFT ||
					key == snake.UP && preKey == snake.DOWN ||
					key == snake.DOWN && preKey == snake.UP) {
					key = preKey;
				}
				else {
					preKey = key;
				}

				if (snake.move(key) == true) {
					//移动成功 代码
					//system("cls");
					//wall.drawWall();
					gotoxy(hOut, 0, Wall::ROW);

					cout << "得分：" << snake.getScore() << "分" << endl;
					Sleep(snake.sleepTime());
				}
				else {
					isDead = true;
					break;
				}
			}
			else {
				key = preKey;  //强制将错误按键变为上一次移动的方向
			}
		} while (!_kbhit()); //没有键盘输入的时候返回0。
	}


	////测试
	//wall.setWall(5, 4, '=');
	//wall.setWall(5, 5, '=');
	//wall.setWall(5, 6, '@');


	//cout << wall.getWall(0, 0) << endl;
	//cout << wall.getWall(5, 4) << endl;
	//cout << wall.getWall(5, 6) << endl;
	//cout << wall.getWall(1, 1) << endl;

	system("pause");
	return EXIT_SUCCESS;
}
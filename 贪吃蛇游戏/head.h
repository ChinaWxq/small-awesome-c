#pragma once
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include <stdlib.h>
#include <conio.h>

#define U 1
#define D 2
#define L 3
#define R 4	//蛇的状态

typedef struct snake
{
	int x;//一个结点的xy坐标
	int y;
	struct snake* next;//蛇身下一个结点
}Snake,*SnakeLink;

//全局变量
int g_score = 0, g_add = 10;//总得分和吃食物的得分
int g_highScore = 0;//最高分
int g_status, g_sleepTime = 200;//蛇前进的状态和运行时间间隔
SnakeLink g_head, g_food;//蛇头指针和食物指针
SnakeLink g_q;//遍历蛇用的指针
int g_endGamesStatus = 0;//游戏结束的情况，1：撞墙，2：咬到自己，3：主动退出
HANDLE hOut;//控制台句柄


/*******函  数  声  明 *******/
void gotoxy(int x, int y);   //设置光标位置
int color(int c);           //更改文字颜色
void printSnake();          //字符画---蛇
void welcomeToGame();       //开始界面
void createMap();           //绘制地图
void scoreAndTips();		//游戏界面右侧的得分和小提示
void initSnake();           //初始化蛇身，画蛇身
void createFood();          //创建并随机出现食物
int biteSelf();             //判断是否咬到了自己
void crossWall();       //设置蛇撞墙的情况
void speedUp();				//加速
void speedDown();			//减速
void snakeMove();           //控制蛇前进方向
void keyBoardControl();     //控制键盘按键
void lostDraw();            //游戏结束界面
void endGame();             //游戏结束
void choose();				//游戏失败之后的选择
void file_out();            //在文件中读取最高分
void file_in();            	//储存最高分进文件
void explation();           //游戏说明
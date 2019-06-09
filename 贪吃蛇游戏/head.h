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
#define R 4	//�ߵ�״̬

typedef struct snake
{
	int x;//һ������xy����
	int y;
	struct snake* next;//������һ�����
}Snake,*SnakeLink;

//ȫ�ֱ���
int g_score = 0, g_add = 10;//�ܵ÷ֺͳ�ʳ��ĵ÷�
int g_highScore = 0;//��߷�
int g_status, g_sleepTime = 200;//��ǰ����״̬������ʱ����
SnakeLink g_head, g_food;//��ͷָ���ʳ��ָ��
SnakeLink g_q;//�������õ�ָ��
int g_endGamesStatus = 0;//��Ϸ�����������1��ײǽ��2��ҧ���Լ���3�������˳�
HANDLE hOut;//����̨���


/*******��  ��  ��  �� *******/
void gotoxy(int x, int y);   //���ù��λ��
int color(int c);           //����������ɫ
void printSnake();          //�ַ���---��
void welcomeToGame();       //��ʼ����
void createMap();           //���Ƶ�ͼ
void scoreAndTips();		//��Ϸ�����Ҳ�ĵ÷ֺ�С��ʾ
void initSnake();           //��ʼ������������
void createFood();          //�������������ʳ��
int biteSelf();             //�ж��Ƿ�ҧ�����Լ�
void crossWall();       //������ײǽ�����
void speedUp();				//����
void speedDown();			//����
void snakeMove();           //������ǰ������
void keyBoardControl();     //���Ƽ��̰���
void lostDraw();            //��Ϸ��������
void endGame();             //��Ϸ����
void choose();				//��Ϸʧ��֮���ѡ��
void file_out();            //���ļ��ж�ȡ��߷�
void file_in();            	//������߷ֽ��ļ�
void explation();           //��Ϸ˵��
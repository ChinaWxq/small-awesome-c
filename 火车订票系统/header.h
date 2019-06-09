#pragma once
#define _CRT_SECURE_NO_WARNINGS 
#pragma warning(disable: 4996)
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

//频繁用到火车表的信息
#define HEADER1 "------------------------------------BOOK TICKET------------------------------------\n"
#define HEADER2 "|   number    |start city|reach city|takeoff time|receive time|price|ticket number|\n"
#define HEADER3 "|-------------|----------|----------|------------|------------|-----|-------------|\n"
#define FORMAT "|%-10s   |%-10s|%-10s|%-10s  |%-10s  |%5d| %5d       |\n"
#define DATA p->data.num,p->data.startcity,p->data.reachcity,p->data.takeofftime,p->data.receivetime,p->data.price,p->data.ticketnum

//火车票信息
struct train
{	
	char num[10];//列车号
	char startcity[10];//出发城市
	char reachcity[10];//达到城市
	char takeofftime[10];//发车时间
	char receivetime[10];//到达时间
	int price;//票价
	int ticketnum;//票数
};

//订票人的信息
struct man
{
	char num[10];//ID
	char name[10];//姓名
	int bookNum;//订的票数
};

//火车票信息链表的结点结构
typedef struct node
{
	struct train data;
	struct node* next;
}TrainNode,*TrainLink;

//订票人链表的结点结构
typedef struct Man
{
	struct man data;
	struct Man* next;
}BookNode,*BookLink;

//全局变量是否保存信息
int saveflag;

//函数定义
void menu();//菜单显示
void TrainInfo(TrainLink trainHeader);//添加火车信息
void searchtrain(TrainLink trainHeader);//查询火车信息
void printHeader();//格式化输出表头
void printData(TrainLink trainNode);//格式化输出表中数据
void SaveTrainInfo(TrainLink trainHeader);//保存火车信息
void SaveBookInfo(BookLink trainHeader);//保存用户信息
void Bookticket(TrainLink trainHeader, BookLink bookHeader);//订票
void Modify(TrainLink trainHeader);//修改信息
void showTrain(TrainLink trainHeader);//显示列车信息
#pragma once
#pragma warning(disable: 4996)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct StudentNode
{
	int number;//学号
	char name[10];//姓名
	int consumption;//消费
	struct StudentNode* next;
}Node, * LinkList;
#define LEN sizeof(Node)//结构体长度

//全局变量
unsigned int g_studentNum;//学生数量
//函数声明
void menu();//目录界面
LinkList creat();//创建链表
LinkList sort(LinkList head);//排序链表
LinkList load();//加载数据
LinkList del(LinkList head);//删除数据
LinkList add(LinkList head);//添加数据
void search(LinkList head);//查找信息
void print(LinkList head);//显示数据
void save(LinkList head);//存储数据

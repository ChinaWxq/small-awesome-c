#pragma once
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

//通讯录信息
struct Info
{
	char name[15];//姓名
	char city[15];//城市
	char province[15];//省
	char state[10];//国家
	char tel[15];//电话
};
//通讯录链表结构
typedef struct node
{
	struct Info data;
	struct node* next;
}Node, *LinkNode;

//函数信息
void stringInput(char* desStr, int lens, char* notice);//自定义字符串输入检测
void enter(LinkNode header);//通讯录信息录入函数
void del(LinkNode header);//通讯录信息删除函数
void search(LinkNode header);//查询函数
void list(LinkNode header);//通讯录列表函数
void display(LinkNode p);//显示信息
void save(LinkNode header);//数据保存函数
void load(LinkNode header);//数据读取函数
int menu_select();//功能列表函数
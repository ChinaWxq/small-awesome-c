#pragma once
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <dos.h>

#define LEN sizeof(struct Student)
#define FORMAT "%-8d%-15s%-12.1lf%-12.1lf%-12.1lf%-12.1lf\n"
#define DATA stu[i].num,stu[i].name,stu[i].elec,stu[i].expe,stu[i].requ,stu[i].sum

typedef struct Student
{
	int num;//学号
	char name[15];//姓名
	double elec;//选修课
	double expe;//实验课
	double requ;//必修课
	double sum;//总分
}Student;

//函数声明
Student stu[50];
void in();//录入学生信息
void show();//展示学生信息
void order();//按总分排序
void del();//删除学生信息
void modify();//修改学生信息
void menu();//主菜单
void insert();//插入学生信息
void total();//计算总人数
void search();//查找学生信息
#pragma once
#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <dos.h>

#define LEN sizeof(struct commdity)
#define FORMAT "%-8d%-15s%-12.1lf%-12.1lf%-12.1lf\n"
#define DATA comm[i].num,comm[i].name,comm[i].price,comm[i].count,comm[i].total


struct commdity/*������Ʒ��Ϣ�ṹ��*/
{
	int num;/*���*/
	char name[15];/*��Ʒ����*/
	double price;/*����*/
	double count;/*����*/
	double total;/*�ܽ��*/
};

struct commdity comm[50];/*����ṹ������*/

void in();/*¼����Ʒ��Ϣ*/
void show();/*��ʾ��Ʒ��Ϣ*/
void order();/*���ܽ������*/
void del();/*ɾ����Ʒ��Ϣ*/
void modify();/*�޸���ƷϢ*/
void menu();/*���˵�*/
void insert();/*������Ʒ��Ϣ*/
void total();/*��������Ʒ��*/
void search();/*������Ʒ��Ϣ*/


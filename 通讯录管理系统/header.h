#pragma once
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

//ͨѶ¼��Ϣ
struct Info
{
	char name[15];//����
	char city[15];//����
	char province[15];//ʡ
	char state[10];//����
	char tel[15];//�绰
};
//ͨѶ¼����ṹ
typedef struct node
{
	struct Info data;
	struct node* next;
}Node, *LinkNode;

//������Ϣ
void stringInput(char* desStr, int lens, char* notice);//�Զ����ַ���������
void enter(LinkNode header);//ͨѶ¼��Ϣ¼�뺯��
void del(LinkNode header);//ͨѶ¼��Ϣɾ������
void search(LinkNode header);//��ѯ����
void list(LinkNode header);//ͨѶ¼�б���
void display(LinkNode p);//��ʾ��Ϣ
void save(LinkNode header);//���ݱ��溯��
void load(LinkNode header);//���ݶ�ȡ����
int menu_select();//�����б���
#pragma once
#pragma warning(disable: 4996)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct StudentNode
{
	int number;//ѧ��
	char name[10];//����
	int consumption;//����
	struct StudentNode* next;
}Node, * LinkList;
#define LEN sizeof(Node)//�ṹ�峤��

//ȫ�ֱ���
unsigned int g_studentNum;//ѧ������
//��������
void menu();//Ŀ¼����
LinkList creat();//��������
LinkList sort(LinkList head);//��������
LinkList load();//��������
LinkList del(LinkList head);//ɾ������
LinkList add(LinkList head);//�������
void search(LinkList head);//������Ϣ
void print(LinkList head);//��ʾ����
void save(LinkList head);//�洢����

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
	int num;//ѧ��
	char name[15];//����
	double elec;//ѡ�޿�
	double expe;//ʵ���
	double requ;//���޿�
	double sum;//�ܷ�
}Student;

//��������
Student stu[50];
void in();//¼��ѧ����Ϣ
void show();//չʾѧ����Ϣ
void order();//���ܷ�����
void del();//ɾ��ѧ����Ϣ
void modify();//�޸�ѧ����Ϣ
void menu();//���˵�
void insert();//����ѧ����Ϣ
void total();//����������
void search();//����ѧ����Ϣ
#pragma once

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>
#include <mysql.h>
#pragma warning(disable: 4996)
#pragma commnet(lib,"libmysql.lib")//���ÿ�

//�������ݿ���ز�������
MYSQL mysql;//����mysql����
MYSQL_RES* result;//������������
MYSQL_ROW row;//�����б���

char ch[2];//�����ַ�����

//������Ϣ
void showAll();//��ʾ����ͼ����Ϣ
void addBook();//���ͼ����Ϣ
void modifyBook();//�޸�ͼ����Ϣ
void deleteBook();//ɾ��ͼ����Ϣ
void queryBook();//��ѯͼ����Ϣ
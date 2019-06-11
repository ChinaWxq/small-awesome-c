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


struct commdity/*定义商品信息结构体*/
{
	int num;/*编号*/
	char name[15];/*商品名称*/
	double price;/*单价*/
	double count;/*数量*/
	double total;/*总金额*/
};

struct commdity comm[50];/*定义结构体数组*/

void in();/*录入商品信息*/
void show();/*显示商品信息*/
void order();/*按总金额排序*/
void del();/*删除商品信息*/
void modify();/*修改商品息*/
void menu();/*主菜单*/
void insert();/*插入商品信息*/
void total();/*计算总商品数*/
void search();/*查找商品信息*/


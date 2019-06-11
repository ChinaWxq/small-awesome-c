#pragma once

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>
#include <mysql.h>
#pragma warning(disable: 4996)
#pragma commnet(lib,"libmysql.lib")//引用库

//定义数据库相关操作变量
MYSQL mysql;//定义mysql对象
MYSQL_RES* result;//定义结果集变量
MYSQL_ROW row;//定义行变量

char ch[2];//定义字符变量

//函数信息
void showAll();//显示所有图书信息
void addBook();//添加图书信息
void modifyBook();//修改图书信息
void deleteBook();//删除图书信息
void queryBook();//查询图书信息
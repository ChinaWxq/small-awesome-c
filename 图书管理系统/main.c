#include "head.h"

//MySQL
//创建数据库:db_books
//创建数据表:tb_book

/*显示菜单*/
void showMenu()
{
	system("cls");
	printf("\n\n\n\n\n");
	printf("\t╔══════════════════════════════════════════════════════╗\n");
	printf("\t║            Welcome To Lemon Books System             ║\n");
	printf("\t╠══════════════════════════════════════════════════════╣\n");
	printf("\t║\t\t 1 - 显示所有图书信息                  ║\n");
	printf("\t║\t\t 2 - 添加图书信息                      ║\n");
	printf("\t║\t\t 3 - 修改图书信息                      ║\n");
	printf("\t║\t\t 4 - 删除图书信息                      ║\n");
	printf("\t║\t\t 5 - 查询图书信息                      ║\n");
	printf("\t║\t\t 6 - 退出                              ║\n");
	printf("\t╚══════════════════════════════════════════════════════╝\n");
	printf("\n              ENTER YOUR CHOICE(1-6):");

}

int main()
{
	int n;
	mysql_init(&mysql);//初始化mysql结构
	showMenu();
	scanf("%d", &n);
	while (n)
	{
		switch (n)
		{
		case 1:
			showAll();//显示信息
			break;
		case 2:
			addBook();//增加图书信息
			break;
		case 3:
			modifyBook();//修改图书信息
			break;
		case 4:
			deleteBook();//删除图书信息
			break;
		case 5:
			queryBook();//查询图书信息
			break;
		case 6:
			exit(0);//退出
			break;
		default:
			break;
		}
		showMenu();
		scanf("%d", &n);
	}
}

void showAll()
{
	if (!mysql_real_connect(&mysql, "localhost", "root", "root", "db_books", 0, NULL, 0))//连接MySQL服务器
	{
		printf("不能连接数据库!\n");
	}
	else
	{
		if (mysql_query(&mysql, "select * from tb_book"))//查询所有记录
		{
			printf("查询数据表失败!\n");
		}
		else
		{
			result = mysql_store_result(&mysql);//获取结果集
			if (mysql_num_rows(result) != NULL)
			{  //有记录的情况,只有有记录取数据才有意义
				printf("\t ════════════════════════════════════════════════ \n");
				printf("\t                 显 示 所 有 图 书 信 息                  \n");
				printf("\t ════════════════════════════════════════════════ \n");
				printf("\t  图书编号       图书名         作者        出版社      \n");
				printf("\t -------------------------------------------------\n");
				while ((row = mysql_fetch_row(result)))
				{   //取出结果集中记录
					printf("\t     %s             %s            %s         %s   \n", row[0], row[1], row[2], row[3]);  //输出这行记录
				}
				printf("\t ════════════════════════════════════════════════ \n");
			}
			else
			{
				printf("没有记录信息 !\n");
			}
			mysql_free_result(result);//释放结果集
		}
		mysql_close(&mysql);//释放服务器连接
	}
	printf("按任意键返回！\n");
	getch();
}

void addBook()
{
	int rowcount;//结果集的行数
	char id[10];
	id[0] = '\0';
	char bookname[50];
	bookname[0] = '\0';
	char author[50];
	author[0] = '\0';
	char bookconcern[100];
	bookconcern[0] = '\0';
	char *sql;
	char dest[1000];
	dest[0] = '\0';
	if (!mysql_real_connect(&mysql, "localhost", "root", "root", "db_books", 0, NULL, 0))//连接服务器
	{
		printf("不能连接到数据库!\n");
	}
	else
	{
		/*数据库连接成功，插入数据*/
		printf("\t ════════════════════════════════════════════════ \n");
		printf("\t                     添 加 图 书 信 息                    \n");
		printf("\t ════════════════════════════════════════════════ \n");
		if (mysql_query(&mysql, "select * from tb_book"))
		{   //如果查询失败
			printf("\n\t 查询 tb_book 数据表失败!\n");
		}
		else
		{
			result = mysql_store_result(&mysql);//获取结果集
			rowcount = mysql_num_rows(result);//获取结果集的行数
			row = mysql_fetch_row(result);//获取结果集的行
			printf("\tID：");
			scanf("%s", &id);
			if (mysql_num_rows(result) != NULL)
			{
				do
				{
					if (strcmp(id, row[0]) == 0)
					{
						printf("记录已存在，按任意键结束!\n");
						getch();
						mysql_free_result(result);//释放结果集
						mysql_close(&mysql);//关闭数据库
						return;
					}
				} while (row = mysql_fetch_row(result));//获取下一条行数据
			}
			printf("\t图书名：");
			scanf("%s", &bookname);
			sql = "insert into tb_book (ID,bookname,author,bookconcern) values(";
			strcat(dest, sql);
			strcat(dest, "'");
			strcat(dest, id);
			strcat(dest, "','");
			strcat(dest, bookname);
			printf("\t作者：");
			scanf("%s", &author);
			strcat(dest, "','");
			strcat(dest, author);
			printf("\t出版社：");
			scanf("%s", &bookconcern);
			strcat(dest, "','");
			strcat(dest, bookconcern);
			strcat(dest, "')");
			if (mysql_query(&mysql, dest) != 0)//插入
				printf("不能插入该记录!");
			else
				printf("插入成功!\n");
			mysql_free_result(result);
		}
		mysql_close(&mysql);
	}
	printf("按任意键返回！\n");
	getch();
}

void modifyBook()
{
	char id[10];	
	id[0] = '\0';
	char* sql;
	char dest[100];
	dest[0] = '\0';
	char dest1[100];
	dest1[0] = '\0';
	char bookname[50];
	bookname[0] = '\0';
	char author[50];
	author[0] = '\0';
	char bookconcern[100];
	bookconcern[0] = '\0';
	if (!mysql_real_connect(&mysql, "localhost", "root", "root", "db_books", 0, NULL, 0))
	{
		printf("不能连接服务器！\n");
	}
	else
	{
		printf("请输入你要修改的图书编号！\n");
		scanf("%s", &id);
		sql = "select * from tb_book where id=";
		strcat(dest, sql);
		strcat(dest, id);
		if (mysql_query(&mysql, dest))
		{
			printf("查询tb_book数据表失败！\n");
		}
		else
		{
			result = mysql_store_result(&mysql);
			if (mysql_num_rows(result) != NULL)
			{
				printf("发现信息，是否显示?(y/n)\n");
				scanf("%s", ch);
				if (strcmp(ch, "y") == 0 || strcmp(ch, "Y") == 0)
				{
					printf("\t ════════════════════════════════════════════════ \n");
					printf("\t               ***** 显示图书信息 *****                   \n");
					printf("\t ════════════════════════════════════════════════ \n");
					printf("\t图书编号       图书名         作者        出版社      \n");
					printf("\t -------------------------------------------------------- \n");
					while (row = mysql_fetch_row(result))
					{
						printf("\t     %s             %s            %s         %s   \n", row[0], row[1], row[2], row[3]);  //输出这行记录
					}
					printf("\t -------------------------------------------------------- \n");
					printf("Modify?(y/n)\n");
					scanf("%s", ch);
					if (strcmp(ch, "y") == 0 || strcmp(ch, "Y") == 0)
					{
						printf("\t图书名：");
						scanf("%s", &bookname);
						printf("\t作者：");
						scanf("%s", &author);
						printf("\t出版社：");
						scanf("%s", &bookconcern);
						sql = "update tb_book set bookname= '";
						strcat(dest1, sql);
						strcat(dest1, bookname);
						strcat(dest1, "',author='");
						strcat(dest1, author);
						strcat(dest1, "',bookconcern='");
						strcat(dest1, bookconcern);
						strcat(dest1, "'where id =");
						strcat(dest1, id);
						if (mysql_query(&mysql, dest1) != 0)//更新
						{
							printf("不能修改记录！\n");
						}
						else
						{
							printf("修改成功！\n");
						}
					}
				}
			}
			else
			{
				printf("没有发现要修改的信息！\n");
			}
		}
		mysql_free_result(result);
	}
	mysql_close(&mysql);
	printf("按任意键返回！\n");
	getch();
}

void deleteBook()
{
	char id[10];
	id[0] = '\0';
	char* sql;
	char dest[100];
	dest[0] = '\0';
	char dest1[100];
	dest1[0] = '\0';
	if (!mysql_real_connect(&mysql, "localhost", "root", "root", "db_books", 0, NULL, 0))
	{
		printf("无法连接数据库！\n");
	}
	else
	{
		printf("输入你想要删除的图书编号！\n");
		scanf("%s", id);
		sql = "select * from tb_book where id = ";
		strcat(dest, sql);
		strcat(dest, id);
		if (mysql_query(&mysql, dest))
		{
			printf("查询数据表失败！\n");
		}
		else
		{
			result = mysql_store_result(&mysql);
			if (row = mysql_num_rows(result) != NULL)
			{
				printf("发现信息，是否显示?(y/n)\n");
				scanf("%s", ch);
				if (strcmp(ch, "y") == 0 || strcmp(ch, "Y") == 0)
				{
					printf("\t ════════════════════════════════════════════════ \n");
					printf("\t               ***** 显示图书信息 *****                   \n");
					printf("\t ════════════════════════════════════════════════ \n");
					printf("\t图书编号       图书名         作者        出版社      \n");
					printf("\t -------------------------------------------------------- \n");
					while (row = mysql_fetch_row(result))
					{
						printf("\t     %s             %s            %s         %s   \n", row[0], row[1], row[2], row[3]);  //输出这行记录
					}
					printf("\t -------------------------------------------------------- \n");
					printf("Delete?(y/n)\n");
					scanf("%s", ch);
					if (strcmp(ch, "y") == 0 || strcmp(ch, "Y") == 0)
					{
						sql = "delete from tb_book where ID = ";
						strcat(dest1, sql);
						strcat(dest1, id);
						if (mysql_query(&mysql, dest1) != 0)//删除
						{
							printf("无法删除记录！\n");
						}
						else
						{
							printf("删除成功！\n");
						}
					}
				}
				else
				{
					printf("没有发现要删除的信息！\n");
				}
			}
			mysql_free_result(result);
		}
		mysql_close(&mysql);
	}
	printf("按任意键返回！\n");
	getch();
}

void queryBook()
{
	char id[10];
	id[0] = '\0';
	char* sql;
	char dest[100];
	dest[0] = '\0';
	if (!mysql_real_connect(&mysql, "localhost", "root", "root", "db_books", 0, NULL, 0))
	{
		printf("无法连接数据库！\n");
	}
	else
	{
		printf("请输入你要查询的图书编号：");
		scanf("%s", id);
		sql = "select * from tb_book where id = ";
		strcat(dest, sql);
		strcat(dest, id);
		if (mysql_query(&mysql, dest))
		{
			printf("查询数据表失败！\n");
		}
		else
		{
			result = mysql_store_result(&mysql);
			if (mysql_num_rows(result) != NULL)
			{
				printf("\t ════════════════════════════════════════════════ \n");
				printf("\t               ***** 显示图书信息 *****                   \n");
				printf("\t ════════════════════════════════════════════════ \n");
				printf("\t图书编号       图书名         作者        出版社      \n");
				printf("\t -------------------------------------------------------- \n");
				while (row = mysql_fetch_row(result))
				{
					printf("\t     %s             %s            %s         %s   \n", row[0], row[1], row[2], row[3]);  //输出这行记录
				}
				printf("\t -------------------------------------------------------- \n");
			}
			else
			{
				printf("没有你要查询的信息！\n");
			}
			mysql_free_result(result);
		}
		mysql_close(&mysql);
	}
	printf("按任意键返回！\n");
	getch();
}
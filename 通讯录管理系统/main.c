#include "header.h"

/*
通讯录管理系统：
	按1 数据录入
	按2 数据删除
	按3 通讯录列表
	按4 通讯录查询
	按5 保存数据
	按6 读取文件数据，下载数据
	按7 退出系统

	该系统主要使用链表和文件的读写进行操作，对链表进行增添、修改和删除。
*/

int main()
{
	LinkNode header;//头结点
	header = (Node*)malloc(sizeof(Node));
	if (header == NULL)
	{
		printf("allocate memory error!\n");
		exit(1);
	}
	header->next = NULL;
	while (1)
	{
		system("cls");
		switch (menu_select())
		{
		case 1:
			enter(header);//录入函数
			break;
		case 2:
			del(header);//删除函数
			break;
		case 3:
			list(header);//通讯录函数
			break;
		case 4:
			search(header);//查询函数
			break;
		case 5:
			save(header);//保存函数
			break;
		case 6:
			load(header);//读取数据
			break;
		case 7:
			exit(0);
		}
		printf("please press any key to continue.......\n");
		getch();
	}
}

int menu_select()
{
	int i = 0;
	do
	{
		system("cls");
		puts("\n\n\t*****************************ADDRESS LIST*****************************");
		puts("\t|*             1.input record                                       *|");
		puts("\t|*             2.delete record                                      *|");
		puts("\t|*             3.list record                                        *|");
		puts("\t|*             4.search record                                      *|");
		puts("\t|*             5.save record                                        *|");
		puts("\t|*             6.load record                                        *|");
		puts("\t|*             7.Quit                                               *|");
		puts("\t**********************************************************************");
		printf("\n\tEnter your choice:<1-7>");
		scanf("%d", &i);
	} while (i <= 0 || i > 7);
	return i;
}

void enter(LinkNode header)
{
	LinkNode p, q;
	q = header;
	while (q->next != NULL)
	{
		q = q->next;
	}//q为尾结点
	while (1)
	{
		p = (Node*)malloc(sizeof(Node));//申请空间
		if (p == NULL)
		{
			printf("allocate memory error!\n");//申请失败
			exit(1);
		}
		stringInput(p->data.name, 15, "enter name(0 to return):\n");//输入姓名
		if (strcmp(p->data.name, "0") == 0)//姓名为0退出信息输入
		{
			break;
		}
		stringInput(p->data.city, 15, "enter city:\n");//输入城市
		stringInput(p->data.province, 15, "enter province:\n");//输入省份
		stringInput(p->data.state, 10, "enter state:\n");//输入国家
		stringInput(p->data.tel, 15, "enter telephone:\n");//输入电话号码
		p->next = NULL;
		q->next = p;
		q = p;
	}
}

void stringInput(char* desStr, int lens, char* notice)
{
	char inputStr[50];
	inputStr[0] = '\0';
	do
	{
		printf(notice);//显示提示信息
		scanf("%s", inputStr);//输入字符串
		if (strlen(inputStr) > lens)
			printf("exceed the required length!\n");//超过lens值重新输入
	} while (strlen(inputStr) > lens);
	strcpy(desStr, inputStr);//赋给目标字符串
}

void search(LinkNode header)
{
	char name[20];
	name[0] = '\0';
	LinkNode p;
	p = header->next;
	printf("enter name to find:");
	scanf("%s", name);//输入需要查找的名字
	int isFind = 0;
	while (p)
	{
		if (strcmp(name, p->data.name) == 0)
		{
			display(p);//调用显示信息
			isFind = 1;
			break;
		}
		else
		{
			p = p->next;
		}
	}
	if (!isFind)
	{
		printf("not find this name!\n");
		return;
	}
}

void del(LinkNode header)
{
	/*
	删除链表结点，使用两个指针分别指向当前结点和当前结点前一个结点，
	若匹配当前结点，将当前结点的next指向赋给前一个结点的next指向，释放当前结点的空间
	若不匹配，同时向下一个结点推进
	*/
	LinkNode p, q;
	char s[20];
	s[0] = '\0';
	q = header->next;
	p = header;
	printf("enter name:");
	scanf("%s", s);//输入要删除的姓名
	while (q)
	{
		if (strcmp(s, q->data.name) == 0)
		{
			p->next = q->next;
			free(q);//释放内存
			printf("delete successfully!");
			break;
		}
		else
		{
			p = q;
			q = q->next;
		}
	}
}

void list(LinkNode header)
{
	LinkNode p;
	p = header->next;
	int i = 0;
	if (p == NULL)
	{
		printf("\nno record,please load records!!!\n");
		return;
	}
	while (p != NULL)
	{
		printf("\nThe %dth Message : \n", ++i);
		display(p);
		p = p->next;
	}
}

void display(LinkNode p)
{
	printf("name : %20s\n", p->data.name);
	printf("city : %20s\n", p->data.city);
	printf("province : %20s\n", p->data.province);
	printf("state : %20s\n", p->data.state);
	printf("tel : %20s\n", p->data.tel);
}

void save(LinkNode header)
{
	LinkNode p;
	FILE* fp;
	p = header->next;
	if ((fp = fopen("addresslist.txt", "wb")) == NULL)
	{
		printf("can't open this file");
		exit(1);
	}
	printf("\nSaving file\n");
	while (p)
	{
		fwrite(p, sizeof(Node), 1, fp);
		p = p->next;
	}
	fclose(fp);
}

void load(LinkNode header)
{
	LinkNode p, q;
	FILE* fp;
	header->next = NULL;
	p = header;
	if ((fp = fopen("addresslist.txt", "rb")) == NULL)
	{
		printf("can't open this file");
		exit(1);
	}
	printf("\nLoading file\n");
	while (!feof(fp))
	{
		q = (Node*)malloc(sizeof(Node));
		if (q == NULL)
		{
			printf("allocate memory error!\n");
			exit(1);
		}
		if (fread(q, sizeof(Node), 1, fp) != 1)
		{
			break;
		}
		else
		{
			q->next = NULL;//插入链表中
			p->next = q;
			p = q;
		}
	}
	fclose(fp);
}
#include "header.h"

/*
学生个人消费管理系统：
该系统，必须先创建信息表，将数据保存文件中，再次使用时下载数据才能使用数据。
链表的常规操作
	按0 退出系统
	按1 创造学生消费信息表
	按2 下载数据
	按3 查询学习消费信息
	按4 删除学习消费信息
	按5 增加学生消费信息
	按6 展示学生消费信息表
	按7 保存数据
*/
int main()
{
	int num = 0;
	LinkList head = NULL;
	menu();
	scanf("%d", &num);
	while (1)
	{
		switch (num)
		{
		case 1:
			head = creat();
			break;
		case 2:
			head = load();
			break;
		case 3:
			search(head);
			break;
		case 4:
			head = del(head);
			break;
		case 5:
			head = add(head);
			break;
		case 6:
			print(head);
			break;
		case 7:
			save(head);
			break;
		case 0:
			exit(0);
		default:
			printf("Input error,please again!");
		}
		printf("please press any key to continue......\n");
		getch();
		menu();
		scanf("%d", &num);
	}
}

void menu()
{
	system("cls");
	printf("\n\n\n");
	printf("\t\t----------------------Student Consume----------------------\n");
	printf("\t\t\t0. exit                                            \n");
	printf("\t\t\t1. creat                                           \n");
	printf("\t\t\t2. load                                            \n");
	printf("\t\t\t3. search                                          \n");
	printf("\t\t\t4. delete                                          \n");
	printf("\t\t\t5. add                                             \n");
	printf("\t\t\t6. show                                            \n");
	printf("\t\t\t7. save                                            \n");
	printf("\t\t------------------------------------------------------------\n\n");
	printf("\t\tchoose(0-7):");
}

LinkList creat()
{
	LinkList p = NULL, q = NULL;
	LinkList header = NULL;
	header = (Node*)malloc(LEN);//创建头结点
	if (header == NULL)
	{
		printf("allocate memory error!\n");
		exit(1);
	}
	header->next = NULL;
	q = header;
	while (1)
	{
		p = (Node*)malloc(LEN);
		if (p == NULL)
		{
			printf("allocate memory error!\n");
			exit(1);
		}
		printf("Please input student's information!\n");
		printf("Input number(input 0 return && number > 0):");
		scanf("%d", &p->number);
		if (p->number == 0)
		{
			break;//输入学号0退出录入信息
		}
		else if (p->number < 0)
		{
			printf("Numer inputed error!Must > 0!!!\n");
			printf("Input number again(input 0 return && number > 0):");//再次输入
			scanf("%d", &p->number);
		}
		printf("Input name:");
		scanf("%s", p->name);
		printf("Input consume money:");
		scanf("%d", &p->consumption);
		//插入链表
		p->next = NULL;
		q->next = p;
		q = p;
		g_studentNum++;//学生数量增加1，学生信息录入
	}
	header = sort(header);
	return header;
}

LinkList sort(LinkList head)
{ 
	//冒泡排序
	LinkList max = NULL, p = head->next;
	int i, j;
	for (i = 0; i < g_studentNum - 1; ++i)
	{
		for (j = i; j < g_studentNum - 1 - i; ++j)
		{
			max = p;
			p = p->next;
			if (max->number > p->number)
			{	//交换前后结点的学号
				int tempNum = max->number;
				max->number = p->number;
				p->number = tempNum;
				//交换前后结点的姓名
				char tempStr[10];
				tempStr[0] = '\0';
				strcpy(tempStr, max->name);
				strcpy(max->name, p->name);
				strcpy(p->name, tempStr);
				//交换前后结点的消费
				int tempConsume = max->consumption;
				max->consumption = p->consumption;
				p->consumption = tempConsume;
			}
		}
		p = head->next;
	}
	return head;
}

LinkList load()
{
	LinkList  p = NULL, q = NULL, r = NULL;
	q = (Node*)malloc(LEN);
	if (q == NULL)
	{
		printf("allocate memory error!\n");
		exit(1);
	}
	q->next = NULL;
	r = q;
	FILE* fp;
	printf("\nLoading Data......\n");
	if ((fp = fopen("consume.txt", "rb")) == NULL)
	{
		printf("can't open this file!\n");
		exit(1);
	}
	while (!feof(fp))
	{
		p = (Node*)malloc(LEN);
		if (p == NULL)
		{
			printf("allocate memory error!\n");
			exit(1);
		}
		if (fread(p, LEN, 1, fp) != 1)
		{
			break;
		}
		else
		{
			p->next = NULL;
			r->next = p;
			r = p;
		}
	}
	fclose(fp);
	return q;
}

void search(LinkList head)
{
	LinkList p = head->next;
	int searchNum = 0;
	printf("Input your want search number:\n");
	scanf("%d", &searchNum);
	int isFind = 0;
	while (p != NULL)
	{
		if (p->number == searchNum)
		{
			printf("-----------------------------------------\n");
			printf("student number : %20d\n", p->number);
			printf("student name ; %20s\n", p->name);
			printf("student consume : %20d\n", p->consumption);
			printf("-----------------------------------------\n");
			isFind = 1;
			break;
		}
		p = p->next;
	}
	if (!isFind)
	{
		printf("can't find this record!\n");
		return;
	}
}

LinkList del(LinkList head)
{
	LinkList p = NULL, q = NULL, r = head;
	p = head;
	q = head->next;
	int deleteNum = 0;
	int isDel = 0;
	printf("input the student's number of deleting:\n");
	scanf("%d", &deleteNum);
	while (q != NULL)
	{
		if (deleteNum == q->number)
		{
			p->next = q->next;
			free(q);
			printf("delete successfully!\n");
			isDel = 1;
			break;
		}
		else
		{
			p = q;
			q = q->next;
		}
	}
	if (!isDel)
	{
		printf("can't find this record!\n");
	}
	return r;
}

void print(LinkList head)
{
	if (head == NULL)
	{
		printf("no record!\n");
		return;
	}
	LinkList p = head->next;
	printf("------------------------Student Consume Message---------------------\n");
	printf("|%10s\t|%10s\t|%20s\t           |\n", "number", "name", "consumption");
	while (p != NULL)
	{
		printf("|%10d\t|%10s\t|%20d\t           |\n", p->number, p->name, p->consumption);
		p = p->next;
	}
	printf("--------------------------------------------------------------------\n");
}

void save(LinkList head)
{
	LinkList p = head->next;
	FILE* fp;
	if ((fp = fopen("consume.txt", "wb")) == NULL)
	{
		printf("can't open this file!\n");
		exit(1);
	}
	printf("\nSaving Data......\n");
	while (p)
	{
		fwrite(p, LEN, 1, fp);
		p = p->next;
	}
	fclose(fp);
}

LinkList add(LinkList head)
{
	LinkList p = NULL, r = head;
	while (r->next != NULL)
	{
		r = r->next;
	}
	while (1)
	{
		p = (Node*)malloc(LEN);
		if (p == NULL)
		{
			printf("allocate memory error!\n");
			exit(1);
		}
		printf("Please input student's information!\n");
		printf("Input number(input 0 return && number > 0):");
		scanf("%d", &p->number);
		if (p->number == 0)
		{
			break;//输入学号0退出录入信息
		}
		else if (p->number < 0)
		{
			printf("Numer inputed error!Must > 0!!!\n");
			printf("Input number again(input 0 return && number > 0):");//再次输入
			scanf("%d", &p->number);
		}
		printf("Input name:");
		scanf("%s", p->name);
		printf("Input consume money:");
		scanf("%d", &p->consumption);
		//插入链表
		p->next = NULL;
		r->next = p;
		r = p;
		g_studentNum++;//学生数量增加1，学生信息录入
	}
	head = sort(head);
	return head;
}
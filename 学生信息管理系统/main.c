#include "head.h"

void menu()/*自定义函数实现菜单功能*/
{
	system("cls");
	printf("\n\n\n\n");
	printf("\t\t|---------------学生信息管理系统---------------|\n");
	printf("\t\t|\t\t\t\t\t       |\n");
	printf("\t\t|\t\t 1. 录入学生信息\t       |\n");
	printf("\t\t|\t\t 2. 查找学生信息\t       |\n");
	printf("\t\t|\t\t 3. 删除学生信息\t       |\n");
	printf("\t\t|\t\t 4. 修改学生信息\t       |\n");
	printf("\t\t|\t\t 5. 插入学生信息\t       |\n");
	printf("\t\t|\t\t 6. 排序\t\t       |\n");
	printf("\t\t|\t\t 7. 统计学生总数\t       |\n");
	printf("\t\t|\t\t 8. 显示所有学生信息\t       |\n");
	printf("\t\t|\t\t 0. 退出系统\t\t       |\n");
	printf("\t\t|\t\t\t\t\t       |\n");
	printf("\t\t|----------------------------------------------|\n\n");
	printf("\t\t\t请选择(0-8):");
}

int main()
{
	system("color f0");//白底黑字
	int n;
	menu();
	scanf("%d", &n);
	while (n)
	{
		switch (n)
		{
		case 1:
			in();
			break;
		case 2:
			search();
			break;
		case 3:
			del();
			break;
		case 4:
			modify();
			break;
		case 5:
			insert();
			break;
		case 6:
			order();
			break;
		case 7:
			total();
			break;
		case 8:
			show();
			break;
		}
		getch();
		menu();
		scanf("%d", &n);
	}
}

void in()
{
	int i, record = 0;//记录条数
	char ch[2];
	FILE* fp;
	if ((fp = fopen("data.txt", "ab+")) == NULL)
	{
		printf("文件不存在！\n");
		return;
	}
	while (!feof(fp))
	{
		if (fread(&stu[record], LEN, 1, fp) == 1)
		{
			record++;
		}
	}
	fclose(fp);
	if (record == 0)
	{
		printf("文件中没有记录！\n");
	}
	else
	{
		show();
	}
	if ((fp = fopen("data.txt", "ab")) == NULL)
	{
		printf("文件不存在！\n");
		return;
	}
	printf("输入学生信息（y/n)：");
	scanf("%s", ch);
	while (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0)
	{
		printf("number:");
		scanf("%d", &stu[record].num);
		for (i = 0; i < record; ++i)
		{
			if (stu[i].num == stu[record].num)
			{
				printf("number 已存在，按任意键继续！\n");
				getch();
				fclose(fp);
				return;
			}
		}
		printf("name:");
		scanf("%s", &stu[record].name);
		printf("elective:");
		scanf("%lf", &stu[record].elec);
		printf("experiment:");
		scanf("%lf", &stu[record].expe);
		printf("required course:");
		scanf("%lf", &stu[record].requ);
		stu[record].sum = stu[record].elec + stu[record].expe + stu[record].requ;
		if (fwrite(&stu[record], LEN, 1, fp) != 1)
		{
			printf("不能保存！\n");
			getch();
		}
		else
		{
			printf("%d被保存！\n", stu[record].num);
			record++;
		}
		printf("继续?（y/n):");
		scanf("%s", ch);
	}
	fclose(fp);
	printf("OK！\n");
}

void search()
{
	FILE* fp;
	int i, m = 0, snum;
	if ((fp = fopen("data.txt", "rb")) == NULL)
	{
		printf("文件不存在！\n");
		return;
	}
	while (!feof(fp))
	{
		if (fread(&stu[m], LEN, 1, fp) == 1)
			m++;
	}
	fclose(fp);
	if (m == 0)
	{
		printf("文件中没有记录！\n");
	}
	printf("请输入 number:");
	scanf("%d", &snum);
	for (i = 0; i < m; ++i)
	{
		if (snum == stu[i].num)
		{
			printf("number  name           elective    experiment  required    sum\t\n");
			printf(FORMAT, DATA);
			break;
		}
	}
	if (i == m)
	{
		printf("未找到该学生的信息！\n");
	}
}

void del()
{
	FILE* fp;
	int snum, i, j, m = 0;
	char ch[2];
	if ((fp = fopen("data.txt", "rb")) == NULL)
	{
		printf("文件不存在！\n");
		return;
	}
	while (!feof(fp))
	{
		if (fread(&stu[m], LEN, 1, fp) == 1)
			m++;
	}
	fclose(fp);
	printf("请输入学生的学号：");
	scanf("%d", &snum);
	for (i = 0; i < m; ++i)
	{
		if (stu[i].num == snum)
		{
			printf("找到了这条记录，是否要删除！（y/n)\n");
			scanf("%s", ch);
			if (strcmp(ch, "y") == 0 || strcmp(ch, "Y") == 0)
			{
				for (j = i; j < m - 1; ++j)
				{
					stu[j] = stu[j + 1];
				}
				m--;
				if ((fp = fopen("data.txt", "wb")) == NULL)
				{
					printf("文件不存在！\n");
					return;
				}
				for (j = 0; j < m; ++j)
				{
					if (fwrite(&stu[j], LEN, 1, fp) != 1)
					{
						printf("不能保存！\n");
						getch();
					}
				}
				fclose(fp);
				printf("删除成功！\n");
				return;
			}
			else
			{
				printf("找到了记录，不删除！\n");
			}
			break;
		}
	}
	if (i == m)
	{	
		printf("未找到该学生！\n");
	}
}

void modify()
{
	FILE* fp;
	Student t;
	int i = 0, j = 0, m = 0, snum = 0;
	if ((fp = fopen("data.txt", "rb")) == NULL)
	{
		printf("文件不存在！\n");
		return;
	}
	while (!feof(fp))
	{
		if (fread(&stu[m], LEN, 1, fp) == 1)
			m++;
	}
	if (m == 0)
	{
		printf("没有记录！\n");
		fclose(fp);
		return;
	}
	show();
	printf("你要修改的学生number：");
	scanf("%d", &snum);
	for (i = 0; i < m; ++i)
	{
		if (snum == stu[i].num)
		{
			printf("找到该学生的信息！\n");
			printf("name:");
			scanf("%s", &stu[i].name);
			printf("elective:");
			scanf("%lf", &stu[i].elec);
			printf("experiment:");
			scanf("%lf", &stu[i].expe);
			printf("required course:");
			scanf("%lf", &stu[i].requ);
			stu[i].sum = stu[i].elec + stu[i].expe + stu[i].requ;
			if ((fp = fopen("data.txt", "wb")) == NULL)
			{
				printf("不能打开文件！\n");
				return;
			}
			for (j = 0; j < m; j++)
			{
				if (fwrite(&stu[j], LEN, 1, fp) != 1)
				{
					printf("不能保存文件！\n");
					getch();
				}
			}
			fclose(fp);
			break;
		}	
	}
	if (i == m)
	{
		printf("未找到该学生的信息！\n");
	}
}

void insert()
{
	FILE* fp;
	int i, j, k, m = 0, snum;
	if ((fp = fopen("data.txt", "rb")) == NULL)
	{
		printf("文件不存在！\n");
		return;
	}
	while (!feof(fp))
	{
		if (fread(&stu[m], LEN, 1, fp) == 1)
			m++;
	}
	if (m == 0)
	{
		printf("没有记录！\n");
		fclose(fp);
		return;
	}
	printf("请输入你要插入的位置(number)：\n");
	scanf("%d", &snum);
	for (i = 0; i < m; ++i)
	{
		if (stu[i].num == snum)
			break;
	}
	for (j = m - 1; j > i; --j)
	{
		stu[j + 1] = stu[j];
	}
	printf("请输入要插入的学生信息！\n");
	printf("number:");
	scanf("%d", &stu[i+1].num);
	printf("name:");
	scanf("%s", &stu[i + 1].name);
	printf("elective:");
	scanf("%lf", &stu[i + 1].elec);
	printf("experiment:");
	scanf("%lf", &stu[i + 1].expe);
	printf("required course:");
	scanf("%lf", &stu[i + 1].requ);
	stu[i + 1].sum = stu[i + 1].elec + stu[i+1].expe + stu[i + 1].requ;
	printf("插入成功按任意键返回！\n");
	if ((fp = fopen("data.txt", "wb")) == NULL)
	{
		printf("不能打开！\n");
		return;
	}
	for (k = 0; k <= m; ++k)
	{
		if (fwrite(&stu[k], LEN, 1, fp) != 1)
		{
			printf("不能保存！\n");
			getch();
		}
	}
	fclose(fp);
}

void order()
{
	FILE* fp;
	Student t;
	int i = 0, j = 0, m = 0;
	if ((fp = fopen("data.txt", "rb")) == NULL)
	{
		printf("文件不存在！\n");
		return;
	}
	while (!feof(fp))
	{
		if (fread(&stu[m], LEN, 1, fp) == 1)
			m++;
	}
	fclose(fp);
	if (m == 0)
	{
		printf("没有记录！\n");
		return;
	}
	if ((fp = fopen("data.txt","wb"))==NULL)
	{
		printf("文件不能打开！\n");
		return;
	}
	for (i = 0; i < m - 1; ++i)
	{
		for (j = 0; j < m - 1 - i; ++j)
		{
			if (stu[j].num > stu[j + 1].num)
			{
				t = stu[j];
				stu[j] = stu[j + 1];
				stu[j + 1] = t;
			}
		}
	}
	int k = 0;
	for (k = 0; k < m; ++k)
	{
		if (fwrite(&stu[k], LEN, 1, fp) != 1)
		{
			printf("不能保存！\n");
			getch();
		}
	}
	fclose(fp);
}

void show()
{
	int i, m = 0;
	FILE* fp;
	if ((fp = fopen("data.txt", "rb")) == NULL)
	{
		printf("文件不存在！\n");
		return;
	}
	while (!feof(fp))
	{
		if (fread(&stu[m], LEN, 1, fp) == 1)
			m++;
	}
	fclose(fp);
	if (m == 0)
	{
		printf("没有记录！\n");
		return;
	}
	printf("number  name           elective    experiment  required    sum\t\n");
	for (i = 0; i < m; ++i)
	{
		printf(FORMAT, DATA);
	}
	printf("\n");
}

void total()
{
	FILE* fp;
	int m = 0;
	if ((fp = fopen("data.txt", "r+")) == NULL)
	{
		printf("文件不存在！\n");
		return;
	}
	while (!feof(fp))
		if (fread(&stu[m], LEN, 1, fp) == 1)
			m++;			/*统计记录个数即学生个数*/
	if (m == 0) { printf("no record!\n"); fclose(fp); return; }
	printf("这个班级一共有 %d 名学生!\n", m);/*将统计的个数输出*/
	fclose(fp);
}
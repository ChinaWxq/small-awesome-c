#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

//员工信息结构体
typedef struct employee
{
	int num;//员工编号
	char duty[10];//员工职务
	char name[10];//员工姓名
	char sex[3];//员工性别
	unsigned char age;//员工年龄
	char edu[10];//教育水平
	int salary;//员工工资
	char tel_office[13];//办公电话
	char tel_home[13];//家庭电话
	char mobile[13];//手机
	char qq[11];//QQ号码
	char address[31];//家庭地址
	struct employee* next;
}EMP, *LinkList;

//全局变量
char password[9];//系统密码
LinkList emp_first, emp_end;//定义指向链表的首结点和尾结点的指针
/*
	使用全局变量的结构体指针指向数据表的首结点
	在菜单选择之前，将数据从文件中读出，emp_first指向首结点
	数据增添、删除等操作都是在全局变量emp_first上进行，然后将emp_first代表的数据信息上传到文件中更新信息。 
*/ 
char g_first;//判断信息表是否有数据 ，1为无数据，0为有数据 

//函数声明
void listEmp();//显示信息表 
void readData();//从文件读取数据 
void saveData();//保存数据到文件 
void bound(char ch, int n);//画出分界线
void checkFirst();//初始化检测
void menu();//主菜单
void login();//登入
void addEmp();//添加信息
void delEmp();//删除信息
void findEmp();//查找信息
LinkList findName(char* name);//查找姓名
LinkList findNum(int num);//查找工号
LinkList findTel(char* name);//查找电话
LinkList findQQ(char* name);//查找QQ
void displayEmp(LinkList emp1, char* field, char* name);//显示信息
void modifyEmp();//修改信息
int modi_salary(int salary);//修改薪水
int modi_age(int age);//修改年龄
char* modi_field(char* field, char* content, int len);//修改字符串信息
void summaryEmp();//统计信息
void resetPwd();//重置密码

int main()
{
	emp_first = emp_end = NULL;//链表指针初始化
	checkFirst();//初始化检测函数
	login();//登录函数
	readData();//从文件中读取数据初始化链表
	menu();//功能菜单显示函数
	system("pause");
	return 0;
}

void checkFirst()
{
	/*
	打开密码文件，判断是否为空，
	进而判断系统是否是第一次使用，第一次使用初始化密码
	不是第一次使用，进入登陆界面，提示输入密码。
	*/
	FILE* fp1, * fp2;
	char pwd[9], pwd1[9], ch;
	int i = 0;
	if ((fp1 = fopen("config.txt", "rb")) == NULL)
	{
		printf("\n新系统，请进行相应的初始化操作！\n");
		bound('_', 50);
		do
		{
			printf("\n设置密码，请不要超过8位：");
			for (i = 0; i < 8 && ((pwd[i] = getch()) != 13); ++i)
				putch('*');
			pwd[i] = '\0';
			printf("\n再确认一次密码：");
			for (i = 0; i < 8 && ((pwd1[i] = getch()) != 13); ++i)
				putch('*');
			pwd1[i] = '\0';
			if (strcmp(pwd, pwd1) != 0)//判断两次输入密码是否一致
			{
				printf("\n两次密码输入不一致，请重新输入！！！\n\n");
			}
			else
			{
				break;
			}
		} while (1);
		if ((fp2 = fopen("config.txt", "wb")) == NULL)
		{
			printf("\n系统创建失败，请按任意键退出！");
			getch();
			exit(1);
		}
		i = 0;
		while (pwd[i])
		{
			putw(pwd[i], fp2);//数组元素送入文件流中
			i++;
		}
		fclose(fp2);
		printf("\n\n系统初始化成功，按任意键退出，再重新进入！\n");
		getch();
		exit(1);
	}
	else
	{
		i = 0;
		while (!feof(fp1) && i < 8)
		{
			pwd[i++] = getw(fp1);
		}
		pwd[i] = '\0';
		if (i >= 8)
			i--;
		while (pwd[i] != -1 && i >= 0)
		{
			i--;
		}
		pwd[i] = '\0';
		strcpy(password, pwd);
		fclose(fp1);
	}
}

void menu()
{
	char choice;
	do
	{
		system("cls");
		printf("\n\t\t\t\t  企业员工管理系统\n\n");
		printf("\t\t\t---------------------------------\n");
		printf("\t\t\t|\t\t\t\t|\n");
		printf("\t\t\t|   \t1. 输入员工信息\t\t|\n");
		printf("\t\t\t|   \t2. 查询员工信息\t\t|\n");
		printf("\t\t\t|   \t3. 显示员工信息\t\t|\n");
		printf("\t\t\t|   \t4. 修改员工信息\t\t|\n");
		printf("\t\t\t|   \t5. 删除员工信息\t\t|\n");
		printf("\t\t\t|   \t6. 统计员工信息\t\t|\n");
		printf("\t\t\t|   \t7. 重置系统密码\t\t|\n");
		printf("\t\t\t|   \t0. 退出系统    \t\t|\n");
		printf("\t\t\t|\t\t\t\t|\n");
		printf("\t\t\t---------------------------------\n");
		printf("\n\t\t\t 请输入你需要的选择：");
		fflush(stdin);
		choice = getchar();
		//菜单选择中需要判断当前是否有数据 
		switch (choice)
		{
		case '1':
			addEmp();//调用员工信息添加函数
			break;
		case '2':
			if (g_first)
			{
				printf("系统信息中无员工信息，请先添加员工信息！\n");
				getch();
				break;
			}
			findEmp();//调用员工信息查找函数
			break;
		case '3':
			if (g_first)
			{
				printf("系统信息中无员工信息，请先添加员工信息！\n");
				getch();
				break;
			}
			listEmp();//调用员工信息列表函数
			break;
		case '4':
			if (g_first)
			{
				printf("系统信息中无员工信息，请先添加员工信息！\n");
				getch();
				break;
			}
			modifyEmp();//调用员工信息修改函数
			break;
		case '5':
			if (g_first)
			{
				printf("系统信息中无员工信息，请先添加员工信息！\n");
				getch();
				break;
			}
			delEmp();//调用员工信息删除函数
			break;
		case '6':
			if (g_first)
			{
				printf("系统信息中无员工信息，请先添加员工信息！\n");
				getch();
				break;
			}
			summaryEmp();//统计函数
			break;
		case '7':
			resetPwd();//重置系统的函数
			break;
		case '0':
			saveData();//保存数据函数
			exit(0);
		}
	} while (1);
}

void login()
{
	int i, n = 3;
	char pwd[9];
	do
	{
		printf("请输入密码：");
		for (i = 0; i < 8 && ((pwd[i] = getch()) != 13); ++i)
			putch('*');
		pwd[i] = '\0';
		if (strcmp(pwd, password)!=0)
		{
			getch();
			system("cls");
			n--;
		}
		else
		{
			break;
		}
	} while (n > 0);//密码输入三次的控制
	if (!n)
	{
		printf("请退出，已经错误三次密码！");
		getch();
		exit(1);
	}
}

void addEmp()
{
	LinkList emp1;
	int i = 0;
	do
	{
		i++;
		emp1 = (EMP*)malloc(sizeof(EMP));//申请内存
		if (emp1 == NULL)//判断内存是否分配成功
		{
			printf("内存分配失败，按任意键退出！\n");
			getch();
			return;
		}
		printf("请添加第%d个员工的信息:\n",i);
		bound('_', 30);
		printf("工号：");
		scanf("%d", &emp1->num);
		printf("职务：");
		scanf("%s", &emp1->duty);
		printf("姓名：");
		scanf("%s", &emp1->name);
		printf("性别：");
		scanf("%s", &emp1->sex);
		printf("年龄：");
		scanf("%d", &emp1->age);
		printf("文化程度：");
		scanf("%s", &emp1->edu);
		printf("工资：");
		scanf("%d", &emp1->salary);
		printf("办公电话：");
		scanf("%s", &emp1->tel_office);
		printf("家庭电话：");
		scanf("%s", &emp1->tel_home);
		printf("移动电话：");
		scanf("%s", &emp1->mobile);
		printf("QQ：");
		scanf("%s", &emp1->qq);
		printf("地址：");
		scanf("%s", &emp1->address);
		emp1->next = NULL;
		if (emp_first == NULL)//如果头指针为空 
		{
			emp_first = emp1;//头指针和尾指针都指向新结点 
			emp_end = emp1;
		}
		else
		{
			emp_end->next = emp1;//否则尾指针指向新结点 
			emp_end = emp1;
		}
		g_first = 0;//现已经有员工信息数据 
		printf("\n");
		bound('_', 30);
		printf("\n是否继续输入？(y/n)");
		char choice = getch();
		if (choice != 'y' && choice != 'Y')
		{
			printf("\n输入完毕，按任意键返回\n");
			getch();
			return;
		}
		system("cls");
	} while (1);
	
}

void delEmp()
{
	int findok = 0;
	LinkList emp1, emp2;//2个指针用来删除链表
	char name[10], choice;
	system("cls");
	printf("\n输入要删除的员工姓名：");
	scanf("%s", name);
	emp1 = emp_first;
	emp2 = emp1;
	while (emp1)
	{
		if (strcmp(emp1->name, name) == 0)
		{
			findok = 1;
			system("cls");

			printf("员工：%s的信息如下：\n", emp1->name);
			bound('_', 40);
			printf("工号：%d\n", emp1->num);
			printf("职务：%s\n", emp1->duty);
			printf("姓名：%s\n", emp1->name);
			printf("性别：%s\n", emp1->sex);
			printf("年龄：%d\n", emp1->age);
			printf("文化程度：%s\n", emp1->edu);
			printf("工资：%d\n", emp1->salary);
			printf("办公电话：%s\n", emp1->tel_office);
			printf("家庭电话：%s\n", emp1->tel_home);
			printf("移动电话：%s\n", emp1->mobile);
			printf("QQ号码：%s\n", emp1->qq);
			printf("住址：%s\n", emp1->address);
			bound('_', 40);
			printf("您真的要删除该员工吗？(y/n)");
			fflush(stdin);
			choice = getchar();

			if (choice == 'y' || choice == 'Y')
			{
				if (emp1 == emp_first)
				{
					emp_first = emp1->next;
				}
				else
				{
					emp2->next = emp1->next;
				}
				printf("员工%s已被删除", emp1->name);
				getch();
				free(emp1);
				saveData();
				return;
			}
			else
			{
				return;
			}
		}
		else
		{
			emp2 = emp1;
			emp1 = emp1->next;
		}
	}
	if (!findok)
	{
		bound('_', 40);
		printf("\n没有找到姓名是：%s的信息！\n", name);
		getch();
	}
}

void findEmp()
{
	int choice, ret = 0, num;
	char str[13];
	LinkList emp1;
	system("cls");
	do
	{
		printf("\t查询员工信息\n");
		bound('_', 30);
		printf("\t1.按姓名查询\n");
		printf("\t2.按工号查询\n");
		printf("\t3.按电话查询\n");
		printf("\t4.按QQ号查询\n");
		printf("\t0.返回主菜单\n");
		bound('_', 30);
		printf("\n请选择菜单：");
		do
		{
			choice = getchar();
			system("cls");
			switch (choice)
			{
			case '1':
				printf("\n输入要查询的员工姓名：");
				scanf("%s", str);
				emp1 = findName(str);//查找员工姓名 
				displayEmp(emp1, "姓名", str);
				getch();
				break;
			case '2':
				printf("\n输入要查询的员工工号：");
				scanf("%d", &num);
				emp1 = findNum(num);//查找员工工号 
				itoa(num, str, 10);
				displayEmp(emp1, "工号", str);
				getch();
				break;
			case '3':
				printf("\n输入要查询的员工电话：");
				scanf("%s", str);
				emp1 = findTel(str);//查找员工电话 
				displayEmp(emp1, "电话", str);
				getch();
				break;
			case '4':
				printf("\n输入要查询的员工QQ：");
				scanf("%s", str);
				emp1 = findQQ(str);//查找员工QQ 
				displayEmp(emp1, "QQ", str);
				getch();
				break;
			case '0':
				ret = 1;
				break;
			}
		} while (choice >= '0' && choice <= '4');
		system("cls");
		if (ret)
			break;
	} while (1);
}

LinkList findName(char* name)
{
	LinkList emp1;
	emp1 = emp_first;

	while (emp1)//遍历查找 
	{
		if (strcmp(name, emp1->name) == 0)
		{
			return emp1;
		}
		emp1 = emp1->next;
	}
	return NULL;
}

LinkList findNum(int num)
{
	LinkList emp1;
	emp1 = emp_first;
	while (emp1)//遍历查找 
	{
		if (num == emp1->num)
			return emp1;
		emp1 = emp1->next;
	}
	return NULL;
}

LinkList findTel(char* name)
{
	LinkList emp1;
	emp1 = emp_first;
	while (emp1)//遍历查找 
	{
		if ((strcmp(name, emp1->tel_office) == 0)
			|| (strcmp(name, emp1->tel_home) == 0)
			|| (strcmp(name, emp1->mobile) == 0))
			return emp1;
		emp1 = emp1->next;
	}
	return NULL;
}

LinkList findQQ(char* name)
{
	LinkList emp1;
	emp1 = emp_first;
	while (emp1)//遍历查找 
	{
		if (strcmp(name, emp1->qq) == 0)
			return emp1;
		emp1 = emp1->next;
	}
	return NULL;
}

void displayEmp(LinkList emp1, char* field, char* name)//展示信息 
{
	if (emp1)
	{
		printf("\n%s:%s信息如下：\n", field, name);
		bound('_', 30);
		printf("工号：%d\n", emp1->num);
		printf("职务：%s\n", emp1->duty);
		printf("姓名：%s\n", emp1->name);
		printf("性别：%s\n", emp1->sex);
		printf("年龄：%d\n", emp1->age);
		printf("文化程度：%s\n", emp1->edu);
		printf("工资：%d\n", emp1->salary);
		printf("办公电话：%s\n", emp1->tel_office);
		printf("家庭电话：%s\n", emp1->tel_home);
		printf("移动电话：%s\n", emp1->mobile);
		printf("QQ号码：%s\n", emp1->qq);
		printf("住址：%s\n", emp1->address);
		bound('_', 30);
	}
	else
	{
		bound('_', 40);
		printf("资料库没有%s为：%s的员工！", field, name);
	}
}

void modifyEmp()
{
	LinkList emp1;
	char name[10], * newcontent;
	int choice;
	printf("\n请输入你要修改的员工姓名：");
	scanf("%s", &name);
	emp1 = findName(name);
	displayEmp(emp1, "姓名", name);
	if (emp1)
	{
		printf("\n请输入你要修改的内容选项！\n");
		bound('_', 40);
		printf("1.修改职务				2.修改年龄\n");
		printf("3.修改文化程度			4.修改工资\n");
		printf("5.修改办公室电话		6.修改家庭电话\n");
		printf("7.修改移动电话			8.修改QQ号码\n");
		printf("9.修改住址				0.返回\n");
		do
		{
			choice = getchar();
			switch (choice)
			{
			case '1':
				newcontent = modi_field("职务", emp1->duty, 10);
				if (newcontent != NULL)
				{
					strcpy(emp1->duty, newcontent);
					free(newcontent);
				}
				break;
			case '2':
				emp1->age = modi_age(emp1->age);
				break;
			case '3':
				newcontent = modi_field("文化程度", emp1->edu, 10);
				if (newcontent != NULL)
				{
					strcpy(emp1->edu, newcontent);
					free(newcontent);
				}
				break;
			case '4':
				emp1->salary = modi_salary(emp1->salary);
				break;
			case '5':
				newcontent = modi_field("办公室电话", emp1->tel_office, 13);
				if (newcontent != NULL)
				{
					strcpy(emp1->tel_office, newcontent);
					free(newcontent);
				}
				break;
			case '6':
				newcontent = modi_field("家庭电话", emp1->tel_home, 13);
				if (newcontent != NULL)
				{
					strcpy(emp1->tel_home, newcontent);
					free(newcontent);
				}
				break;
			case '7':
				newcontent = modi_field("移动电话", emp1->mobile, 13);
				if (newcontent != NULL)
				{
					strcpy(emp1->mobile, newcontent);
					free(newcontent);
				}
				break;
			case '8':
				newcontent = modi_field("QQ", emp1->qq, 11);
				if (newcontent != NULL)
				{
					strcpy(emp1->qq, newcontent);
					free(newcontent);
				}
				break;
			case '9':
				newcontent = modi_field("住址", emp1->address, 30);
				if (newcontent != NULL)
				{
					strcpy(emp1->address, newcontent);
					free(newcontent);
				}
				break;
			case '0':
				return;
			}
		} while (choice <= '9' && choice >= '0');
		saveData();//保存信息 
		printf("\n修改完毕，按任意键返回！\n");
		getch();
	}
}

int modi_salary(int salary) 
{
	int newSalary;
	printf("原来的工资：%d", salary);
	printf("新的工资：");
	scanf("%d", &newSalary);
	return (newSalary);
}

int modi_age(int age)
{
	int newAge;
	printf("原来的年龄：%d", age);
	printf("新的年龄：");
	scanf("%d", &newAge);
	return (newAge);
}

char* modi_field(char* field, char* content, int len)//返回修改内容 
{
	char* str;
	str = malloc(sizeof(char) * len);
	if (str == NULL)
	{
		printf("内存分配失败，按任意键退出！\n");
		getch();
		return NULL;
	}
	printf("原来%s为：%s\n", field, content);
	printf("修改为（内存不超过%d个字符）：", len);
	scanf("%s", str);
	return str;
}

void summaryEmp()//统计信息 
{
	LinkList emp1;
	int sum = 0, num = 0, man = 0, woman = 0;
	emp1 = emp_first;
	while (emp1)
	{
		num++;
		sum += emp1->salary;
		if (strcmp("男", emp1->sex) == 0)
		{
			man++;
		}
		else
		{
			woman++;
		}
		emp1 = emp1->next;
	}
	printf("\n下面是员工的统计信息：\n");
	bound('_', 40);
	printf("员工数量：%d\n", num);
	printf("员工总工资：%d\n", sum);
	printf("男员工数：%d\n", man);
	printf("女员工数：%d\n", woman);
	bound('_', 40);
	printf("按任意键退出！\n");
	getch();
	return;
}

void resetPwd()
{
	char pwd[9], pwd1[9], ch;
	int i;
	FILE* fp1;
	system("cls");
	printf("\n请输入旧密码：\n");
	for (i = 0; i < 8 && ((pwd[i] = getch()) != 13); ++i)
		putch('*');
	pwd[i] = '\0';
	if (strcmp(password, pwd) != 0)
	{
		printf("\n密码错误，按任意键退出！\n");
		getch();
		return;
	}
	do
	{
		printf("\n设置新密码，请不要超过8位！\n");
		for (i = 0; i < 8 && ((pwd[i] = getch()) != 13); ++i)
			putch('*');
		pwd[i] = '\0';
		printf("\n再确认一次密码：\n");
		for (i = 0; i < 8 && ((pwd1[i] = getch()) != 13); ++i)
			putch('*');
		pwd1[i] = '\0';
		if (strcmp(pwd, pwd1) != 0)
		{
			printf("\n两次密码不一致，请重新输入！\n");
		}
		else
		{
			break;
		}
	} while (1);
	if ((fp1 = fopen("config.txt", "wb")) == NULL)
	{
		printf("\n系统创建失败，按任意键退出！\n");
		getch();
		exit(1);
	}
	i = 0;
	while (pwd[i])
	{
		putw(pwd[i], fp1);
		i++;
	}
	fclose(fp1);
	printf("\n密码修改成功，按任意键退出！\n");
	getch();
}

void listEmp()
{
	printf("\n员工信息表\n");
	LinkList emp1 = emp_first;
	int i = 0;
	while (emp1)
	{
		bound('_', 30);
		printf("第%d个员工的信息：\n",++i);
		printf("工号：%d\n", emp1->num);
		printf("职务：%s\n", emp1->duty);
		printf("姓名：%s\n", emp1->name);
		printf("性别：%s\n", emp1->sex);
		printf("年龄：%d\n", emp1->age);
		printf("文化程度：%s\n", emp1->edu);
		printf("工资：%d\n", emp1->salary);
		printf("办公电话：%s\n", emp1->tel_office);
		printf("家庭电话：%s\n", emp1->tel_home);
		printf("移动电话：%s\n", emp1->mobile);
		printf("QQ号码：%s\n", emp1->qq);
		printf("住址：%s\n", emp1->address);
		bound('_', 30);
		emp1 = emp1->next;
	}
	fflush(stdin);
	getchar();
}

void readData()
{
	FILE* fp;
	if ((fp = fopen("worker.txt", "rb") )== NULL)
	{
		//如果不存在信息文件，那么g_first=1，无信息 
		g_first = 1; 
		return;
	};
	//否则将信息存入全局链表中 
	LinkList emp1, emp2;//使用两个指针完成数据的下载 
	while (!feof(fp))
	{
		emp2 = (EMP*)malloc(sizeof(EMP));//申请内存 
		if (fread(emp2, sizeof(EMP), 1, fp) == 1)
		{
			if (emp_first == NULL)//如果首结点为空 
			{
				emp_first = emp2;//赋给首结点 
				emp1 = emp2;//emp1指向首结点 
			}
			else
			{
				emp2->next = NULL;//尾结点指向NULL 
				emp1->next = emp2;//指向新结点 
				emp1 = emp2;// 更新尾结点 
			}
		}
	}
	emp_end = emp_first;//尾指针和首指针都指向首结点 
	fclose(fp);
}

void saveData()//保存数据 
{
	FILE* fp;
	if ((fp = fopen("worker.txt", "wb")) == NULL)
	{
		printf("文件读取失败！\n");
		exit(1);
	}
	LinkList emp1 = emp_first;
	while (emp1)//循环写入 
	{
		fwrite(emp1, sizeof(EMP), 1, fp);
		emp1 = emp1->next;
	}
	fclose(fp);
}

void bound(char ch, int n)//画分界线 
{
	int i; 
	for (i = 0; i < n; ++i)
		putchar(ch);
	putchar('\n');
}

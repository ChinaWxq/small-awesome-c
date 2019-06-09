#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

//Ա����Ϣ�ṹ��
typedef struct employee
{
	int num;//Ա�����
	char duty[10];//Ա��ְ��
	char name[10];//Ա������
	char sex[3];//Ա���Ա�
	unsigned char age;//Ա������
	char edu[10];//����ˮƽ
	int salary;//Ա������
	char tel_office[13];//�칫�绰
	char tel_home[13];//��ͥ�绰
	char mobile[13];//�ֻ�
	char qq[11];//QQ����
	char address[31];//��ͥ��ַ
	struct employee* next;
}EMP, *LinkList;

//ȫ�ֱ���
char password[9];//ϵͳ����
LinkList emp_first, emp_end;//����ָ��������׽���β����ָ��
/*
	ʹ��ȫ�ֱ����Ľṹ��ָ��ָ�����ݱ���׽��
	�ڲ˵�ѡ��֮ǰ�������ݴ��ļ��ж�����emp_firstָ���׽��
	��������ɾ���Ȳ���������ȫ�ֱ���emp_first�Ͻ��У�Ȼ��emp_first�����������Ϣ�ϴ����ļ��и�����Ϣ�� 
*/ 
char g_first;//�ж���Ϣ���Ƿ������� ��1Ϊ�����ݣ�0Ϊ������ 

//��������
void listEmp();//��ʾ��Ϣ�� 
void readData();//���ļ���ȡ���� 
void saveData();//�������ݵ��ļ� 
void bound(char ch, int n);//�����ֽ���
void checkFirst();//��ʼ�����
void menu();//���˵�
void login();//����
void addEmp();//�����Ϣ
void delEmp();//ɾ����Ϣ
void findEmp();//������Ϣ
LinkList findName(char* name);//��������
LinkList findNum(int num);//���ҹ���
LinkList findTel(char* name);//���ҵ绰
LinkList findQQ(char* name);//����QQ
void displayEmp(LinkList emp1, char* field, char* name);//��ʾ��Ϣ
void modifyEmp();//�޸���Ϣ
int modi_salary(int salary);//�޸�нˮ
int modi_age(int age);//�޸�����
char* modi_field(char* field, char* content, int len);//�޸��ַ�����Ϣ
void summaryEmp();//ͳ����Ϣ
void resetPwd();//��������

int main()
{
	emp_first = emp_end = NULL;//����ָ���ʼ��
	checkFirst();//��ʼ����⺯��
	login();//��¼����
	readData();//���ļ��ж�ȡ���ݳ�ʼ������
	menu();//���ܲ˵���ʾ����
	system("pause");
	return 0;
}

void checkFirst()
{
	/*
	�������ļ����ж��Ƿ�Ϊ�գ�
	�����ж�ϵͳ�Ƿ��ǵ�һ��ʹ�ã���һ��ʹ�ó�ʼ������
	���ǵ�һ��ʹ�ã������½���棬��ʾ�������롣
	*/
	FILE* fp1, * fp2;
	char pwd[9], pwd1[9], ch;
	int i = 0;
	if ((fp1 = fopen("config.txt", "rb")) == NULL)
	{
		printf("\n��ϵͳ���������Ӧ�ĳ�ʼ��������\n");
		bound('_', 50);
		do
		{
			printf("\n�������룬�벻Ҫ����8λ��");
			for (i = 0; i < 8 && ((pwd[i] = getch()) != 13); ++i)
				putch('*');
			pwd[i] = '\0';
			printf("\n��ȷ��һ�����룺");
			for (i = 0; i < 8 && ((pwd1[i] = getch()) != 13); ++i)
				putch('*');
			pwd1[i] = '\0';
			if (strcmp(pwd, pwd1) != 0)//�ж��������������Ƿ�һ��
			{
				printf("\n�����������벻һ�£����������룡����\n\n");
			}
			else
			{
				break;
			}
		} while (1);
		if ((fp2 = fopen("config.txt", "wb")) == NULL)
		{
			printf("\nϵͳ����ʧ�ܣ��밴������˳���");
			getch();
			exit(1);
		}
		i = 0;
		while (pwd[i])
		{
			putw(pwd[i], fp2);//����Ԫ�������ļ�����
			i++;
		}
		fclose(fp2);
		printf("\n\nϵͳ��ʼ���ɹ�����������˳��������½��룡\n");
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
		printf("\n\t\t\t\t  ��ҵԱ������ϵͳ\n\n");
		printf("\t\t\t---------------------------------\n");
		printf("\t\t\t|\t\t\t\t|\n");
		printf("\t\t\t|   \t1. ����Ա����Ϣ\t\t|\n");
		printf("\t\t\t|   \t2. ��ѯԱ����Ϣ\t\t|\n");
		printf("\t\t\t|   \t3. ��ʾԱ����Ϣ\t\t|\n");
		printf("\t\t\t|   \t4. �޸�Ա����Ϣ\t\t|\n");
		printf("\t\t\t|   \t5. ɾ��Ա����Ϣ\t\t|\n");
		printf("\t\t\t|   \t6. ͳ��Ա����Ϣ\t\t|\n");
		printf("\t\t\t|   \t7. ����ϵͳ����\t\t|\n");
		printf("\t\t\t|   \t0. �˳�ϵͳ    \t\t|\n");
		printf("\t\t\t|\t\t\t\t|\n");
		printf("\t\t\t---------------------------------\n");
		printf("\n\t\t\t ����������Ҫ��ѡ��");
		fflush(stdin);
		choice = getchar();
		//�˵�ѡ������Ҫ�жϵ�ǰ�Ƿ������� 
		switch (choice)
		{
		case '1':
			addEmp();//����Ա����Ϣ��Ӻ���
			break;
		case '2':
			if (g_first)
			{
				printf("ϵͳ��Ϣ����Ա����Ϣ���������Ա����Ϣ��\n");
				getch();
				break;
			}
			findEmp();//����Ա����Ϣ���Һ���
			break;
		case '3':
			if (g_first)
			{
				printf("ϵͳ��Ϣ����Ա����Ϣ���������Ա����Ϣ��\n");
				getch();
				break;
			}
			listEmp();//����Ա����Ϣ�б���
			break;
		case '4':
			if (g_first)
			{
				printf("ϵͳ��Ϣ����Ա����Ϣ���������Ա����Ϣ��\n");
				getch();
				break;
			}
			modifyEmp();//����Ա����Ϣ�޸ĺ���
			break;
		case '5':
			if (g_first)
			{
				printf("ϵͳ��Ϣ����Ա����Ϣ���������Ա����Ϣ��\n");
				getch();
				break;
			}
			delEmp();//����Ա����Ϣɾ������
			break;
		case '6':
			if (g_first)
			{
				printf("ϵͳ��Ϣ����Ա����Ϣ���������Ա����Ϣ��\n");
				getch();
				break;
			}
			summaryEmp();//ͳ�ƺ���
			break;
		case '7':
			resetPwd();//����ϵͳ�ĺ���
			break;
		case '0':
			saveData();//�������ݺ���
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
		printf("���������룺");
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
	} while (n > 0);//�����������εĿ���
	if (!n)
	{
		printf("���˳����Ѿ������������룡");
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
		emp1 = (EMP*)malloc(sizeof(EMP));//�����ڴ�
		if (emp1 == NULL)//�ж��ڴ��Ƿ����ɹ�
		{
			printf("�ڴ����ʧ�ܣ���������˳���\n");
			getch();
			return;
		}
		printf("����ӵ�%d��Ա������Ϣ:\n",i);
		bound('_', 30);
		printf("���ţ�");
		scanf("%d", &emp1->num);
		printf("ְ��");
		scanf("%s", &emp1->duty);
		printf("������");
		scanf("%s", &emp1->name);
		printf("�Ա�");
		scanf("%s", &emp1->sex);
		printf("���䣺");
		scanf("%d", &emp1->age);
		printf("�Ļ��̶ȣ�");
		scanf("%s", &emp1->edu);
		printf("���ʣ�");
		scanf("%d", &emp1->salary);
		printf("�칫�绰��");
		scanf("%s", &emp1->tel_office);
		printf("��ͥ�绰��");
		scanf("%s", &emp1->tel_home);
		printf("�ƶ��绰��");
		scanf("%s", &emp1->mobile);
		printf("QQ��");
		scanf("%s", &emp1->qq);
		printf("��ַ��");
		scanf("%s", &emp1->address);
		emp1->next = NULL;
		if (emp_first == NULL)//���ͷָ��Ϊ�� 
		{
			emp_first = emp1;//ͷָ���βָ�붼ָ���½�� 
			emp_end = emp1;
		}
		else
		{
			emp_end->next = emp1;//����βָ��ָ���½�� 
			emp_end = emp1;
		}
		g_first = 0;//���Ѿ���Ա����Ϣ���� 
		printf("\n");
		bound('_', 30);
		printf("\n�Ƿ�������룿(y/n)");
		char choice = getch();
		if (choice != 'y' && choice != 'Y')
		{
			printf("\n������ϣ������������\n");
			getch();
			return;
		}
		system("cls");
	} while (1);
	
}

void delEmp()
{
	int findok = 0;
	LinkList emp1, emp2;//2��ָ������ɾ������
	char name[10], choice;
	system("cls");
	printf("\n����Ҫɾ����Ա��������");
	scanf("%s", name);
	emp1 = emp_first;
	emp2 = emp1;
	while (emp1)
	{
		if (strcmp(emp1->name, name) == 0)
		{
			findok = 1;
			system("cls");

			printf("Ա����%s����Ϣ���£�\n", emp1->name);
			bound('_', 40);
			printf("���ţ�%d\n", emp1->num);
			printf("ְ��%s\n", emp1->duty);
			printf("������%s\n", emp1->name);
			printf("�Ա�%s\n", emp1->sex);
			printf("���䣺%d\n", emp1->age);
			printf("�Ļ��̶ȣ�%s\n", emp1->edu);
			printf("���ʣ�%d\n", emp1->salary);
			printf("�칫�绰��%s\n", emp1->tel_office);
			printf("��ͥ�绰��%s\n", emp1->tel_home);
			printf("�ƶ��绰��%s\n", emp1->mobile);
			printf("QQ���룺%s\n", emp1->qq);
			printf("סַ��%s\n", emp1->address);
			bound('_', 40);
			printf("�����Ҫɾ����Ա����(y/n)");
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
				printf("Ա��%s�ѱ�ɾ��", emp1->name);
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
		printf("\nû���ҵ������ǣ�%s����Ϣ��\n", name);
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
		printf("\t��ѯԱ����Ϣ\n");
		bound('_', 30);
		printf("\t1.��������ѯ\n");
		printf("\t2.�����Ų�ѯ\n");
		printf("\t3.���绰��ѯ\n");
		printf("\t4.��QQ�Ų�ѯ\n");
		printf("\t0.�������˵�\n");
		bound('_', 30);
		printf("\n��ѡ��˵���");
		do
		{
			choice = getchar();
			system("cls");
			switch (choice)
			{
			case '1':
				printf("\n����Ҫ��ѯ��Ա��������");
				scanf("%s", str);
				emp1 = findName(str);//����Ա������ 
				displayEmp(emp1, "����", str);
				getch();
				break;
			case '2':
				printf("\n����Ҫ��ѯ��Ա�����ţ�");
				scanf("%d", &num);
				emp1 = findNum(num);//����Ա������ 
				itoa(num, str, 10);
				displayEmp(emp1, "����", str);
				getch();
				break;
			case '3':
				printf("\n����Ҫ��ѯ��Ա���绰��");
				scanf("%s", str);
				emp1 = findTel(str);//����Ա���绰 
				displayEmp(emp1, "�绰", str);
				getch();
				break;
			case '4':
				printf("\n����Ҫ��ѯ��Ա��QQ��");
				scanf("%s", str);
				emp1 = findQQ(str);//����Ա��QQ 
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

	while (emp1)//�������� 
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
	while (emp1)//�������� 
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
	while (emp1)//�������� 
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
	while (emp1)//�������� 
	{
		if (strcmp(name, emp1->qq) == 0)
			return emp1;
		emp1 = emp1->next;
	}
	return NULL;
}

void displayEmp(LinkList emp1, char* field, char* name)//չʾ��Ϣ 
{
	if (emp1)
	{
		printf("\n%s:%s��Ϣ���£�\n", field, name);
		bound('_', 30);
		printf("���ţ�%d\n", emp1->num);
		printf("ְ��%s\n", emp1->duty);
		printf("������%s\n", emp1->name);
		printf("�Ա�%s\n", emp1->sex);
		printf("���䣺%d\n", emp1->age);
		printf("�Ļ��̶ȣ�%s\n", emp1->edu);
		printf("���ʣ�%d\n", emp1->salary);
		printf("�칫�绰��%s\n", emp1->tel_office);
		printf("��ͥ�绰��%s\n", emp1->tel_home);
		printf("�ƶ��绰��%s\n", emp1->mobile);
		printf("QQ���룺%s\n", emp1->qq);
		printf("סַ��%s\n", emp1->address);
		bound('_', 30);
	}
	else
	{
		bound('_', 40);
		printf("���Ͽ�û��%sΪ��%s��Ա����", field, name);
	}
}

void modifyEmp()
{
	LinkList emp1;
	char name[10], * newcontent;
	int choice;
	printf("\n��������Ҫ�޸ĵ�Ա��������");
	scanf("%s", &name);
	emp1 = findName(name);
	displayEmp(emp1, "����", name);
	if (emp1)
	{
		printf("\n��������Ҫ�޸ĵ�����ѡ�\n");
		bound('_', 40);
		printf("1.�޸�ְ��				2.�޸�����\n");
		printf("3.�޸��Ļ��̶�			4.�޸Ĺ���\n");
		printf("5.�޸İ칫�ҵ绰		6.�޸ļ�ͥ�绰\n");
		printf("7.�޸��ƶ��绰			8.�޸�QQ����\n");
		printf("9.�޸�סַ				0.����\n");
		do
		{
			choice = getchar();
			switch (choice)
			{
			case '1':
				newcontent = modi_field("ְ��", emp1->duty, 10);
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
				newcontent = modi_field("�Ļ��̶�", emp1->edu, 10);
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
				newcontent = modi_field("�칫�ҵ绰", emp1->tel_office, 13);
				if (newcontent != NULL)
				{
					strcpy(emp1->tel_office, newcontent);
					free(newcontent);
				}
				break;
			case '6':
				newcontent = modi_field("��ͥ�绰", emp1->tel_home, 13);
				if (newcontent != NULL)
				{
					strcpy(emp1->tel_home, newcontent);
					free(newcontent);
				}
				break;
			case '7':
				newcontent = modi_field("�ƶ��绰", emp1->mobile, 13);
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
				newcontent = modi_field("סַ", emp1->address, 30);
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
		saveData();//������Ϣ 
		printf("\n�޸���ϣ�����������أ�\n");
		getch();
	}
}

int modi_salary(int salary) 
{
	int newSalary;
	printf("ԭ���Ĺ��ʣ�%d", salary);
	printf("�µĹ��ʣ�");
	scanf("%d", &newSalary);
	return (newSalary);
}

int modi_age(int age)
{
	int newAge;
	printf("ԭ�������䣺%d", age);
	printf("�µ����䣺");
	scanf("%d", &newAge);
	return (newAge);
}

char* modi_field(char* field, char* content, int len)//�����޸����� 
{
	char* str;
	str = malloc(sizeof(char) * len);
	if (str == NULL)
	{
		printf("�ڴ����ʧ�ܣ���������˳���\n");
		getch();
		return NULL;
	}
	printf("ԭ��%sΪ��%s\n", field, content);
	printf("�޸�Ϊ���ڴ治����%d���ַ�����", len);
	scanf("%s", str);
	return str;
}

void summaryEmp()//ͳ����Ϣ 
{
	LinkList emp1;
	int sum = 0, num = 0, man = 0, woman = 0;
	emp1 = emp_first;
	while (emp1)
	{
		num++;
		sum += emp1->salary;
		if (strcmp("��", emp1->sex) == 0)
		{
			man++;
		}
		else
		{
			woman++;
		}
		emp1 = emp1->next;
	}
	printf("\n������Ա����ͳ����Ϣ��\n");
	bound('_', 40);
	printf("Ա��������%d\n", num);
	printf("Ա���ܹ��ʣ�%d\n", sum);
	printf("��Ա������%d\n", man);
	printf("ŮԱ������%d\n", woman);
	bound('_', 40);
	printf("��������˳���\n");
	getch();
	return;
}

void resetPwd()
{
	char pwd[9], pwd1[9], ch;
	int i;
	FILE* fp1;
	system("cls");
	printf("\n����������룺\n");
	for (i = 0; i < 8 && ((pwd[i] = getch()) != 13); ++i)
		putch('*');
	pwd[i] = '\0';
	if (strcmp(password, pwd) != 0)
	{
		printf("\n������󣬰�������˳���\n");
		getch();
		return;
	}
	do
	{
		printf("\n���������룬�벻Ҫ����8λ��\n");
		for (i = 0; i < 8 && ((pwd[i] = getch()) != 13); ++i)
			putch('*');
		pwd[i] = '\0';
		printf("\n��ȷ��һ�����룺\n");
		for (i = 0; i < 8 && ((pwd1[i] = getch()) != 13); ++i)
			putch('*');
		pwd1[i] = '\0';
		if (strcmp(pwd, pwd1) != 0)
		{
			printf("\n�������벻һ�£����������룡\n");
		}
		else
		{
			break;
		}
	} while (1);
	if ((fp1 = fopen("config.txt", "wb")) == NULL)
	{
		printf("\nϵͳ����ʧ�ܣ���������˳���\n");
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
	printf("\n�����޸ĳɹ�����������˳���\n");
	getch();
}

void listEmp()
{
	printf("\nԱ����Ϣ��\n");
	LinkList emp1 = emp_first;
	int i = 0;
	while (emp1)
	{
		bound('_', 30);
		printf("��%d��Ա������Ϣ��\n",++i);
		printf("���ţ�%d\n", emp1->num);
		printf("ְ��%s\n", emp1->duty);
		printf("������%s\n", emp1->name);
		printf("�Ա�%s\n", emp1->sex);
		printf("���䣺%d\n", emp1->age);
		printf("�Ļ��̶ȣ�%s\n", emp1->edu);
		printf("���ʣ�%d\n", emp1->salary);
		printf("�칫�绰��%s\n", emp1->tel_office);
		printf("��ͥ�绰��%s\n", emp1->tel_home);
		printf("�ƶ��绰��%s\n", emp1->mobile);
		printf("QQ���룺%s\n", emp1->qq);
		printf("סַ��%s\n", emp1->address);
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
		//�����������Ϣ�ļ�����ôg_first=1������Ϣ 
		g_first = 1; 
		return;
	};
	//������Ϣ����ȫ�������� 
	LinkList emp1, emp2;//ʹ������ָ��������ݵ����� 
	while (!feof(fp))
	{
		emp2 = (EMP*)malloc(sizeof(EMP));//�����ڴ� 
		if (fread(emp2, sizeof(EMP), 1, fp) == 1)
		{
			if (emp_first == NULL)//����׽��Ϊ�� 
			{
				emp_first = emp2;//�����׽�� 
				emp1 = emp2;//emp1ָ���׽�� 
			}
			else
			{
				emp2->next = NULL;//β���ָ��NULL 
				emp1->next = emp2;//ָ���½�� 
				emp1 = emp2;// ����β��� 
			}
		}
	}
	emp_end = emp_first;//βָ�����ָ�붼ָ���׽�� 
	fclose(fp);
}

void saveData()//�������� 
{
	FILE* fp;
	if ((fp = fopen("worker.txt", "wb")) == NULL)
	{
		printf("�ļ���ȡʧ�ܣ�\n");
		exit(1);
	}
	LinkList emp1 = emp_first;
	while (emp1)//ѭ��д�� 
	{
		fwrite(emp1, sizeof(EMP), 1, fp);
		emp1 = emp1->next;
	}
	fclose(fp);
}

void bound(char ch, int n)//���ֽ��� 
{
	int i; 
	for (i = 0; i < n; ++i)
		putchar(ch);
	putchar('\n');
}

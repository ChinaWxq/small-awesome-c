#include "header.h"

/*
ͨѶ¼����ϵͳ��
	��1 ����¼��
	��2 ����ɾ��
	��3 ͨѶ¼�б�
	��4 ͨѶ¼��ѯ
	��5 ��������
	��6 ��ȡ�ļ����ݣ���������
	��7 �˳�ϵͳ

	��ϵͳ��Ҫʹ��������ļ��Ķ�д���в�������������������޸ĺ�ɾ����
*/

int main()
{
	LinkNode header;//ͷ���
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
			enter(header);//¼�뺯��
			break;
		case 2:
			del(header);//ɾ������
			break;
		case 3:
			list(header);//ͨѶ¼����
			break;
		case 4:
			search(header);//��ѯ����
			break;
		case 5:
			save(header);//���溯��
			break;
		case 6:
			load(header);//��ȡ����
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
	}//qΪβ���
	while (1)
	{
		p = (Node*)malloc(sizeof(Node));//����ռ�
		if (p == NULL)
		{
			printf("allocate memory error!\n");//����ʧ��
			exit(1);
		}
		stringInput(p->data.name, 15, "enter name(0 to return):\n");//��������
		if (strcmp(p->data.name, "0") == 0)//����Ϊ0�˳���Ϣ����
		{
			break;
		}
		stringInput(p->data.city, 15, "enter city:\n");//�������
		stringInput(p->data.province, 15, "enter province:\n");//����ʡ��
		stringInput(p->data.state, 10, "enter state:\n");//�������
		stringInput(p->data.tel, 15, "enter telephone:\n");//����绰����
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
		printf(notice);//��ʾ��ʾ��Ϣ
		scanf("%s", inputStr);//�����ַ���
		if (strlen(inputStr) > lens)
			printf("exceed the required length!\n");//����lensֵ��������
	} while (strlen(inputStr) > lens);
	strcpy(desStr, inputStr);//����Ŀ���ַ���
}

void search(LinkNode header)
{
	char name[20];
	name[0] = '\0';
	LinkNode p;
	p = header->next;
	printf("enter name to find:");
	scanf("%s", name);//������Ҫ���ҵ�����
	int isFind = 0;
	while (p)
	{
		if (strcmp(name, p->data.name) == 0)
		{
			display(p);//������ʾ��Ϣ
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
	ɾ�������㣬ʹ������ָ��ֱ�ָ��ǰ���͵�ǰ���ǰһ����㣬
	��ƥ�䵱ǰ��㣬����ǰ����nextָ�򸳸�ǰһ������nextָ���ͷŵ�ǰ���Ŀռ�
	����ƥ�䣬ͬʱ����һ������ƽ�
	*/
	LinkNode p, q;
	char s[20];
	s[0] = '\0';
	q = header->next;
	p = header;
	printf("enter name:");
	scanf("%s", s);//����Ҫɾ��������
	while (q)
	{
		if (strcmp(s, q->data.name) == 0)
		{
			p->next = q->next;
			free(q);//�ͷ��ڴ�
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
			q->next = NULL;//����������
			p->next = q;
			p = q;
		}
	}
	fclose(fp);
}
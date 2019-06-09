#include "head.h"

void menu()/*�Զ��庯��ʵ�ֲ˵�����*/
{
	system("cls");
	printf("\n\n\n\n");
	printf("\t\t|---------------ѧ����Ϣ����ϵͳ---------------|\n");
	printf("\t\t|\t\t\t\t\t       |\n");
	printf("\t\t|\t\t 1. ¼��ѧ����Ϣ\t       |\n");
	printf("\t\t|\t\t 2. ����ѧ����Ϣ\t       |\n");
	printf("\t\t|\t\t 3. ɾ��ѧ����Ϣ\t       |\n");
	printf("\t\t|\t\t 4. �޸�ѧ����Ϣ\t       |\n");
	printf("\t\t|\t\t 5. ����ѧ����Ϣ\t       |\n");
	printf("\t\t|\t\t 6. ����\t\t       |\n");
	printf("\t\t|\t\t 7. ͳ��ѧ������\t       |\n");
	printf("\t\t|\t\t 8. ��ʾ����ѧ����Ϣ\t       |\n");
	printf("\t\t|\t\t 0. �˳�ϵͳ\t\t       |\n");
	printf("\t\t|\t\t\t\t\t       |\n");
	printf("\t\t|----------------------------------------------|\n\n");
	printf("\t\t\t��ѡ��(0-8):");
}

int main()
{
	system("color f0");//�׵׺���
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
	int i, record = 0;//��¼����
	char ch[2];
	FILE* fp;
	if ((fp = fopen("data.txt", "ab+")) == NULL)
	{
		printf("�ļ������ڣ�\n");
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
		printf("�ļ���û�м�¼��\n");
	}
	else
	{
		show();
	}
	if ((fp = fopen("data.txt", "ab")) == NULL)
	{
		printf("�ļ������ڣ�\n");
		return;
	}
	printf("����ѧ����Ϣ��y/n)��");
	scanf("%s", ch);
	while (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0)
	{
		printf("number:");
		scanf("%d", &stu[record].num);
		for (i = 0; i < record; ++i)
		{
			if (stu[i].num == stu[record].num)
			{
				printf("number �Ѵ��ڣ��������������\n");
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
			printf("���ܱ��棡\n");
			getch();
		}
		else
		{
			printf("%d�����棡\n", stu[record].num);
			record++;
		}
		printf("����?��y/n):");
		scanf("%s", ch);
	}
	fclose(fp);
	printf("OK��\n");
}

void search()
{
	FILE* fp;
	int i, m = 0, snum;
	if ((fp = fopen("data.txt", "rb")) == NULL)
	{
		printf("�ļ������ڣ�\n");
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
		printf("�ļ���û�м�¼��\n");
	}
	printf("������ number:");
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
		printf("δ�ҵ���ѧ������Ϣ��\n");
	}
}

void del()
{
	FILE* fp;
	int snum, i, j, m = 0;
	char ch[2];
	if ((fp = fopen("data.txt", "rb")) == NULL)
	{
		printf("�ļ������ڣ�\n");
		return;
	}
	while (!feof(fp))
	{
		if (fread(&stu[m], LEN, 1, fp) == 1)
			m++;
	}
	fclose(fp);
	printf("������ѧ����ѧ�ţ�");
	scanf("%d", &snum);
	for (i = 0; i < m; ++i)
	{
		if (stu[i].num == snum)
		{
			printf("�ҵ���������¼���Ƿ�Ҫɾ������y/n)\n");
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
					printf("�ļ������ڣ�\n");
					return;
				}
				for (j = 0; j < m; ++j)
				{
					if (fwrite(&stu[j], LEN, 1, fp) != 1)
					{
						printf("���ܱ��棡\n");
						getch();
					}
				}
				fclose(fp);
				printf("ɾ���ɹ���\n");
				return;
			}
			else
			{
				printf("�ҵ��˼�¼����ɾ����\n");
			}
			break;
		}
	}
	if (i == m)
	{	
		printf("δ�ҵ���ѧ����\n");
	}
}

void modify()
{
	FILE* fp;
	Student t;
	int i = 0, j = 0, m = 0, snum = 0;
	if ((fp = fopen("data.txt", "rb")) == NULL)
	{
		printf("�ļ������ڣ�\n");
		return;
	}
	while (!feof(fp))
	{
		if (fread(&stu[m], LEN, 1, fp) == 1)
			m++;
	}
	if (m == 0)
	{
		printf("û�м�¼��\n");
		fclose(fp);
		return;
	}
	show();
	printf("��Ҫ�޸ĵ�ѧ��number��");
	scanf("%d", &snum);
	for (i = 0; i < m; ++i)
	{
		if (snum == stu[i].num)
		{
			printf("�ҵ���ѧ������Ϣ��\n");
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
				printf("���ܴ��ļ���\n");
				return;
			}
			for (j = 0; j < m; j++)
			{
				if (fwrite(&stu[j], LEN, 1, fp) != 1)
				{
					printf("���ܱ����ļ���\n");
					getch();
				}
			}
			fclose(fp);
			break;
		}	
	}
	if (i == m)
	{
		printf("δ�ҵ���ѧ������Ϣ��\n");
	}
}

void insert()
{
	FILE* fp;
	int i, j, k, m = 0, snum;
	if ((fp = fopen("data.txt", "rb")) == NULL)
	{
		printf("�ļ������ڣ�\n");
		return;
	}
	while (!feof(fp))
	{
		if (fread(&stu[m], LEN, 1, fp) == 1)
			m++;
	}
	if (m == 0)
	{
		printf("û�м�¼��\n");
		fclose(fp);
		return;
	}
	printf("��������Ҫ�����λ��(number)��\n");
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
	printf("������Ҫ�����ѧ����Ϣ��\n");
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
	printf("����ɹ�����������أ�\n");
	if ((fp = fopen("data.txt", "wb")) == NULL)
	{
		printf("���ܴ򿪣�\n");
		return;
	}
	for (k = 0; k <= m; ++k)
	{
		if (fwrite(&stu[k], LEN, 1, fp) != 1)
		{
			printf("���ܱ��棡\n");
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
		printf("�ļ������ڣ�\n");
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
		printf("û�м�¼��\n");
		return;
	}
	if ((fp = fopen("data.txt","wb"))==NULL)
	{
		printf("�ļ����ܴ򿪣�\n");
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
			printf("���ܱ��棡\n");
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
		printf("�ļ������ڣ�\n");
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
		printf("û�м�¼��\n");
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
		printf("�ļ������ڣ�\n");
		return;
	}
	while (!feof(fp))
		if (fread(&stu[m], LEN, 1, fp) == 1)
			m++;			/*ͳ�Ƽ�¼������ѧ������*/
	if (m == 0) { printf("no record!\n"); fclose(fp); return; }
	printf("����༶һ���� %d ��ѧ��!\n", m);/*��ͳ�Ƶĸ������*/
	fclose(fp);
}
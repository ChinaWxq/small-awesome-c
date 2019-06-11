#include "head.h"

//MySQL
//�������ݿ�:db_books
//�������ݱ�:tb_book

/*��ʾ�˵�*/
void showMenu()
{
	system("cls");
	printf("\n\n\n\n\n");
	printf("\t�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
	printf("\t�U            Welcome To Lemon Books System             �U\n");
	printf("\t�d�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�g\n");
	printf("\t�U\t\t 1 - ��ʾ����ͼ����Ϣ                  �U\n");
	printf("\t�U\t\t 2 - ���ͼ����Ϣ                      �U\n");
	printf("\t�U\t\t 3 - �޸�ͼ����Ϣ                      �U\n");
	printf("\t�U\t\t 4 - ɾ��ͼ����Ϣ                      �U\n");
	printf("\t�U\t\t 5 - ��ѯͼ����Ϣ                      �U\n");
	printf("\t�U\t\t 6 - �˳�                              �U\n");
	printf("\t�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
	printf("\n              ENTER YOUR CHOICE(1-6):");

}

int main()
{
	int n;
	mysql_init(&mysql);//��ʼ��mysql�ṹ
	showMenu();
	scanf("%d", &n);
	while (n)
	{
		switch (n)
		{
		case 1:
			showAll();//��ʾ��Ϣ
			break;
		case 2:
			addBook();//����ͼ����Ϣ
			break;
		case 3:
			modifyBook();//�޸�ͼ����Ϣ
			break;
		case 4:
			deleteBook();//ɾ��ͼ����Ϣ
			break;
		case 5:
			queryBook();//��ѯͼ����Ϣ
			break;
		case 6:
			exit(0);//�˳�
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
	if (!mysql_real_connect(&mysql, "localhost", "root", "root", "db_books", 0, NULL, 0))//����MySQL������
	{
		printf("�����������ݿ�!\n");
	}
	else
	{
		if (mysql_query(&mysql, "select * from tb_book"))//��ѯ���м�¼
		{
			printf("��ѯ���ݱ�ʧ��!\n");
		}
		else
		{
			result = mysql_store_result(&mysql);//��ȡ�����
			if (mysql_num_rows(result) != NULL)
			{  //�м�¼�����,ֻ���м�¼ȡ���ݲ�������
				printf("\t �T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T \n");
				printf("\t                 �� ʾ �� �� ͼ �� �� Ϣ                  \n");
				printf("\t �T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T \n");
				printf("\t  ͼ����       ͼ����         ����        ������      \n");
				printf("\t -------------------------------------------------\n");
				while ((row = mysql_fetch_row(result)))
				{   //ȡ��������м�¼
					printf("\t     %s             %s            %s         %s   \n", row[0], row[1], row[2], row[3]);  //������м�¼
				}
				printf("\t �T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T \n");
			}
			else
			{
				printf("û�м�¼��Ϣ !\n");
			}
			mysql_free_result(result);//�ͷŽ����
		}
		mysql_close(&mysql);//�ͷŷ���������
	}
	printf("����������أ�\n");
	getch();
}

void addBook()
{
	int rowcount;//�����������
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
	if (!mysql_real_connect(&mysql, "localhost", "root", "root", "db_books", 0, NULL, 0))//���ӷ�����
	{
		printf("�������ӵ����ݿ�!\n");
	}
	else
	{
		/*���ݿ����ӳɹ�����������*/
		printf("\t �T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T \n");
		printf("\t                     �� �� ͼ �� �� Ϣ                    \n");
		printf("\t �T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T \n");
		if (mysql_query(&mysql, "select * from tb_book"))
		{   //�����ѯʧ��
			printf("\n\t ��ѯ tb_book ���ݱ�ʧ��!\n");
		}
		else
		{
			result = mysql_store_result(&mysql);//��ȡ�����
			rowcount = mysql_num_rows(result);//��ȡ�����������
			row = mysql_fetch_row(result);//��ȡ���������
			printf("\tID��");
			scanf("%s", &id);
			if (mysql_num_rows(result) != NULL)
			{
				do
				{
					if (strcmp(id, row[0]) == 0)
					{
						printf("��¼�Ѵ��ڣ������������!\n");
						getch();
						mysql_free_result(result);//�ͷŽ����
						mysql_close(&mysql);//�ر����ݿ�
						return;
					}
				} while (row = mysql_fetch_row(result));//��ȡ��һ��������
			}
			printf("\tͼ������");
			scanf("%s", &bookname);
			sql = "insert into tb_book (ID,bookname,author,bookconcern) values(";
			strcat(dest, sql);
			strcat(dest, "'");
			strcat(dest, id);
			strcat(dest, "','");
			strcat(dest, bookname);
			printf("\t���ߣ�");
			scanf("%s", &author);
			strcat(dest, "','");
			strcat(dest, author);
			printf("\t�����磺");
			scanf("%s", &bookconcern);
			strcat(dest, "','");
			strcat(dest, bookconcern);
			strcat(dest, "')");
			if (mysql_query(&mysql, dest) != 0)//����
				printf("���ܲ���ü�¼!");
			else
				printf("����ɹ�!\n");
			mysql_free_result(result);
		}
		mysql_close(&mysql);
	}
	printf("����������أ�\n");
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
		printf("�������ӷ�������\n");
	}
	else
	{
		printf("��������Ҫ�޸ĵ�ͼ���ţ�\n");
		scanf("%s", &id);
		sql = "select * from tb_book where id=";
		strcat(dest, sql);
		strcat(dest, id);
		if (mysql_query(&mysql, dest))
		{
			printf("��ѯtb_book���ݱ�ʧ�ܣ�\n");
		}
		else
		{
			result = mysql_store_result(&mysql);
			if (mysql_num_rows(result) != NULL)
			{
				printf("������Ϣ���Ƿ���ʾ?(y/n)\n");
				scanf("%s", ch);
				if (strcmp(ch, "y") == 0 || strcmp(ch, "Y") == 0)
				{
					printf("\t �T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T \n");
					printf("\t               ***** ��ʾͼ����Ϣ *****                   \n");
					printf("\t �T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T \n");
					printf("\tͼ����       ͼ����         ����        ������      \n");
					printf("\t -------------------------------------------------------- \n");
					while (row = mysql_fetch_row(result))
					{
						printf("\t     %s             %s            %s         %s   \n", row[0], row[1], row[2], row[3]);  //������м�¼
					}
					printf("\t -------------------------------------------------------- \n");
					printf("Modify?(y/n)\n");
					scanf("%s", ch);
					if (strcmp(ch, "y") == 0 || strcmp(ch, "Y") == 0)
					{
						printf("\tͼ������");
						scanf("%s", &bookname);
						printf("\t���ߣ�");
						scanf("%s", &author);
						printf("\t�����磺");
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
						if (mysql_query(&mysql, dest1) != 0)//����
						{
							printf("�����޸ļ�¼��\n");
						}
						else
						{
							printf("�޸ĳɹ���\n");
						}
					}
				}
			}
			else
			{
				printf("û�з���Ҫ�޸ĵ���Ϣ��\n");
			}
		}
		mysql_free_result(result);
	}
	mysql_close(&mysql);
	printf("����������أ�\n");
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
		printf("�޷��������ݿ⣡\n");
	}
	else
	{
		printf("��������Ҫɾ����ͼ���ţ�\n");
		scanf("%s", id);
		sql = "select * from tb_book where id = ";
		strcat(dest, sql);
		strcat(dest, id);
		if (mysql_query(&mysql, dest))
		{
			printf("��ѯ���ݱ�ʧ�ܣ�\n");
		}
		else
		{
			result = mysql_store_result(&mysql);
			if (row = mysql_num_rows(result) != NULL)
			{
				printf("������Ϣ���Ƿ���ʾ?(y/n)\n");
				scanf("%s", ch);
				if (strcmp(ch, "y") == 0 || strcmp(ch, "Y") == 0)
				{
					printf("\t �T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T \n");
					printf("\t               ***** ��ʾͼ����Ϣ *****                   \n");
					printf("\t �T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T \n");
					printf("\tͼ����       ͼ����         ����        ������      \n");
					printf("\t -------------------------------------------------------- \n");
					while (row = mysql_fetch_row(result))
					{
						printf("\t     %s             %s            %s         %s   \n", row[0], row[1], row[2], row[3]);  //������м�¼
					}
					printf("\t -------------------------------------------------------- \n");
					printf("Delete?(y/n)\n");
					scanf("%s", ch);
					if (strcmp(ch, "y") == 0 || strcmp(ch, "Y") == 0)
					{
						sql = "delete from tb_book where ID = ";
						strcat(dest1, sql);
						strcat(dest1, id);
						if (mysql_query(&mysql, dest1) != 0)//ɾ��
						{
							printf("�޷�ɾ����¼��\n");
						}
						else
						{
							printf("ɾ���ɹ���\n");
						}
					}
				}
				else
				{
					printf("û�з���Ҫɾ������Ϣ��\n");
				}
			}
			mysql_free_result(result);
		}
		mysql_close(&mysql);
	}
	printf("����������أ�\n");
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
		printf("�޷��������ݿ⣡\n");
	}
	else
	{
		printf("��������Ҫ��ѯ��ͼ���ţ�");
		scanf("%s", id);
		sql = "select * from tb_book where id = ";
		strcat(dest, sql);
		strcat(dest, id);
		if (mysql_query(&mysql, dest))
		{
			printf("��ѯ���ݱ�ʧ�ܣ�\n");
		}
		else
		{
			result = mysql_store_result(&mysql);
			if (mysql_num_rows(result) != NULL)
			{
				printf("\t �T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T \n");
				printf("\t               ***** ��ʾͼ����Ϣ *****                   \n");
				printf("\t �T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T \n");
				printf("\tͼ����       ͼ����         ����        ������      \n");
				printf("\t -------------------------------------------------------- \n");
				while (row = mysql_fetch_row(result))
				{
					printf("\t     %s             %s            %s         %s   \n", row[0], row[1], row[2], row[3]);  //������м�¼
				}
				printf("\t -------------------------------------------------------- \n");
			}
			else
			{
				printf("û����Ҫ��ѯ����Ϣ��\n");
			}
			mysql_free_result(result);
		}
		mysql_close(&mysql);
	}
	printf("����������أ�\n");
	getch();
}
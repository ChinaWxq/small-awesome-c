#include "head.h"
/*
 * ������
 */
int main()
{
	system("color f0");             //����Ϊ�׵�
	int mode = 0;						//��ѯѡ��ģʽ
	int year, month, day, dMn, days;	//������������Լ�����
	int error_times = 0;				//����Ĵ���ƴ�
	LUNARDATE lunar_date;
	LONGTIME lt, lt2;

	while (error_times < 5)
	{
		year = -1, month = -1, day = -1, dMn = -1, days = 9025910;
		//���ñ���
		printf("\n\n\t\t\t    ����������(1840��2100)\n\n");
		lt = GetCurTime();				//��õ�ǰʱ��
		hOut = GetStdHandle(STD_OUTPUT_HANDLE);						//��ȡ����̨���
		SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED);   	//�׵׺���
		printf("\t\t\t   %d-%d-%d %02d:%02d:%02d %s\r\n\n", lt.wYear, lt.wMonth, lt.wDay, lt.wHour, lt.wMinute, lt.wSecond, Xingqi[lt.wDayOfWeek]);
		SetConsoleTextAttribute(hOut, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);   	//�Ļ�������ɫ���׵׺���
		SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED);
		printf("\t\t\t       ��");
		SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_BLUE);
		printf("��");
		SetConsoleTextAttribute(hOut, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
		printf("����ѡ��");
		SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE | FOREGROUND_GREEN);
		printf("��");
		SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE);
		printf("��          \n\n");
		SetConsoleTextAttribute(hOut, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);

		//����˵�ѡ��
		printf("\t\t-------------------------------------------------\n");
		printf("\t\t|\t*  1����ѯũ����\t\t\t|\n\t\t|\t\t\t\t\t\t|\n\t\t|\t*  "
			"2����ѯ������\t\t\t|\n\t\t|\t\t\t\t\t\t|\n\t\t|\t*  "
			"3����ʾ������\t\t\t|\n\t\t|\t\t\t\t\t\t|\n\t\t|\t*  "
			"4������ĳ�������������\t\t|\n\t\t|\t\t\t\t\t\t|\n\t\t|\t*  "
			"5����ѯ�������Ӧ���������ڡ�\t|\n\t\t|\t\t\t\t\t\t|\n\t\t|\t*  "
			"6��������������֮��������        |\n\t\t|\t\t\t\t\t\t|\n\t\t|\t*  "
			"7����ʾ��ʮ�Ľ�����\t\t\t|\n\t\t|\t\t\t\t\t\t|\n\t\t|\t*  "
			"8����ʾ���ա�\t\t\t|\n\t\t|\t\t\t\t\t\t|\n\t\t|\t*  "
			"0���˳���\t\t\t\t|\n");
		printf("\t\t-------------------------------------------------\n");
		printf("\t\t�������룺");
		scanf("%d", &mode);
		system("cls");

		//����ѡ����������ڽ�����������ʾ��ǰʱ��
		lt = GetCurTime();
		SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE);
		printf("\t\t��ǰ����ʱ�䣺%d-%d-%d %02d:%02d:%02d %s\r\n\r\n", lt.wYear, lt.wMonth, lt.wDay, lt.wHour, lt.wMinute, lt.wSecond, Xingqi[lt.wDayOfWeek]);
		SetConsoleTextAttribute(hOut, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
		switch (mode)
		{
		case 0:
			exit(1);
			//ѡ�1��
		case 1:
			printf("ũ����ѯ��\n\n");
			printf("������Ҫ��ѯ�Ĺ�������(�����ʽΪ���� �� ��)��<Year Month Day>");
			while (1)
			{
				scanf("%d%d%d", &year, &month, &day);
				if (year <= start_year || year > end_year || month < 1 || month>12 || day < 1 || day>31)
				{
					error_times++;
					printf("������������������������루����%d��/5�Σ���Year Month Day>", error_times);
					if (error_times >= 5)
					{
						printf("\r\n��������Ѵﵽ���ޣ��밴������˳�����");
						getch();
						return 1;
					}
				}
				else
				{
					dMn = GetDaysOfMonth(year, month, false, false);//�õ���ǰ�·ݵ�ʵ������
					if (day > dMn)
					{
						error_times++;
						printf("��ǰ�·�ֻ��%d�졣���������루����%d��/5�Σ���<Year Month Day>", dMn, error_times);
						if (error_times >= 5)
						{
							printf("\r\n��������Ѵﵽ���ޣ��밴������˳�����");
							getch();
							return 1;
						}
					}
					else
					{
						break;
					}
				}
			}
			ShowCalendar(year, month, day);//��ʾ����
			DateRefer(year, month, day, false);//���ù�����ѯ

			LONGTIME lt, lt2, lt3;
			double jq1, jq2;
			int index_jieqi = 0;				//�������
			int dM0 = Jizhun(year, month, 1);	//������������
			int hang = 0, lie = 0;				//������
			hang = year - start_year;			//��ǰ����������ݱ��е��к�,��0��ʼ
			for (index_jieqi = (month - 1) * 2; index_jieqi < 24; index_jieqi++)
			{
				jq1 = Jieqi[hang * 24 + index_jieqi];
				jq2 = Jieqi[hang * 24 + index_jieqi + 1];
				if (int2(jq1 + 0.5) <= (dM0 + 14) && int2(jq2 + 0.5) > (dM0 + 14))
				{
					break;
				}
			}

			//��ʾ���½���
			lt = GetDate(jq1);
			hOut = GetStdHandle(STD_OUTPUT_HANDLE);				//��ȡ����̨���
			SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE);   	//����������ɫ��Ϊ��ɫ
			printf("\n\t%s��%d-%d-%d %02d:%02d:%02d   ", jieqi[(index_jieqi) % 24], lt.wYear,
				lt.wMonth, lt.wDay, lt.wHour, lt.wMinute, lt.wSecond);
			lt = GetDate(jq2);
			printf("%s��%d-%d-%d %02d:%02d:%02d\r\n\r\n", jieqi[(index_jieqi + 1) % 24], lt.wYear,
				lt.wMonth, lt.wDay, lt.wHour, lt.wMinute, lt.wSecond);
			SetConsoleTextAttribute(hOut, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
			break;
			//ѡ�2��
		case 2:
			printf("������ѯ��\r\n\r\n");
			printf("������ũ�����ڣ���1987��������ʮ�������룺1987 6 17��������Χ��1840��2100��\nYear Month Day>");
			while (1)
			{
				scanf("%d %d %d", &year, &month, &day);
				if (year <= start_year || year > end_year || month < 1 || month>12 || day < 1 || day>30)
				{
					error_times++;
					printf("������������������������루����%d��/5�Σ���Year Month Day>", error_times);
					if (error_times >= 5)
					{
						printf("\r\n��������Ѵﵽ���ޣ��밴������˳�����");
						system("pause >nul");
						return 1;
					}
				}
				else
				{
					//���������ȷ�����ж����������Ƿ񳬹���������
					lunar_date.iYear = year;
					lunar_date.wMonth = month;
					lunar_date.wDay = day;
					lunar_date.bIsLeap = false;
					if (GetGre(lunar_date) != 0)
					{
						error_times++;
						if (error_times >= 5)
						{
							printf("\r\n��������Ѵﵽ���ޣ��밴������˳�����");
							system("pause >nul");
							return 1;
						}
					}
					else
					{
						break;
					}
				}
			}
			printf("\r\n");
			break;
		case 3:
			printf("������ʾ��\r\n\r\n");
			printf("������Ҫ��ѯ�Ĺ���������(1840��2100)��Year Month Day>");
			while (1)
			{
				scanf("%d %d %d", &year, &month, &day);
				if (year <= start_year || year > end_year || month < 1 || month>12)
				{
					error_times++;
					printf("������������������������루����%d��/5�Σ���Year Month>", error_times);
					if (error_times >= 5)
					{
						printf("\r\n��������Ѵﵽ���ޣ��밴������˳�����");
						system("pause >nul");
						return 1;
					}
				}
				else
				{
					break;
				}
			}
			ShowCalendar(year, month, day);
			break;
		case 4:
			printf("����ĳ�������������\r\n\r\n");
			printf("���������ڣ�Year Month Day>");
			while (1)
			{
				scanf("%d %d %d", &year, &month, &day);
				if (year <= start_year || year > end_year || month > 12 || month < 1 || day>31 || day < 1)
				{
					error_times++;
					printf("������������������������루����%d��/5�Σ���Year Month Day>", error_times);
					if (error_times >= 5)
					{
						printf("\r\n��������Ѵﵽ���ޣ��밴������˳�����");
						system("pause >nul");
						return 1;
					}
				}
				else
				{
					dMn = GetDaysOfMonth(year, month, false, false);
					if (day > dMn)
					{
						error_times++;
						printf("��ǰ�·�ֻ��%d�졣���������루����%d��/5�Σ���Year Month Day>", dMn, error_times);
						if (error_times >= 5)
						{
							printf("\r\n��������Ѵﵽ���ޣ��밴������˳�����");
							system("pause >nul");
							return 1;
						}
					}
					else
					{
						break;;
					}
				}
			}
			dMn = Jizhun(year, month, day);
			lt = GetCurTime();
			dMn -= Jizhun(lt.wYear, lt.wMonth, lt.wDay);
			hOut = GetStdHandle(STD_OUTPUT_HANDLE);				//��ȡ����̨���
			if (dMn >= 0)
			{
				SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE);   	//����������ɫ��Ϊ��ɫ
				printf("%d-%d-%d", year, month, day);
				SetConsoleTextAttribute(hOut, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);		//�ָ�������ɫ
				printf(" �Ƚ��죨");
				SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE);		//����������ɫΪ��ɫ
				printf("%d-%d-%d", lt.wYear, lt.wMonth, lt.wDay);
				SetConsoleTextAttribute(hOut, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
				printf("����");
				SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE | FOREGROUND_RED);
				printf("%d", dMn);
				SetConsoleTextAttribute(hOut, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
				printf("����\r\n\n\n\n");
			}
			else
			{
				SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE);  	//����������ɫ��Ϊ��ɫ
				printf("%d-%d-%d", year, month, day);
				SetConsoleTextAttribute(hOut, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);		//�ָ�������ɫ
				printf(" �Ƚ��죨");
				SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE);		//����������ɫΪ��ɫ
				printf("%d-%d-%d", lt.wYear, lt.wMonth, lt.wDay);
				SetConsoleTextAttribute(hOut, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
				printf("���硾");
				SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE | FOREGROUND_RED);
				printf("%d", -dMn);
				SetConsoleTextAttribute(hOut, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
				printf("����\r\n\n\n\n");
			}
			break;
		case 5:
			lt = GetCurTime();
			dMn = Jizhun(lt.wYear, lt.wMonth, lt.wDay);
			hOut = GetStdHandle(STD_OUTPUT_HANDLE);				//��ȡ����̨���
			printf("��ѯ�������Ӧ���������ڣ����������죨%d-%d-%d��������  ��Χ%d��%d����", lt.wYear, lt.wMonth, lt.wDay, -dMn - 2451545, 6574364 - dMn);
			while (1)
			{
				scanf("%d", &days);
				if (days > (6574364 - dMn) || days < (-dMn - 2451545))
				{
					error_times++;
					printf("������������������������루����%d��/5�Σ���Days>", error_times);
					if (error_times >= 5)
					{
						printf("\r\n��������Ѵﵽ���ޣ��밴������˳�����");
						system("pause >nul");
						return 1;
					}
				}
				else
				{
					break;
				}
			}
			lt2 = GetDate((double)(dMn + days));
			lt3 = GetDate((double)(dMn - days));
			printf("������죨%d-%d-%d���� %d ���������Ϊ��", lt.wYear, lt.wMonth, lt.wDay, days);
			SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED);	//����
			printf("\n%d-%d-%d  %s", lt2.wYear, lt2.wMonth, lt2.wDay, Xingqi[lt2.wDayOfWeek]);
			SetConsoleTextAttribute(hOut, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);		//�ָ�������ɫ
			printf("  ����Ϊ��");
			SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED);	//����
			printf("%d-%d-%d  %s\r\n\n\n", lt3.wYear, lt3.wMonth, lt3.wDay, Xingqi[lt3.wDayOfWeek]);
			SetConsoleTextAttribute(hOut, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);		//�ָ�������ɫ
			break;
		case 6:
			printf("������������֮��������\r\n\r\n");
			printf("�������һ�����ڣ�Year Month Day>");
			while (1)
			{
				scanf("%d %d %d", &year, &month, &day);
				if (year <= start_year || year > end_year || month > 12 || month < 1 || day>31 || day < 1)
				{
					error_times++;
					printf("��������������������������һ�����ڣ�����%d��/5�Σ���Year Month Day>", error_times);
					if (error_times >= 5)
					{
						printf("\r\n��������Ѵﵽ���ޣ��밴������˳�����");
						system("pause >nul");
						return 1;
					}
				}
				else
				{
					dMn = GetDaysOfMonth(year, month, false, false);
					if (day > dMn)
					{
						error_times++;
						printf("��ǰ�·�ֻ��%d�졣�����������һ�����ڣ�����%d��/5�Σ���Year Month Day>", dMn, error_times);
						if (error_times >= 5)
						{
							printf("\r\n��������Ѵﵽ���ޣ��밴������˳�����");
							system("pause >nul");
							return 1;
						}
					}
					else
					{
						break;;
					}
				}
			}
			lt2.wYear = year;
			lt2.wMonth = month;
			lt2.wDay = day;
			printf("������ڶ������ڣ�Year Month Day>");
			while (1)
			{
				scanf("%d %d %d", &year, &month, &day);
				if (year <= start_year || year > end_year || month > 12 || month < 1 || day>31 || day < 1)
				{
					error_times++;
					printf("�������������������������ڶ������ڣ�����%d��/5�Σ���Year Month Day>", error_times);
					if (error_times >= 5)
					{
						printf("\r\n��������Ѵﵽ���ޣ��밴������˳�����");
						system("pause >nul");
						return 1;
					}
				}
				else
				{
					dMn = GetDaysOfMonth(year, month, false, false);
					if (day > dMn)
					{
						error_times++;
						printf("��ǰ�·�ֻ��%d�졣����������ڶ������ڣ�����%d��/5�Σ���Year Month Day>", dMn, error_times);
						if (error_times >= 5)
						{
							printf("\r\n��������Ѵﵽ���ޣ��밴������˳�����");
							system("pause >nul");
							return 1;
						}
					}
					else
					{
						break;;
					}
				}
			}
			days = Jizhun(lt2.wYear, lt2.wMonth, lt2.wDay) - Jizhun(year, month, day);
			hOut = GetStdHandle(STD_OUTPUT_HANDLE);				//��ȡ����̨���
			SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE);	//����
			printf("\n%d-%d-%d ", lt2.wYear, lt2.wMonth, lt2.wDay);
			SetConsoleTextAttribute(hOut, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);		//�ָ�������ɫ
			printf("��");
			SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE);	//����
			printf("%d-%d-%d ", year, month, day);
			SetConsoleTextAttribute(hOut, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);		//�ָ�������ɫ
			printf("��� ��");
			SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED);	//����
			printf(" %d ", abs(days));
			SetConsoleTextAttribute(hOut, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);		//�ָ�������ɫ
			printf("���졣\r\n");
			break;
		case 7:
			printf("��ʾ��ʮ�Ľ�����\r\n\r\n");
			printf("������Ҫ��ѯ����ݣ�1840��2100����");
			while (1)
			{
				scanf("%d", &year);
				if (year <= start_year || year > end_year)
				{
					error_times++;
					printf("�����������������������루����%d��/5�Σ���Year>", error_times);
					if (error_times >= 5)
					{
						printf("\r\n��������Ѵﵽ���ޣ��밴������˳�����");
						system("pause >nul");
						return 1;
					}
				}
				else
				{
					break;
				}
			}
			ShowSolarTerms(year);
			break;
		case 8:
			printf("\t\t\t        ��ʾ����\r\n\r\n");
			printf("\t\t========================================\n");
			printf("\n\t\t1����ʾ��������\t\t2����ʾũ������\n");
			printf("\n\t\t��ѡ��");
			int choice = 0;
			scanf("%d", &choice);
			system("cls"); //����DOS��������
			switch (choice)
			{
			case 1:
				printf("\n\t\t\t\t �������ղ�ѯ\n\n");
				printf("\t\t =========================================\n");
				printf("\n");
				printf("\t\t ������Ҫ��ѯ���·�:   ");
				while (1)
				{
					int month = 0;
					scanf("%d", &month);
					if (month < 0 || month>13)
					{
						printf("\t\t���������������ȷ�·ݣ�1~12��:");
					}
					else
					{
						hOut = GetStdHandle(STD_OUTPUT_HANDLE);				//��ȡ����̨���
						SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED);	//����
						printf("\n\t\t\t\t%d�·ݵĽ���\n", month);
						SetConsoleTextAttribute(hOut, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);		//�ָ�������ɫ
						Holiday(month);
						break;
					}
				}
				break;
			case 2:
				printf("\n\t\t\t\t ũ�����ղ�ѯ\n\n");
				printf("\t\t===============================================\n");
				printf("\n");
				hOut = GetStdHandle(STD_OUTPUT_HANDLE);				//��ȡ����̨���
				SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE);	//����
				printf("\n\t\tũ�����³�һ   ����(the Spring Festival)\n");
				printf("\n\t\tũ������ʮ��   Ԫ����(Lantern Festival)\n");
				printf("\n\t\tũ�����³���   �����(the Dragon-Boat Festival)\n");
				printf("\n\t\tũ�����³���   ��Ϧ��(�й����˽ڣ�(Double-Seventh Day)\n");
				printf("\n\t\tũ������ʮ��   �����(the Mid-Autumn Festival)\n");
				printf("\n\t\tũ�����³���   ������(the Double Ninth Festival)\n");
				printf("\n\t\tũ�����³���   ���˽�(the laba Rice Porridge Festival)\n");
				printf("\n\t\tũ�����¶�ʮ�� ��ͳɨ����\n\n");
				SetConsoleTextAttribute(hOut, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);		//�ָ�������ɫ
				break;
			}
			break;
		default:
			error_times++;
			printf("���������������������루����%d��/5�Σ���\r\n\r\n", error_times);
			if (error_times >= 5)
			{
				printf("\r\n��������Ѵﵽ���ޣ��밴������˳�����");
				system("pause >nul");
				return 1;
			}
			break;
		}
		printf("�밴������������˵���");
		system("pause >nul");
		system("cls");
	}
	return 0;
}

/*
 * ��ӡ��һ���µ�����
 */
void ShowCalendar(int year, int month, int day)
{
	int dM0 = Jizhun(year, month, 1);		//������������
	int jd_day = dM0;						//���Բ�ѯ������������ũ���·�
	int base_days = 0;					//��׼��
	base_days = Jizhun(year, month, day);
	int dw0 = (dM0 + 142113) % 7;				//��������
	int idw = dw0;						//idw���ڱ�����ڣ����ڵ�һ�����
	int dMn = GetDaysOfMonth(year, month, false, false);//����������
	int hang = 0, lie = 0;					//������
	int Lyear = 0, Lmonth = 0, Lday = 0;		//ũ���ꡢ�¡���
	int nday0 = 1, nday1 = 1;				//nday0Ϊ����,nday1Ϊũ��
	int lunar_ndays = 0;					//ũ����������
	char* leap = "";						//����
	char* daxiao = "";					//���»�С��
	int dM0_lunar = 0, dM_lunar = 0;			//���׵�ũ��
	int cal_item = 0;						//���Ӽ���,��0��ʼ��С��7
	bool isfirstline = true;				//��ǵ�һ�����
	bool fillblanks = true;				//�Ƿ����ո�
	bool islunarcal = false;				//�Ƿ�Ϊũ������
	double jq1, jq2;						//���ڴ�ű��½�������ʱ��(������ÿ������������������)
	int Lmonth_index = 0;					//ũ������
	int index_jieqi = 0;					//�������
	LONGTIME lt;						//ʱ��ṹ��
	hang = year - start_year;				//��ǰ����������ݱ��е��к�,��0��ʼ
	lie = month - 1;						//���ǵ���ѯ�ķ�Χ,�����·ݼ�1Ϊ��ʼ��ѯ�к�,ũ���º��빫���º�������2

	//��ѯ�����������ڵ�ũ����
	for (lie; lie < 15; lie++)				//ע������һ����15��
	{

		if ((Yueshou[hang * 15 + lie - 1] <= dM0) && (Yueshou[hang * 15 + lie] > dM0))		//���ҵ�ǰ������������ũ����
		{
			break;
		}
	}
	lie--;								//����forѭ����ӵ�1

	//����
	if (Yuexu[hang * 14 + lie - 1] == Yuexu[hang * 14 + lie])
	{
		leap = "��";						//ũ�������г���������ͬ��,���¸���Ϊ����,������ǰһ����ͬ,��ǰ��"��"��
	}

	//�жϴ�ũ�����м��죬����30�죬Ϊ�����¡�����29�죬��Ϊ��С�¡�
	lunar_ndays = Yueshou[hang * 15 + lie + 1] - Yueshou[hang * 15 + lie];//ũ����������
	if (lunar_ndays == 31)				//ũ���´���31��,С��30��
	{
		daxiao = "��";
	}
	else if (lunar_ndays == 30)
	{
		daxiao = "С";
	}

	//���������еĵ�һ���ũ������
	Lyear = year;							//ũ����
	Lmonth_index = hang * 14 + lie;			//ũ��������
	Lmonth = Yuexu[Lmonth_index] - 1;		//ũ����,��ʮһ�¿�ʼ(����������ũ����Ϊ��)
	if (Lmonth < 1)
	{
		Lmonth += 12;
	}
	if (Lmonth > 10 && ((hang * 14 + lie) % 14 < 2))
	{
		Lyear--;						//����ʮһ�º�ʮ���µģ����ӦΪ��һ���
	}
	Lday = dM0 - Yueshou[hang * 15 + lie];		//ũ�������Ǿ�ũ�����׵���������

	//���������������λ��
	dM0_lunar = Lday;						//ũ���������ڵ�
	dM_lunar = dM0_lunar;
	for (index_jieqi = (month - 1) * 2; index_jieqi < 24; index_jieqi++)
	{
		jq1 = Jieqi[hang * 24 + index_jieqi];
		jq2 = Jieqi[hang * 24 + index_jieqi + 1];
		if (int2(jq1 + 0.5) <= (dM0 + 14) && int2(jq2 + 0.5) > (dM0 + 14))
		{
			break;
		}
	}

	//��ʼ��ӡ����
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);				//��ȡ����̨���
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE | FOREGROUND_RED);   	//����������ɫ��Ϊ��ɫ
	printf("\r\n\t\t����  %d��%d��  %s%s\r\n\r\n", year, month, Xingqi[(base_days + 142113) % 7], leap);
	SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED);   	//����������ɫ��Ϊ��ɫ
	printf("  ����\t");
	SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	printf("  ��һ\t  �ܶ�\t  ����\t  ����\t  ����\t");
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED);   	//����������ɫ��Ϊ��ɫ
	printf("  ����\r\n");
	SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	printf("________________________________________________________\r\n");

	//����forѭ����ʼ��ӡ����,��Ӧ����
	for (cal_item = 0; cal_item < 7; cal_item++)
	{
		if (!islunarcal)    			//�ж��Ƿ���ũ��
		{
			//���������
			if (fillblanks) 			//�ж��Ƿ��ǿո�
			{
				if (isfirstline && dw0 != 0)//��һ�첻Ϊ�������ڵ�һ��
				{
					printf("   \t   ");//��ʽ����,��ͬ
				}
				if (dw0 == 0)
				{
					printf("");
					cal_item = -1;		//����û���κ���䣬���������Ȼ��0�����¸�forѭ��ʱ����ֵ�������������ó�-1
				}
				for (idw; idw > 1; idw--)
				{
					//���ո���Ϊ��һ��if�Ѿ������һ�Σ���������Ҫ�����һ�Σ��������Ƶ�idw>1
					printf("\t   ");	//��������������ڵ�ǰ�漸��
					cal_item++;			//��ǰ���λ��������һ��
				}
				//�ո������ϣ����������
				idw = dw0;				//���¸�ֵ����������������,Ϊ�˿��ƶ�Ӧ��ũ�����
				fillblanks = false;		//ȡ�����ո�
			}
			else
			{
				if (cal_item == 0)
				{
					printf("   ");		//��ʽ����,��ͬ
				}
				printf("%d\t   ", nday0);
				nday0++;				//������������һ��

				if (cal_item == 5 || cal_item == 6)		//�������������պ�ɫ���������������
				{
					handle = GetStdHandle(STD_OUTPUT_HANDLE);				//��ȡ����̨���
					SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED);
				}
				else
				{
					SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
				}
				//������ڴ��ڵ��µ�������
				if (nday0 > dMn)
				{
					printf("\r\n");
					cal_item = -1;			//for ѭ��֮�����̼�һ,��˸�Ϊ-1
					islunarcal = true;		//��ʼ���ũ��
				}
				if (cal_item == 6)
				{
					cal_item = -1;
					printf("\r\n");
					islunarcal = true;		//һ�й��������ɣ�ת��ũ�����
					if (isfirstline)
					{
						fillblanks = true;	//��ʼ���ո�
					}
				}
			}
			//��ӡũ��
		}
		else
		{
			if (fillblanks)
			{
				//ũ�����ո�
				if (isfirstline && dw0 != 0)
				{
					printf("   \t ");
				}
				if (dw0 == 0)
				{
					cal_item = -1;
				}
				for (idw; idw > 2; idw--)
				{

					printf("\t   ");	//�������ũ��ǰ��ո������빫����ͬ��ԭ�����ڿ����������
					cal_item++;			//��ǰ���λ��������һ��
				}
				if (dw0 > 1)
				{
					printf("\t ");
					cal_item++;
				}
				fillblanks = false;		//ֹͣ���ո�
			}
			else
			{
				if (dM_lunar >= lunar_ndays)
				{
					//ũ���ճ�����������,��Ϊ��һ��
					//��һ�����²�ѯ
					Lmonth_index++;
					Lmonth = Yuexu[Lmonth_index] - 1;
					if (Lmonth < 1)
					{
						Lmonth += 12;
					}

					if (Lmonth > 10)
					{
						year--;		//����ʮһ�º�ʮ���µģ����ӦΪ��һ���
					}
					lunar_ndays = Yueshou[hang * 15 + lie + 2] - Yueshou[hang * 15 + lie + 1];	//���¼����µ�һ��ũ��������
					dM_lunar = 0;		//�ӳ�һ��ʼ
				}
				//�������������պ�ɫ�������ũ������
				if (cal_item == 0 || cal_item == 6)
				{
					handle = GetStdHandle(STD_OUTPUT_HANDLE);				//��ȡ����̨���
					SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED);
				}
				else
				{
					SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
				}

				if (int2(jq1 + 0.5) == jd_day)
				{
					if (cal_item == 0)
					{
						printf("  ");
					}
					HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);		//��ȡ����̨���
					SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED);   	//����������ɫ��Ϊ��ɫ
					printf("%s", jieqi[(index_jieqi) % 24]);					//��������н���(jq1),���ӡ����������
					SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
				}
				else if (int2(jq2 + 0.5) == jd_day)
				{
					if (cal_item == 0)
					{
						printf("  ");
					}
					HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);		//��ȡ����̨���
					SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED);   	//����������ɫ��Ϊ��ɫ
					printf("%s", jieqi[(index_jieqi + 1) % 24]);					//��������н���(jq2),���ӡ����������
					SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
				}
				else
				{
					if (dM_lunar == 0)
					{
						if (Yuexu[Lmonth_index] == Yuexu[Lmonth_index - 1])
						{
							printf("��");           //���������
						}
						else
						{
							if (cal_item == 0)
							{
								printf(" ");
							}
						}
						printf("%s", mName[Lmonth - 1]);
						if (lunar_ndays == 30)
						{
							printf("��");
						}
						else
						{
							printf("С");
						}
					}
					else
					{
						if (cal_item == 0)
						{
							printf("  ");
						}
						printf("%s", dName[dM_lunar]);
					}
				}
				jd_day++;			//��׼��ָ����һ��
				dM_lunar++;			//ũ����ָ����һ��
				nday1++;			//��������ŵ�����ָ����һ��
				if (dM_lunar == lunar_ndays)
				{
					if (Yuexu[Lmonth_index + 1] == Yuexu[Lmonth_index])
					{
						printf(" ");
					}
					else
					{
						printf("\t ");
					}
				}
				else
				{
					if (Yuexu[Lmonth_index - 1] == Yuexu[Lmonth_index])
					{
						if (dM_lunar == 0)
						{
							printf(" ");
						}
						else
						{
							printf("\t ");
						}
					}
					else
					{
						printf("\t ");
					}
				}
				if (nday1 > dMn)
				{
					break;
				}

				if (cal_item == 6)
				{
					cal_item = -1;		//for ѭ��֮�����̼�һ,��˸�Ϊ-1
					printf("\r\n\r\n");
					islunarcal = false;	//һ�н�����ʼת���������
					if (isfirstline)
					{
						isfirstline = false;
					}
					if (nday1 > dMn)
					{
						break;
					}
				}
			}
		}
	}
	printf("\r\n________________________________________________________\r\n");
}

/*
 * ���㵱ǰ�·ݵ�����
 */
int GetDaysOfMonth(int year, int month, bool mode, bool bLeap)
{
	int dM0 = 0, dMn = 0;
	if (!mode)
	{
		dM0 = Jizhun(year, month, 1);				//��������
		if (month == 12)
		{
			dMn = Jizhun(++year, 1, 1) - dM0;			//Ԫ��
		}
		else
		{
			dMn = Jizhun(year, ++month, 1) - dM0;		//�¸���
		}
	}
	else
	{
		int leap_Month = -1;						//ũ����������λ��
		int hang = year - start_year;				//������
		int i = 0;
		int lie = month + 1;
		for (i = 0; i < 14; i++)
		{
			if (Yuexu[hang * 14 + i + 1] == Yuexu[hang * 14 + i])
			{
				leap_Month = i - 1;
				break;
			}
		}
		if (leap_Month == -1)
		{
			if (bLeap)
			{
				return -1;					//�����ǰ��������£������������£��򷵻�-1���Դ����������
			}
		}
		else
		{
			if (bLeap)
			{
				if (leap_Month != month)
				{
					return -1;			//��ǰ��������£������ǵ�ǰ�����·�
				}
			}
		}
		if (leap_Month != -1)
		{
			if (month > leap_Month)		//�ڵ��������Լ�֮��
			{

				lie++;
			}
			else
			{
				if (bLeap == true && month == leap_Month)
				{
					lie++;
				}
			}
		}
		dMn = Yueshou[hang * 15 + lie + 1] - Yueshou[hang * 15 + lie];
	}
	return dMn;//���ص�ǰ�����·ݵ�����
}

/*
 * ��ѯĳ��ũ���ͽ���
 */
void DateRefer(int year, int month, int day, bool SST)
{
	int Lyear = 0, Lmonth = 0, Lday = 0;
	int base_days = 0;			//��׼��
	int hang = 0, lie = 0;			//������
	int i = 0, ijq0 = 0, ijq1 = 0;		//����
	char* leap = "";				//����
	char* daxiao = "";			//���»�С��
	Lyear = year;
	base_days = Jizhun(year, month, day);
	hang = year - start_year;
	lie = month - 1;

	for (lie; lie < 15; lie++)
	{
		if ((Yueshou[hang * 15 + lie - 1] <= base_days) && (Yueshou[hang * 15 + lie] > base_days))
		{
			break;
		}
	}
	lie--;//������ӵ�1
	if (Yuexu[hang * 14 + lie - 1] == Yuexu[hang * 14 + lie])
	{
		leap = "��";
	}
	if ((Yueshou[hang * 15 + lie + 1] - Yueshou[hang * 15 + lie]) == 31)
	{
		daxiao = "��";
	}
	else
	{
		daxiao = "С";
	}
	Lmonth = Yuexu[hang * 14 + lie] - 1;
	if (Lmonth < 1)
	{
		Lmonth += 12;
	}
	if (Lmonth > 10 && ((hang * 14 + lie) % 14 < 2))
	{
		Lyear--;//����ʮһ�º�ʮ���µģ����ӦΪ��һ���
	}
	Lday = base_days - Yueshou[hang * 15 + lie];//�ӳ�һ��ʼ

	if (SST)        //SSTΪtrueʱ����ʾũ������ʾ����
	{
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);				//��ȡ����̨���
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE | FOREGROUND_RED);   	//����������ɫ��Ϊ��ɫ
		printf("%s%s�� %s%s(%s)%s", tiangan[(Lyear - 1984 + 9000) % 10],
			dizhi[(Lyear - 1984 + 9000) % 12], leap, mName[Lmonth - 1], daxiao, dName[Lday]);
		SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	}
	else
	{
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);				//��ȡ����̨���
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE | FOREGROUND_RED);   	//����������ɫ��Ϊ��ɫ
		printf("\n\t\tũ��  %s%s[%s]�� %s%s��%s��%s\t\n", tiangan[(Lyear - 1984 + 9000) % 10],
			dizhi[(Lyear - 1984 + 9000) % 12], shengxiao[(Lyear - 1984 + 9000) % 12],
			leap, mName[Lmonth - 1], daxiao, dName[Lday]);
		SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
		for (i = (month - 1) * 2; i < 48; i++)
		{
			ijq0 = int2(Jieqi[hang * 24 + i] + 0.5);
			ijq1 = int2(Jieqi[hang * 24 + i + 1] + 0.5);
			if (ijq1 > base_days && ijq0 <= base_days)
			{
				if (ijq0 == base_days)
				{
					LONGTIME lt = GetDate(Jieqi[hang * 24 + i]);
					printf("\n\t���ս�����");
					HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);				//��ȡ����̨���
					SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED);   	//����������ɫ��Ϊ��ɫ
					printf("%s", jieqi[i % 24]);
					SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
					printf(" ����ʱ�䣺");
					SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED);   	//����������ɫ��Ϊ��ɫ
					printf("%d-%d-%d %02d:%02d:%02d\r\n\r\n", lt.wYear, lt.wMonth, lt.wDay, lt.wHour, lt.wMinute, lt.wSecond);
					SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
				}
				else
				{
					printf("\n\t������һ��������");
					HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);				//��ȡ����̨���
					SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED);   	//����������ɫ��Ϊ��ɫ
					printf("%s", jieqi[(i + 1) % 24]);
					SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
					printf("������");
					SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED);   	//����������ɫ��Ϊ��ɫ
					printf("%d", ijq1 - base_days);
					SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
					printf("��\n");
				}
				break;
			}
		}
	}
}

/*
 * �������׼��
 */
int Jizhun(int year, int month, int day)
{
	int basedays = 0;
	int x = 0, y = 0;
	if (month <= 2 && month > 0)
	{
		year--;
		month += 12;
	}
	x = (int)(year / 100);
	y = 0;
	if (year == 1582)
	{
		if (month == 10)
		{
			if (day >= 15)
			{
				y = 2 - x + (int)(x / 4);
			}
		}
		else if (month > 10)
		{
			y = 2 - x + (int)(x / 4);
		}
	}
	else if (year > 1582)
	{
		y = 2 - x + (int)(x / 4);
	}
	basedays = (int)(365.25 * (year + 16)) + 36525 * 47 + (int)(30.6001 * (month + 1)) + day + y - 2453069;
	return basedays;
}

/*
 * ���С�ڵ��ڸ���������
 */
int int2(double v)
{
	int a = (int)v;
	if (v < 0)
	{
		double rm = GetDecimal(v);
		if (rm != 0)
		{
			a--;
		}
	}
	return a;
}

/*
 * ��ȡС�����֣��Ը���ȡ������
 */
double GetDecimal(double n)
{
	n -= (int)n;
	return n;
}

/*
 * ��С����ת����
 */
LONGTIME GetDate(double n)
{
	LONGTIME lt;
	double A, F, D;
	int x = 0;
	n += 0.5;
	x += 2;
	x *= 10;
	x += 4;
	x *= 10;
	x += 5;
	x *= 10;
	x += 1;
	lt.wYear = 0;
	lt.wMonth = 0;
	lt.wDay = 0;
	lt.wHour = 0;
	lt.wMinute = 0;
	lt.wSecond = 0;
	lt.wMillisecond = 0;
	x *= 10;
	x += 5;
	x *= 10;
	x += 4;
	x *= 10;
	x += 5;
	n += x;
	lt.wDayOfWeek = ((int2)(n + 1)) % 7;
	A = (int)n;
	F = n - A;
	if (A >= 2299161)
	{
		D = (int)((A - 1867216.25) / 36524.25);
		A += 1 + D - (int)(D / 4);
	}
	A += 1524;
	lt.wYear = (int)((double)(A - 122.1) / 365.25);
	D = A - (int)(365.25 * lt.wYear);
	lt.wMonth = (int)(D / 30.6001);
	lt.wDay = (int)(D - (int)(lt.wMonth * 30.6001));
	lt.wYear -= 4716;
	lt.wMonth--;
	if (lt.wMonth > 12)
	{
		lt.wMonth -= 12;
	}
	if (lt.wMonth <= 2)
	{
		lt.wYear++;
	}
	F *= 24;
	lt.wHour = (int)F;
	F -= lt.wHour;
	F *= 60;
	lt.wMinute = (int)F;
	F -= lt.wMinute;
	F *= 60;
	lt.wSecond = (int)F;
	F -= lt.wSecond;
	F *= 1000;
	lt.wMillisecond = (int)F;
	return lt;
}

/*
 * ũ���鹫��
 */
int GetGre(LUNARDATE LunarDate)
{
	int hang = LunarDate.iYear - start_year;
	int lie = LunarDate.wMonth + 1;
	int leap_month = -1;
	int i = 0;
	double ndays = 0.0;
	int ileapMonth = 0;
	int dMn = 0;
	LONGTIME lt;
	for (i = 0; i < 14; i++)
	{
		if (Yuexu[hang * 14 + i + 1] == Yuexu[hang * 14 + i])
		{
			leap_month = i - 1;//ũ������
			if (leap_month <= 0)
			{
				leap_month += 12;
			}
			break;
		}
	}
	if (leap_month == LunarDate.wMonth)
	{
		printf("��ǰ�·��Ƿ�Ϊ���£��������������롰Y�����������롰N����>");
		ileapMonth = getche();
		if (ileapMonth == 89 || ileapMonth == 121)
		{
			LunarDate.bIsLeap = true;
		}
		else if (ileapMonth == 78 || ileapMonth == 110)
		{
			LunarDate.bIsLeap = false;
		}
		printf("\r\n");
	}
	dMn = GetDaysOfMonth(LunarDate.iYear, LunarDate.wMonth, true, LunarDate.bIsLeap);
	if (dMn == -1)
	{
		printf("��ǰũ��������Ϣ�������������룺Year Month Day>");
		return 2;//���ش���
	}
	else
	{
		if (dMn < LunarDate.wDay)
		{
			if (LunarDate.bIsLeap)
			{
				printf("%d����%sֻ�� %d �죬���������룺Year Month Day>", LunarDate.iYear, mName[LunarDate.wMonth - 1], dMn);
			}
			else
			{
				printf("%d��%sֻ�� %d �죬���������룺Year Month Day>", LunarDate.iYear, mName[LunarDate.wMonth - 1], dMn);
			}
			return 1;
		}
	}
	if (leap_month != -1)
	{
		//��λ��ǰ��
		if (LunarDate.wMonth > leap_month)
		{
			lie++;
		}
		else
		{
			if (LunarDate.wMonth == leap_month && LunarDate.bIsLeap == true)
			{
				lie++;
			}
		}
	}
	ndays = Yueshou[hang * 15 + lie];
	ndays += LunarDate.wDay;
	ndays--;
	lt = GetDate(ndays);
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);				//��ȡ����̨���
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED);   	//����������ɫ��Ϊ��ɫ
	printf("\r\n%d (%s%s)�� [%s] ", LunarDate.iYear, tiangan[(LunarDate.iYear - 1984 + 9000) % 10], dizhi[(LunarDate.iYear - 1984 + 9000) % 12], shengxiao[(LunarDate.iYear - 1984 + 9000) % 12]);
	if (LunarDate.bIsLeap)
	{
		printf("��");
	}
	printf("%s%s ", mName[LunarDate.wMonth - 1], dName[LunarDate.wDay - 1]);
	SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);		//�ָ���ɫ
	printf("�Ĺ�������Ϊ��");
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED);
	printf("%d��%d��%d�� %s\r\n", lt.wYear, lt.wMonth, lt.wDay, Xingqi[lt.wDayOfWeek]);
	SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);		//�ָ���ɫ
	return 0;
}

/*
 * ��õ�ǰ����
 */
LONGTIME GetCurTime()
{
	SYSTEMTIME st;
	LONGTIME lt;
	GetSystemTime(&st);
	lt = SysTimeToLong(st);
	lt = GMTConvert(lt);
	return lt;
}

/*
 * ʱ��ṹ��ת��
 */
LONGTIME SysTimeToLong(SYSTEMTIME SystemTime)
{
	LONGTIME LongTime;
	LongTime.wYear = (long int)SystemTime.wYear;
	LongTime.wMonth = SystemTime.wMonth;
	LongTime.wDay = SystemTime.wDay;
	LongTime.wHour = SystemTime.wHour;
	LongTime.wMinute = SystemTime.wMinute;
	LongTime.wSecond = SystemTime.wSecond;
	LongTime.wMillisecond = SystemTime.wMilliseconds;
	LongTime.wDayOfWeek = SystemTime.wDayOfWeek;
	return LongTime;
}

/*
 * ʱ��ת��
 */
LONGTIME GMTConvert(LONGTIME OrigTime)
{
	//����ʱ��ת����ϵͳ��ǰʱ��
	int m_hour = 0, m_day = 0, m_month = 0, m_year = 0, m_minute = 0, m_second = 0, zone = 0;
	TIME_ZONE_INFORMATION stTimeZone;
	ZeroMemory(&stTimeZone, sizeof(TIME_ZONE_INFORMATION));
	GetTimeZoneInformation(&stTimeZone);//��ȡ��ǰʱ��
	zone = 0 - stTimeZone.Bias / 60;
	m_year = OrigTime.wYear;
	m_month = OrigTime.wMonth;
	m_day = OrigTime.wDay;
	m_hour = OrigTime.wHour;
	m_minute = OrigTime.wMinute;
	m_second = OrigTime.wSecond;
	if (m_hour >= 24 - zone)
	{
		//��Ҫ��һ��
		m_hour = m_hour - 24 + zone;
		if (OrigTime.wDayOfWeek < 7)
		{
			OrigTime.wDayOfWeek++;
		}
		else
		{
			OrigTime.wDayOfWeek = OrigTime.wDayOfWeek - 6;
		}
		if (IsLeapYear(m_year))
		{
			if (m_month == 2)
			{
				if (m_day == 29)
				{
					m_month++;
					m_day = 1;
				}
				else
				{
					m_day++;
				}
			}
			else if (m_month == 1 || m_month == 3 || m_month == 5 || m_month == 7 || m_month == 8 || m_month == 10)
			{
				if (m_day == 31)
				{
					m_month++;
					m_day = 1;
				}
				else
				{
					m_day++;
				}
			}
			else if (m_month == 4 || m_month == 6 || m_month == 9 || m_month == 11)
			{
				if (m_day == 30)
				{
					m_month++;
					m_day = 1;
				}
				else
				{
					m_day++;
				}
			}
			else if (m_month == 12)
			{
				if (m_day == 31)
				{
					m_month = 1;
					m_day = 1;
					m_year++;
				}
				else
				{
					m_day++;
				}
			}
		}
		else
		{
			if (m_month == 2)
			{
				if (m_day == 28)
				{
					m_month++;
					m_day = 1;
				}
				else
				{
					m_day++;
				}
			}
			else if (m_month == 1 || m_month == 3 || m_month == 5 || m_month == 7 || m_month == 8 || m_month == 10)
			{
				if (m_day == 31)
				{
					m_month++;
					m_day = 1;
				}
				else
				{
					m_day++;
				}
			}
			else if (m_month == 4 || m_month == 6 || m_month == 9 || m_month == 11)
			{
				if (m_day == 30)
				{
					m_month++;
					m_day = 1;
				}
				else
				{
					m_day++;
				}
			}
			else if (m_month == 12)
			{
				if (m_day == 31)
				{
					m_month = 1;
					m_day = 1;
					m_year++;
				}
				else
				{
					m_day++;
				}
			}
		}
	}
	else
	{
		m_hour = m_hour + zone;
	}
	OrigTime.wYear = m_year;
	OrigTime.wMonth = m_month;
	OrigTime.wDay = m_day;
	OrigTime.wHour = m_hour;
	OrigTime.wMinute = m_minute;
	OrigTime.wSecond = m_second;
	return OrigTime;
}

/*
 * �ж������������Ƿ�Ϊ����
 */
bool IsLeapYear(int nYear)
{
	if (nYear > 1582)
	{
		if (nYear % 4 == 0 && nYear % 100 != 0 || nYear % 400 == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
		return true;
	}
	else if (nYear > -4713)
	{
		if (nYear % 4 == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
		return true;
	}
	return false;
}

/*
 * ��ʾ��ʮ�Ľ���
 */
void ShowSolarTerms(int year)
{
	int hang = year - start_year;
	int lie = 3;//��������ʼ�㡣
	LONGTIME lt;
	printf("\r\n  ��������\t��������\t����ʱ��\t  ũ��\t\t����\r\n");
	printf("----------------------------------------------------------------------\r\n");
	for (lie; lie < 27; lie++)//��Ϊlie��ʼΪ3������24��������Ϊ26�����С��27
	{
		lt = GetDate(Jieqi[hang * 24 + lie]);
		printf("  %02d. ", lie - 2);
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);				//��ȡ����̨���
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED);   	//����������ɫ��Ϊ��ɫ
		printf("%s", jieqi[lie % 24]);
		SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
		printf("  \t%d-%d-%d\t%02d:%02d:%02d  ", lt.wYear, lt.wMonth, lt.wDay, lt.wHour, lt.wMinute, lt.wSecond);

		DateRefer(lt.wYear, lt.wMonth, lt.wDay, true);
		if (lie == 26)
		{
			printf("  %s\r\n", Xingqi[lt.wDayOfWeek]);
		}
		else
		{
			printf("  %s\r\n\r\n", Xingqi[lt.wDayOfWeek]);
		}
	}
	printf("----------------------------------------------------------------------\r\n");
}

/*
 * ��ù�������
 */
void Holiday(int month)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);				//��ȡ����̨���
	switch (month)
	{
	case 1:
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE);	//����
		printf("\n\t\t 1��1��Ԫ��(New Year's Day)\n");
		printf("\t\t 1�����һ�������չ�������\n\n");
		SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);		//�ָ�������ɫ
		break;
	case 2:
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE);	//����
		printf("\n\t\t 2��2��  ����ʪ����(World Wetlands Day)\n");
		printf("\t\t 2��14�� ���˽�(Valentine's Day)\n\n");
		SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);		//�ָ�������ɫ
		break;
	case 3:
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE);	//����
		printf("\n\t\t 3��3��  ȫ��������\n");
		printf("\t\t 3��5��  ����־Ը�߷�����\n");
		printf("\t\t 3��8��  ���ʸ�Ů��(International Women' Day)\n");
		printf("\t\t 3��9��  ����ĸ�׺���\n");
		printf("\t\t 3��12�� �й�ֲ����(China Arbor Day)\n");
		printf("\t\t 3��14�� ��ɫ���˽�(White Day)\n");
		printf("\t\t 3��14�� ���ʾ�����(International Policemen' Day)\n");
		printf("\t\t 3��15�� ����������Ȩ����(World Consumer Right Day)\n");
		printf("\t\t 3��21�� ����ɭ����(World Forest Day)\n");
		printf("\t\t 3��21�� ����˯����(World Sleep Day)\n");
		printf("\t\t 3��22�� ����ˮ��(World Water Day)\n");
		printf("\t\t 3��23�� ����������(World Meteorological Day)\n");
		printf("\t\t 3��24�� ������ν�˲���(World Tuberculosis Day)\n");
		printf("\t\t 3�����һ�������ܵ�����һ��Сѧ����ȫ������\n\n");
		SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);		//�ָ�������ɫ
		break;
	case 4:
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE);	//����
		printf("\n\t\t 4��1��  ���˽�(April Fools' Day)\n");
		printf("\t\t 4��5��  ������(Tomb-sweeping Day)\n");
		printf("\t\t 4��7��  ����������(World Health Day)\n");
		printf("\t\t 4��22�� ���������(World Earth Day)\n");
		printf("\t\t 4��26�� ����֪ʶ��Ȩ��(World Intellectual PropertyDay)\n\n");
		SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);		//�ָ�������ɫ
		break;
	case 5:
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE);	//����
		printf("\n\t\t 5��1��  �����Ͷ���(International Labour Day)\n");
		printf("\t\t 5��3��  ����������(World Asthma Day)\n");
		printf("\t\t 5��4��  �й������(Chinese Youth Day)\n");
		printf("\t\t 5��8��  �����ʮ����(World Red-Cross Day)\n");
		printf("\t\t 5��12�� ���ʻ�ʿ��(International Nurse Day)\n");
		printf("\t\t 5��15�� ���ʼ�ͥ��(International Family Day)\n");
		printf("\t\t 5��17�� ���������(World Telecommunications Day)\n");
		printf("\t\t 5��20�� ȫ��ѧ��Ӫ����\n");
		printf("\t\t 5��23�� ����ţ����(International Milk Day)\n");
		printf("\t\t 5��31�� ����������(World No-Smoking Day)\n");
		printf("\t\t 5�µڶ���������ĸ�׽�(Mother's Day)\n");
		printf("\t\t 5�µ�����������ȫ��������\n\n");
		SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);		//�ָ�������ɫ
		break;
	case 6:
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE);	//����
		printf("\n\t\t 6��1��  ���ʶ�ͯ��(International Children's Day)\n");
		printf("\t\t 6��5��  ���绷����(International Environment Day)\n");
		printf("\t\t 6��6��  ȫ��������\n");
		printf("\t\t 6��17�� ������λ�Į���͸ɺ���(World Day to combat desertification)\n");
		printf("\t\t 6��23�� ���ʰ���ƥ����(International Olympic Day)\n");
		printf("\t\t 6��25�� ȫ��������\n");
		printf("\t\t 6��26�� ���ʽ�����(International Day Against Drug Abuse and Illicit Trafficking)\n");
		printf("\t\t 6�µ����������ո��׽�(Father's Day)\n\n");
		SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);		//�ָ�������ɫ
		break;
	case 7:
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE);	//����
		printf("\n\t\t 7��1��  �й�������������(Anniversary of the Founding of the Chinese Communist Party)\n");
		printf("\t\t 7��1��  ���ʽ�����(International Architecture Day)\n");
		printf("\t\t 7��7��  �й�������ս��������\n");
		printf("\t\t 7��11�� �����˿���(World Population Day)\n\n");
		SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);		//�ָ�������ɫ
		break;
	case 8:
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE);	//����
		printf("\n\t\t 8��1��  �й������ž�������(Army Day)\n");
		printf("\t\t 8��12�� ���������(International Youth Day)\n\n");
		SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);		//�ָ�������ɫ
		break;
	case 9:
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE);	//����
		printf("\n\t\t 9��8��  ����ɨä��(International Anti-illiteracy Day)\n");
		printf("\t\t 9��10�� �й���ʦ��(Teacher's Day)\n");
		printf("\t\t 9��16�� �й��Խ�����\n");
		printf("\t\t 9��16�� ���ʳ����㱣����(International Day for the Preservation of the Ozone Layer)\n");
		printf("\t\t 9��20�� ȫ��������\n");
		printf("\t\t 9��21�� ����ͣ����(World Cease-fire Day)\n");
		printf("\t\t 9��27�� ����������(World Tourism Day)\n");
		printf("\t\t 9�µ��������ڶ����ʺ�ƽ��(International Peace Day)\n");
		printf("\t\t 9�µ�����������ȫ������������\n");
		printf("\t\t 9�µ��ĸ������չ������˽�(International Day of the Deaf)\n\n");
		SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);		//�ָ�������ɫ
		break;
	case 10:
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE);	//����
		printf("\n10��1��  �л����񹲺͹������(National Day)\n");
		printf("\t\t 10��1��  ����������(International Music Day)\n");
		printf("\t\t 10��1��  ������������(International Day of Older Persons)\n");
		printf("\t\t 10��4��  ���綯����(World Animal Day)\n");
		printf("\t\t 10��5��  �����ʦ��(World Teachers' Day)�����Ϲ��̿�����֯ȷ����\n");
		printf("\t\t 10��8��  ȫ����Ѫѹ��\n");
		printf("\t\t 10��9��  ����������(World Post Day)\n");
		printf("\t\t 10��10�� ���羫��������(World Mental Health Day)\n");
		printf("\t\t 10��14�� �����׼��(World Standards Day)\n");
		printf("\t\t 10��15�� ����ä�˽�(International Day of the Blind)\n");
		printf("\t\t 10��15�� ����ũ�帾Ů��(World Rural Women's Day)\n");
		printf("\t\t 10��16�� ������ʳ��(World Food Day)\n");
		printf("\t\t 10��17�� ��������ƶ����(International Day for the Eradication of Poverty)\n");
		printf("\t\t 10��24�� ���Ϲ���(United Nations Day)\n");
		printf("\t\t 10��24�� ���緢չ������(World Development Information Day)\n");
		printf("\t\t 10��28�� �й����Խ�����\n");
		printf("\t\t 10��29�� ���������������(International Biodiversity Day)\n");
		printf("\t\t 10��31�� ��ʥ��(Halloween)\n");
		printf("\t\t 10�µĵ�һ������һ����ס����(World Habitat Day)\n");
		printf("\t\t 10�µĵڶ�����˹һ���ô�ж���(Thanksgiving Day)\n");
		printf("\t\t 10�µڶ������������ʼ�����Ȼ�ֺ���(International Day for Natural Disaster Reduction)\n");
		printf("\t\t 10�µڶ������������簮����(World Sight Day)\n\n");
		SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);		//�ָ�������ɫ
		break;
	case 11:
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE);	//����
		printf("\n\t\t 11��8��  �й����߽�\n");
		printf("\t\t 11��9��  ����������\n");
		printf("\t\t 11��14�� ����������(World Diabetes Day)\n");
		printf("\t\t 11��17�� ���ʴ�ѧ����\n");
		printf("\t\t 11��25�� ���������Ը�Ů�ı�����(International Day For the elimination of Violence against Women)\n");
		printf("\t\t 11�����һ�������������ж���(Thanksgiving Day)\n\n");
		SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);		//�ָ�������ɫ
		break;
	case 12:
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE);	//����
		printf("\n\t\t 12��1��  ���簮�̲���(World AIDS Day)\n");
		printf("\t\t 12��3��  ����м�����(World Disabled Day)\n");
		printf("\t\t 12��4��  ȫ������������\n");
		printf("\t\t 12��9��  ����������(World Football Day)\n");
		printf("\t\t 12��25�� ʥ����(Christmas Day)\n");
		printf("\t\t 12��29�� ���������������(International Biological Diversity Day)\n\n");
		SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);		//�ָ�������ɫ
		break;
	}
}



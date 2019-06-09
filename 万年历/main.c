#include "head.h"
/*
 * 主函数
 */
int main()
{
	system("color f0");             //设置为白底
	int mode = 0;						//查询选择模式
	int year, month, day, dMn, days;	//输入的年月日以及天数
	int error_times = 0;				//输入的错误计次
	LUNARDATE lunar_date;
	LONGTIME lt, lt2;

	while (error_times < 5)
	{
		year = -1, month = -1, day = -1, dMn = -1, days = 9025910;
		//设置标题
		printf("\n\n\t\t\t    超级万年历(1840～2100)\n\n");
		lt = GetCurTime();				//获得当前时间
		hOut = GetStdHandle(STD_OUTPUT_HANDLE);						//获取控制台句柄
		SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED);   	//白底红字
		printf("\t\t\t   %d-%d-%d %02d:%02d:%02d %s\r\n\n", lt.wYear, lt.wMonth, lt.wDay, lt.wHour, lt.wMinute, lt.wSecond, Xingqi[lt.wDayOfWeek]);
		SetConsoleTextAttribute(hOut, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);   	//改回文字颜色，白底黑字
		SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED);
		printf("\t\t\t       ★");
		SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_BLUE);
		printf("★");
		SetConsoleTextAttribute(hOut, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
		printf("功能选择");
		SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE | FOREGROUND_GREEN);
		printf("★");
		SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE);
		printf("★          \n\n");
		SetConsoleTextAttribute(hOut, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);

		//输出菜单选项
		printf("\t\t-------------------------------------------------\n");
		printf("\t\t|\t*  1、查询农历。\t\t\t|\n\t\t|\t\t\t\t\t\t|\n\t\t|\t*  "
			"2、查询公历。\t\t\t|\n\t\t|\t\t\t\t\t\t|\n\t\t|\t*  "
			"3、显示月历。\t\t\t|\n\t\t|\t\t\t\t\t\t|\n\t\t|\t*  "
			"4、计算某天距今天的天数。\t\t|\n\t\t|\t\t\t\t\t\t|\n\t\t|\t*  "
			"5、查询距今天相应天数的日期。\t|\n\t\t|\t\t\t\t\t\t|\n\t\t|\t*  "
			"6、计算任意两天之间的天数差。        |\n\t\t|\t\t\t\t\t\t|\n\t\t|\t*  "
			"7、显示二十四节气。\t\t\t|\n\t\t|\t\t\t\t\t\t|\n\t\t|\t*  "
			"8、显示节日。\t\t\t|\n\t\t|\t\t\t\t\t\t|\n\t\t|\t*  "
			"0、退出。\t\t\t\t|\n");
		printf("\t\t-------------------------------------------------\n");
		printf("\t\t您的输入：");
		scanf("%d", &mode);
		system("cls");

		//无论选择哪项，都会在界面最上面显示当前时间
		lt = GetCurTime();
		SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE);
		printf("\t\t当前日期时间：%d-%d-%d %02d:%02d:%02d %s\r\n\r\n", lt.wYear, lt.wMonth, lt.wDay, lt.wHour, lt.wMinute, lt.wSecond, Xingqi[lt.wDayOfWeek]);
		SetConsoleTextAttribute(hOut, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
		switch (mode)
		{
		case 0:
			exit(1);
			//选项“1”
		case 1:
			printf("农历查询：\n\n");
			printf("请输入要查询的公历日期(输入格式为：年 月 日)：<Year Month Day>");
			while (1)
			{
				scanf("%d%d%d", &year, &month, &day);
				if (year <= start_year || year > end_year || month < 1 || month>12 || day < 1 || day>31)
				{
					error_times++;
					printf("您输入的日期有误，请重新输入（错误%d次/5次）：Year Month Day>", error_times);
					if (error_times >= 5)
					{
						printf("\r\n错误次数已达到上限，请按任意键退出程序。");
						getch();
						return 1;
					}
				}
				else
				{
					dMn = GetDaysOfMonth(year, month, false, false);//得到当前月份的实际天数
					if (day > dMn)
					{
						error_times++;
						printf("当前月份只有%d天。请重新输入（错误%d次/5次）：<Year Month Day>", dMn, error_times);
						if (error_times >= 5)
						{
							printf("\r\n错误次数已达到上限，请按任意键退出程序。");
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
			ShowCalendar(year, month, day);//显示月历
			DateRefer(year, month, day, false);//调用公历查询

			LONGTIME lt, lt2, lt3;
			double jq1, jq2;
			int index_jieqi = 0;				//节气序号
			int dM0 = Jizhun(year, month, 1);	//公历月首天数
			int hang = 0, lie = 0;				//行与列
			hang = year - start_year;			//当前年份所处数据表中的行号,从0开始
			for (index_jieqi = (month - 1) * 2; index_jieqi < 24; index_jieqi++)
			{
				jq1 = Jieqi[hang * 24 + index_jieqi];
				jq2 = Jieqi[hang * 24 + index_jieqi + 1];
				if (int2(jq1 + 0.5) <= (dM0 + 14) && int2(jq2 + 0.5) > (dM0 + 14))
				{
					break;
				}
			}

			//显示当月节气
			lt = GetDate(jq1);
			hOut = GetStdHandle(STD_OUTPUT_HANDLE);				//获取控制台句柄
			SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE);   	//更改文字颜色，为蓝色
			printf("\n\t%s：%d-%d-%d %02d:%02d:%02d   ", jieqi[(index_jieqi) % 24], lt.wYear,
				lt.wMonth, lt.wDay, lt.wHour, lt.wMinute, lt.wSecond);
			lt = GetDate(jq2);
			printf("%s：%d-%d-%d %02d:%02d:%02d\r\n\r\n", jieqi[(index_jieqi + 1) % 24], lt.wYear,
				lt.wMonth, lt.wDay, lt.wHour, lt.wMinute, lt.wSecond);
			SetConsoleTextAttribute(hOut, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
			break;
			//选项“2”
		case 2:
			printf("公历查询：\r\n\r\n");
			printf("请输入农历日期（如1987年闰六月十七则输入：1987 6 17，）（范围：1840～2100）\nYear Month Day>");
			while (1)
			{
				scanf("%d %d %d", &year, &month, &day);
				if (year <= start_year || year > end_year || month < 1 || month>12 || day < 1 || day>30)
				{
					error_times++;
					printf("您输入的日期有误，请重新输入（错误%d次/5次）：Year Month Day>", error_times);
					if (error_times >= 5)
					{
						printf("\r\n错误次数已达到上限，请按任意键退出程序。");
						system("pause >nul");
						return 1;
					}
				}
				else
				{
					//输入基本正确后，再判断输入天数是否超过当月天数
					lunar_date.iYear = year;
					lunar_date.wMonth = month;
					lunar_date.wDay = day;
					lunar_date.bIsLeap = false;
					if (GetGre(lunar_date) != 0)
					{
						error_times++;
						if (error_times >= 5)
						{
							printf("\r\n错误次数已达到上限，请按任意键退出程序。");
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
			printf("月历显示：\r\n\r\n");
			printf("请输入要查询的公历年月日(1840～2100)：Year Month Day>");
			while (1)
			{
				scanf("%d %d %d", &year, &month, &day);
				if (year <= start_year || year > end_year || month < 1 || month>12)
				{
					error_times++;
					printf("您输入的年月有误，请重新输入（错误%d次/5次）。Year Month>", error_times);
					if (error_times >= 5)
					{
						printf("\r\n错误次数已达到上限，请按任意键退出程序。");
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
			printf("计算某天距今天的天数：\r\n\r\n");
			printf("请输入日期：Year Month Day>");
			while (1)
			{
				scanf("%d %d %d", &year, &month, &day);
				if (year <= start_year || year > end_year || month > 12 || month < 1 || day>31 || day < 1)
				{
					error_times++;
					printf("您输入的日期有误，请重新输入（错误%d次/5次）：Year Month Day>", error_times);
					if (error_times >= 5)
					{
						printf("\r\n错误次数已达到上限，请按任意键退出程序。");
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
						printf("当前月份只有%d天。请重新输入（错误%d次/5次）：Year Month Day>", dMn, error_times);
						if (error_times >= 5)
						{
							printf("\r\n错误次数已达到上限，请按任意键退出程序。");
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
			hOut = GetStdHandle(STD_OUTPUT_HANDLE);				//获取控制台句柄
			if (dMn >= 0)
			{
				SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE);   	//更改文字颜色，为蓝色
				printf("%d-%d-%d", year, month, day);
				SetConsoleTextAttribute(hOut, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);		//恢复文字颜色
				printf(" 比今天（");
				SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE);		//更改文字颜色为蓝色
				printf("%d-%d-%d", lt.wYear, lt.wMonth, lt.wDay);
				SetConsoleTextAttribute(hOut, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
				printf("）晚【");
				SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE | FOREGROUND_RED);
				printf("%d", dMn);
				SetConsoleTextAttribute(hOut, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
				printf("】天\r\n\n\n\n");
			}
			else
			{
				SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE);  	//更改文字颜色，为蓝色
				printf("%d-%d-%d", year, month, day);
				SetConsoleTextAttribute(hOut, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);		//恢复文字颜色
				printf(" 比今天（");
				SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE);		//更改文字颜色为蓝色
				printf("%d-%d-%d", lt.wYear, lt.wMonth, lt.wDay);
				SetConsoleTextAttribute(hOut, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
				printf("）早【");
				SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE | FOREGROUND_RED);
				printf("%d", -dMn);
				SetConsoleTextAttribute(hOut, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
				printf("】天\r\n\n\n\n");
			}
			break;
		case 5:
			lt = GetCurTime();
			dMn = Jizhun(lt.wYear, lt.wMonth, lt.wDay);
			hOut = GetStdHandle(STD_OUTPUT_HANDLE);				//获取控制台句柄
			printf("查询距今天相应天数的日期（请输入距今天（%d-%d-%d）的天数  范围%d～%d）：", lt.wYear, lt.wMonth, lt.wDay, -dMn - 2451545, 6574364 - dMn);
			while (1)
			{
				scanf("%d", &days);
				if (days > (6574364 - dMn) || days < (-dMn - 2451545))
				{
					error_times++;
					printf("您输入的天数有误，请重新输入（错误%d次/5次）：Days>", error_times);
					if (error_times >= 5)
					{
						printf("\r\n错误次数已达到上限，请按任意键退出程序。");
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
			printf("距离今天（%d-%d-%d）【 %d 】天的日期为：", lt.wYear, lt.wMonth, lt.wDay, days);
			SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED);	//红字
			printf("\n%d-%d-%d  %s", lt2.wYear, lt2.wMonth, lt2.wDay, Xingqi[lt2.wDayOfWeek]);
			SetConsoleTextAttribute(hOut, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);		//恢复文字颜色
			printf("  或者为：");
			SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED);	//红字
			printf("%d-%d-%d  %s\r\n\n\n", lt3.wYear, lt3.wMonth, lt3.wDay, Xingqi[lt3.wDayOfWeek]);
			SetConsoleTextAttribute(hOut, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);		//恢复文字颜色
			break;
		case 6:
			printf("计算任意两天之间的天数差：\r\n\r\n");
			printf("请输入第一个日期：Year Month Day>");
			while (1)
			{
				scanf("%d %d %d", &year, &month, &day);
				if (year <= start_year || year > end_year || month > 12 || month < 1 || day>31 || day < 1)
				{
					error_times++;
					printf("您输入的日期有误，请重新输入第一个日期（错误%d次/5次）：Year Month Day>", error_times);
					if (error_times >= 5)
					{
						printf("\r\n错误次数已达到上限，请按任意键退出程序。");
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
						printf("当前月份只有%d天。请重新输入第一个日期（错误%d次/5次）：Year Month Day>", dMn, error_times);
						if (error_times >= 5)
						{
							printf("\r\n错误次数已达到上限，请按任意键退出程序。");
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
			printf("请输入第二个日期：Year Month Day>");
			while (1)
			{
				scanf("%d %d %d", &year, &month, &day);
				if (year <= start_year || year > end_year || month > 12 || month < 1 || day>31 || day < 1)
				{
					error_times++;
					printf("您输入的日期有误，请重新输入第二个日期（错误%d次/5次）：Year Month Day>", error_times);
					if (error_times >= 5)
					{
						printf("\r\n错误次数已达到上限，请按任意键退出程序。");
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
						printf("当前月份只有%d天。请重新输入第二个日期（错误%d次/5次）：Year Month Day>", dMn, error_times);
						if (error_times >= 5)
						{
							printf("\r\n错误次数已达到上限，请按任意键退出程序。");
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
			hOut = GetStdHandle(STD_OUTPUT_HANDLE);				//获取控制台句柄
			SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE);	//蓝字
			printf("\n%d-%d-%d ", lt2.wYear, lt2.wMonth, lt2.wDay);
			SetConsoleTextAttribute(hOut, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);		//恢复文字颜色
			printf("与");
			SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE);	//蓝字
			printf("%d-%d-%d ", year, month, day);
			SetConsoleTextAttribute(hOut, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);		//恢复文字颜色
			printf("相差 【");
			SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED);	//红字
			printf(" %d ", abs(days));
			SetConsoleTextAttribute(hOut, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);		//恢复文字颜色
			printf("】天。\r\n");
			break;
		case 7:
			printf("显示二十四节气：\r\n\r\n");
			printf("请输入要查询的年份（1840～2100）：");
			while (1)
			{
				scanf("%d", &year);
				if (year <= start_year || year > end_year)
				{
					error_times++;
					printf("您输入的年份有误，请重新输入（错误%d次/5次）：Year>", error_times);
					if (error_times >= 5)
					{
						printf("\r\n错误次数已达到上限，请按任意键退出程序。");
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
			printf("\t\t\t        显示节日\r\n\r\n");
			printf("\t\t========================================\n");
			printf("\n\t\t1、显示公历节日\t\t2、显示农历节日\n");
			printf("\n\t\t请选择：");
			int choice = 0;
			scanf("%d", &choice);
			system("cls"); //调用DOS清屏命令
			switch (choice)
			{
			case 1:
				printf("\n\t\t\t\t 公历节日查询\n\n");
				printf("\t\t =========================================\n");
				printf("\n");
				printf("\t\t 请输入要查询的月份:   ");
				while (1)
				{
					int month = 0;
					scanf("%d", &month);
					if (month < 0 || month>13)
					{
						printf("\t\t输入错误，请输入正确月份（1~12）:");
					}
					else
					{
						hOut = GetStdHandle(STD_OUTPUT_HANDLE);				//获取控制台句柄
						SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED);	//红字
						printf("\n\t\t\t\t%d月份的节日\n", month);
						SetConsoleTextAttribute(hOut, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);		//恢复文字颜色
						Holiday(month);
						break;
					}
				}
				break;
			case 2:
				printf("\n\t\t\t\t 农历节日查询\n\n");
				printf("\t\t===============================================\n");
				printf("\n");
				hOut = GetStdHandle(STD_OUTPUT_HANDLE);				//获取控制台句柄
				SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE);	//蓝字
				printf("\n\t\t农历正月初一   春节(the Spring Festival)\n");
				printf("\n\t\t农历正月十五   元宵节(Lantern Festival)\n");
				printf("\n\t\t农历五月初五   端午节(the Dragon-Boat Festival)\n");
				printf("\n\t\t农历七月初七   七夕节(中国情人节）(Double-Seventh Day)\n");
				printf("\n\t\t农历八月十五   中秋节(the Mid-Autumn Festival)\n");
				printf("\n\t\t农历九月初九   重阳节(the Double Ninth Festival)\n");
				printf("\n\t\t农历腊月初八   腊八节(the laba Rice Porridge Festival)\n");
				printf("\n\t\t农历腊月二十四 传统扫房日\n\n");
				SetConsoleTextAttribute(hOut, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);		//恢复文字颜色
				break;
			}
			break;
		default:
			error_times++;
			printf("您的输入有误，请重新输入（错误%d次/5次）。\r\n\r\n", error_times);
			if (error_times >= 5)
			{
				printf("\r\n错误次数已达到上限，请按任意键退出程序。");
				system("pause >nul");
				return 1;
			}
			break;
		}
		printf("请按任意键返回主菜单。");
		system("pause >nul");
		system("cls");
	}
	return 0;
}

/*
 * 打印出一个月的月历
 */
void ShowCalendar(int year, int month, int day)
{
	int dM0 = Jizhun(year, month, 1);		//公历月首天数
	int jd_day = dM0;						//用以查询公历月首所在农历月份
	int base_days = 0;					//基准日
	base_days = Jizhun(year, month, day);
	int dw0 = (dM0 + 142113) % 7;				//月首星期
	int idw = dw0;						//idw用于标记星期，用于第一行填充
	int dMn = GetDaysOfMonth(year, month, false, false);//本月总天数
	int hang = 0, lie = 0;					//行与列
	int Lyear = 0, Lmonth = 0, Lday = 0;		//农历年、月、日
	int nday0 = 1, nday1 = 1;				//nday0为公历,nday1为农历
	int lunar_ndays = 0;					//农历月总天数
	char* leap = "";						//闰月
	char* daxiao = "";					//大月或小月
	int dM0_lunar = 0, dM_lunar = 0;			//月首的农历
	int cal_item = 0;						//格子计数,从0开始且小于7
	bool isfirstline = true;				//标记第一行输出
	bool fillblanks = true;				//是否填充空格
	bool islunarcal = false;				//是否为农历计算
	double jq1, jq2;						//用于存放本月节气交节时间(此历中每个公历月有两个节气)
	int Lmonth_index = 0;					//农历月序
	int index_jieqi = 0;					//节气序号
	LONGTIME lt;						//时间结构体
	hang = year - start_year;				//当前年份所处数据表中的行号,从0开始
	lie = month - 1;						//考虑到查询的范围,所以月份减1为初始查询列号,农历月号与公历月号最多相差2

	//查询公历月首所在的农历月
	for (lie; lie < 15; lie++)				//注意数据一行有15列
	{

		if ((Yueshou[hang * 15 + lie - 1] <= dM0) && (Yueshou[hang * 15 + lie] > dM0))		//查找当前公历月首所在农历月
		{
			break;
		}
	}
	lie--;								//减掉for循环多加的1

	//闰月
	if (Yuexu[hang * 14 + lie - 1] == Yuexu[hang * 14 + lie])
	{
		leap = "闰";						//农历月序中出现两个相同的,则下个月为闰月,月名与前一月相同,在前加"闰"字
	}

	//判断此农历月有几天，如有30天，为“大月”；有29天，则为“小月”
	lunar_ndays = Yueshou[hang * 15 + lie + 1] - Yueshou[hang * 15 + lie];//农历月总天数
	if (lunar_ndays == 31)				//农历月大月31天,小月30天
	{
		daxiao = "大";
	}
	else if (lunar_ndays == 30)
	{
		daxiao = "小";
	}

	//计算月历中的第一天的农历日期
	Lyear = year;							//农历年
	Lmonth_index = hang * 14 + lie;			//农历月索引
	Lmonth = Yuexu[Lmonth_index] - 1;		//农历月,从十一月开始(即冬至所在农历月为首)
	if (Lmonth < 1)
	{
		Lmonth += 12;
	}
	if (Lmonth > 10 && ((hang * 14 + lie) % 14 < 2))
	{
		Lyear--;						//对于十一月和十二月的，年份应为上一年的
	}
	Lday = dM0 - Yueshou[hang * 15 + lie];		//农历日则是距农历月首的天数来算

	//计算节气日期所在位置
	dM0_lunar = Lday;						//农历月首所在的
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

	//开始打印日历
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);				//获取控制台句柄
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE | FOREGROUND_RED);   	//更改文字颜色，为粉色
	printf("\r\n\t\t公历  %d年%d月  %s%s\r\n\r\n", year, month, Xingqi[(base_days + 142113) % 7], leap);
	SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED);   	//更改文字颜色，为红色
	printf("  周日\t");
	SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	printf("  周一\t  周二\t  周三\t  周四\t  周五\t");
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED);   	//更改文字颜色，为红色
	printf("  周六\r\n");
	SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	printf("________________________________________________________\r\n");

	//以下for循环开始打印日期,对应星期
	for (cal_item = 0; cal_item < 7; cal_item++)
	{
		if (!islunarcal)    			//判断是否是农历
		{
			//公历填充表格
			if (fillblanks) 			//判断是否是空格
			{
				if (isfirstline && dw0 != 0)//第一天不为周日且在第一行
				{
					printf("   \t   ");//格式控制,下同
				}
				if (dw0 == 0)
				{
					printf("");
					cal_item = -1;		//本次没有任何填充，所以序号仍然是0，而下个for循环时，此值会递增，因此设置成-1
				}
				for (idw; idw > 1; idw--)
				{
					//填充空格，因为上一个if已经填充了一次，所以这里要少填充一次，条件控制到idw>1
					printf("\t   ");	//输出月首所在星期的前面几格
					cal_item++;			//当前填充位置往后移一格
				}
				//空格输出完毕，到日期输出
				idw = dw0;				//重新赋值公历月首所在星期,为了控制对应的农历输出
				fillblanks = false;		//取消填充空格
			}
			else
			{
				if (cal_item == 0)
				{
					printf("   ");		//格式控制,下同
				}
				printf("%d\t   ", nday0);
				nday0++;				//公历日序增加一天

				if (cal_item == 5 || cal_item == 6)		//星期六和星期日红色字体输出公历日期
				{
					handle = GetStdHandle(STD_OUTPUT_HANDLE);				//获取控制台句柄
					SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED);
				}
				else
				{
					SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
				}
				//如果日期大于当月的总天数
				if (nday0 > dMn)
				{
					printf("\r\n");
					cal_item = -1;			//for 循环之后立刻加一,因此赋为-1
					islunarcal = true;		//开始输出农历
				}
				if (cal_item == 6)
				{
					cal_item = -1;
					printf("\r\n");
					islunarcal = true;		//一行公历输出完成，转到农历输出
					if (isfirstline)
					{
						fillblanks = true;	//开始填充空格
					}
				}
			}
			//打印农历
		}
		else
		{
			if (fillblanks)
			{
				//农历填充空格
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

					printf("\t   ");	//填充首行农历前面空格，条件与公历不同，原因在于控制输出布局
					cal_item++;			//当前填充位置往后移一格
				}
				if (dw0 > 1)
				{
					printf("\t ");
					cal_item++;
				}
				fillblanks = false;		//停止填充空格
			}
			else
			{
				if (dM_lunar >= lunar_ndays)
				{
					//农历日超出本月天数,则为下一月
					//下一月重新查询
					Lmonth_index++;
					Lmonth = Yuexu[Lmonth_index] - 1;
					if (Lmonth < 1)
					{
						Lmonth += 12;
					}

					if (Lmonth > 10)
					{
						year--;		//对于十一月和十二月的，年份应为上一年的
					}
					lunar_ndays = Yueshou[hang * 15 + lie + 2] - Yueshou[hang * 15 + lie + 1];	//重新计算新的一个农历月天数
					dM_lunar = 0;		//从初一开始
				}
				//星期六和星期日红色字体输出农历日期
				if (cal_item == 0 || cal_item == 6)
				{
					handle = GetStdHandle(STD_OUTPUT_HANDLE);				//获取控制台句柄
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
					HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);		//获取控制台句柄
					SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED);   	//更改文字颜色，为红色
					printf("%s", jieqi[(index_jieqi) % 24]);					//如果当天有节气(jq1),则打印出节气名称
					SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
				}
				else if (int2(jq2 + 0.5) == jd_day)
				{
					if (cal_item == 0)
					{
						printf("  ");
					}
					HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);		//获取控制台句柄
					SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED);   	//更改文字颜色，为红色
					printf("%s", jieqi[(index_jieqi + 1) % 24]);					//如果当天有节气(jq2),则打印出节气名称
					SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
				}
				else
				{
					if (dM_lunar == 0)
					{
						if (Yuexu[Lmonth_index] == Yuexu[Lmonth_index - 1])
						{
							printf("闰");           //如果是闰月
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
							printf("大");
						}
						else
						{
							printf("小");
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
				jd_day++;			//基准日指向下一天
				dM_lunar++;			//农历日指向下一天
				nday1++;			//天所在序号递增，指向下一天
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
					cal_item = -1;		//for 循环之后立刻加一,因此赋为-1
					printf("\r\n\r\n");
					islunarcal = false;	//一行结束后开始转到公历输出
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
 * 计算当前月份的天数
 */
int GetDaysOfMonth(int year, int month, bool mode, bool bLeap)
{
	int dM0 = 0, dMn = 0;
	if (!mode)
	{
		dM0 = Jizhun(year, month, 1);				//月首天数
		if (month == 12)
		{
			dMn = Jizhun(++year, 1, 1) - dM0;			//元旦
		}
		else
		{
			dMn = Jizhun(year, ++month, 1) - dM0;		//下个月
		}
	}
	else
	{
		int leap_Month = -1;						//农历闰月所在位置
		int hang = year - start_year;				//所在行
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
				return -1;					//如果当前年份无闰月，而输入有闰月，则返回-1，以代表输入错误
			}
		}
		else
		{
			if (bLeap)
			{
				if (leap_Month != month)
				{
					return -1;			//当前年份有闰月，但并非当前输入月份
				}
			}
		}
		if (leap_Month != -1)
		{
			if (month > leap_Month)		//在当年闰月以及之后
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
	return dMn;//返回当前公历月份的天数
}

/*
 * 查询某天农历和节气
 */
void DateRefer(int year, int month, int day, bool SST)
{
	int Lyear = 0, Lmonth = 0, Lday = 0;
	int base_days = 0;			//基准日
	int hang = 0, lie = 0;			//行与列
	int i = 0, ijq0 = 0, ijq1 = 0;		//节气
	char* leap = "";				//闰月
	char* daxiao = "";			//大月或小月
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
	lie--;//减掉多加的1
	if (Yuexu[hang * 14 + lie - 1] == Yuexu[hang * 14 + lie])
	{
		leap = "闰";
	}
	if ((Yueshou[hang * 15 + lie + 1] - Yueshou[hang * 15 + lie]) == 31)
	{
		daxiao = "大";
	}
	else
	{
		daxiao = "小";
	}
	Lmonth = Yuexu[hang * 14 + lie] - 1;
	if (Lmonth < 1)
	{
		Lmonth += 12;
	}
	if (Lmonth > 10 && ((hang * 14 + lie) % 14 < 2))
	{
		Lyear--;//对于十一月和十二月的，年份应为上一年的
	}
	Lday = base_days - Yueshou[hang * 15 + lie];//从初一开始

	if (SST)        //SST为true时，显示农历不显示节气
	{
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);				//获取控制台句柄
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE | FOREGROUND_RED);   	//更改文字颜色，为粉色
		printf("%s%s年 %s%s(%s)%s", tiangan[(Lyear - 1984 + 9000) % 10],
			dizhi[(Lyear - 1984 + 9000) % 12], leap, mName[Lmonth - 1], daxiao, dName[Lday]);
		SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	}
	else
	{
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);				//获取控制台句柄
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE | FOREGROUND_RED);   	//更改文字颜色，为粉色
		printf("\n\t\t农历  %s%s[%s]年 %s%s（%s）%s\t\n", tiangan[(Lyear - 1984 + 9000) % 10],
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
					printf("\n\t今日节气：");
					HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);				//获取控制台句柄
					SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED);   	//更改文字颜色，为红色
					printf("%s", jieqi[i % 24]);
					SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
					printf(" 交节时间：");
					SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED);   	//更改文字颜色，为红色
					printf("%d-%d-%d %02d:%02d:%02d\r\n\r\n", lt.wYear, lt.wMonth, lt.wDay, lt.wHour, lt.wMinute, lt.wSecond);
					SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
				}
				else
				{
					printf("\n\t距离下一个节气『");
					HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);				//获取控制台句柄
					SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED);   	//更改文字颜色，为红色
					printf("%s", jieqi[(i + 1) % 24]);
					SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
					printf("』还有");
					SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED);   	//更改文字颜色，为红色
					printf("%d", ijq1 - base_days);
					SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
					printf("天\n");
				}
				break;
			}
		}
	}
}

/*
 * 计算出基准天
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
 * 获得小于等于该数的整数
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
 * 获取小数部分，对负数取负部分
 */
double GetDecimal(double n)
{
	n -= (int)n;
	return n;
}

/*
 * 将小数日转公历
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
 * 农历查公历
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
			leap_month = i - 1;//农历闰月
			if (leap_month <= 0)
			{
				leap_month += 12;
			}
			break;
		}
	}
	if (leap_month == LunarDate.wMonth)
	{
		printf("当前月份是否为闰月？（是闰月则输入“Y”，否则输入“N”）>");
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
		printf("当前农历闰月信息有误，请重新输入：Year Month Day>");
		return 2;//返回错误
	}
	else
	{
		if (dMn < LunarDate.wDay)
		{
			if (LunarDate.bIsLeap)
			{
				printf("%d年闰%s只有 %d 天，请重新输入：Year Month Day>", LunarDate.iYear, mName[LunarDate.wMonth - 1], dMn);
			}
			else
			{
				printf("%d年%s只有 %d 天，请重新输入：Year Month Day>", LunarDate.iYear, mName[LunarDate.wMonth - 1], dMn);
			}
			return 1;
		}
	}
	if (leap_month != -1)
	{
		//定位当前列
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
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);				//获取控制台句柄
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED);   	//更改文字颜色，为红色
	printf("\r\n%d (%s%s)年 [%s] ", LunarDate.iYear, tiangan[(LunarDate.iYear - 1984 + 9000) % 10], dizhi[(LunarDate.iYear - 1984 + 9000) % 12], shengxiao[(LunarDate.iYear - 1984 + 9000) % 12]);
	if (LunarDate.bIsLeap)
	{
		printf("闰");
	}
	printf("%s%s ", mName[LunarDate.wMonth - 1], dName[LunarDate.wDay - 1]);
	SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);		//恢复颜色
	printf("的公历日期为：");
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED);
	printf("%d年%d月%d日 %s\r\n", lt.wYear, lt.wMonth, lt.wDay, Xingqi[lt.wDayOfWeek]);
	SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);		//恢复颜色
	return 0;
}

/*
 * 获得当前日期
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
 * 时间结构体转换
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
 * 时区转换
 */
LONGTIME GMTConvert(LONGTIME OrigTime)
{
	//从零时区转换到系统当前时区
	int m_hour = 0, m_day = 0, m_month = 0, m_year = 0, m_minute = 0, m_second = 0, zone = 0;
	TIME_ZONE_INFORMATION stTimeZone;
	ZeroMemory(&stTimeZone, sizeof(TIME_ZONE_INFORMATION));
	GetTimeZoneInformation(&stTimeZone);//获取当前时区
	zone = 0 - stTimeZone.Bias / 60;
	m_year = OrigTime.wYear;
	m_month = OrigTime.wMonth;
	m_day = OrigTime.wDay;
	m_hour = OrigTime.wHour;
	m_minute = OrigTime.wMinute;
	m_second = OrigTime.wSecond;
	if (m_hour >= 24 - zone)
	{
		//需要加一天
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
 * 判断所传入的年份是否为闰年
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
 * 显示二十四节气
 */
void ShowSolarTerms(int year)
{
	int hang = year - start_year;
	int lie = 3;//从立春开始算。
	LONGTIME lt;
	printf("\r\n  节气名称\t交节日期\t交节时间\t  农历\t\t星期\r\n");
	printf("----------------------------------------------------------------------\r\n");
	for (lie; lie < 27; lie++)//因为lie初始为3，则算24个节气后，为26，因此小于27
	{
		lt = GetDate(Jieqi[hang * 24 + lie]);
		printf("  %02d. ", lie - 2);
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);				//获取控制台句柄
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED);   	//更改文字颜色，为红色
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
 * 获得公历节日
 */
void Holiday(int month)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);				//获取控制台句柄
	switch (month)
	{
	case 1:
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE);	//蓝字
		printf("\n\t\t 1月1日元旦(New Year's Day)\n");
		printf("\t\t 1月最后一个星期日国际麻风节\n\n");
		SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);		//恢复文字颜色
		break;
	case 2:
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE);	//蓝字
		printf("\n\t\t 2月2日  世界湿地日(World Wetlands Day)\n");
		printf("\t\t 2月14日 情人节(Valentine's Day)\n\n");
		SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);		//恢复文字颜色
		break;
	case 3:
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE);	//蓝字
		printf("\n\t\t 3月3日  全国爱耳日\n");
		printf("\t\t 3月5日  青年志愿者服务日\n");
		printf("\t\t 3月8日  国际妇女节(International Women' Day)\n");
		printf("\t\t 3月9日  保护母亲河日\n");
		printf("\t\t 3月12日 中国植树节(China Arbor Day)\n");
		printf("\t\t 3月14日 白色情人节(White Day)\n");
		printf("\t\t 3月14日 国际警察日(International Policemen' Day)\n");
		printf("\t\t 3月15日 世界消费者权益日(World Consumer Right Day)\n");
		printf("\t\t 3月21日 世界森林日(World Forest Day)\n");
		printf("\t\t 3月21日 世界睡眠日(World Sleep Day)\n");
		printf("\t\t 3月22日 世界水日(World Water Day)\n");
		printf("\t\t 3月23日 世界气象日(World Meteorological Day)\n");
		printf("\t\t 3月24日 世界防治结核病日(World Tuberculosis Day)\n");
		printf("\t\t 3月最后一个完整周的星期一中小学生安全教育日\n\n");
		SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);		//恢复文字颜色
		break;
	case 4:
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE);	//蓝字
		printf("\n\t\t 4月1日  愚人节(April Fools' Day)\n");
		printf("\t\t 4月5日  清明节(Tomb-sweeping Day)\n");
		printf("\t\t 4月7日  世界卫生日(World Health Day)\n");
		printf("\t\t 4月22日 世界地球日(World Earth Day)\n");
		printf("\t\t 4月26日 世界知识产权日(World Intellectual PropertyDay)\n\n");
		SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);		//恢复文字颜色
		break;
	case 5:
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE);	//蓝字
		printf("\n\t\t 5月1日  国际劳动节(International Labour Day)\n");
		printf("\t\t 5月3日  世界哮喘日(World Asthma Day)\n");
		printf("\t\t 5月4日  中国青年节(Chinese Youth Day)\n");
		printf("\t\t 5月8日  世界红十字日(World Red-Cross Day)\n");
		printf("\t\t 5月12日 国际护士节(International Nurse Day)\n");
		printf("\t\t 5月15日 国际家庭日(International Family Day)\n");
		printf("\t\t 5月17日 世界电信日(World Telecommunications Day)\n");
		printf("\t\t 5月20日 全国学生营养日\n");
		printf("\t\t 5月23日 国际牛奶日(International Milk Day)\n");
		printf("\t\t 5月31日 世界无烟日(World No-Smoking Day)\n");
		printf("\t\t 5月第二个星期日母亲节(Mother's Day)\n");
		printf("\t\t 5月第三个星期日全国助残日\n\n");
		SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);		//恢复文字颜色
		break;
	case 6:
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE);	//蓝字
		printf("\n\t\t 6月1日  国际儿童节(International Children's Day)\n");
		printf("\t\t 6月5日  世界环境日(International Environment Day)\n");
		printf("\t\t 6月6日  全国爱眼日\n");
		printf("\t\t 6月17日 世界防治荒漠化和干旱日(World Day to combat desertification)\n");
		printf("\t\t 6月23日 国际奥林匹克日(International Olympic Day)\n");
		printf("\t\t 6月25日 全国土地日\n");
		printf("\t\t 6月26日 国际禁毒日(International Day Against Drug Abuse and Illicit Trafficking)\n");
		printf("\t\t 6月第三个星期日父亲节(Father's Day)\n\n");
		SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);		//恢复文字颜色
		break;
	case 7:
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE);	//蓝字
		printf("\n\t\t 7月1日  中国共产党诞生日(Anniversary of the Founding of the Chinese Communist Party)\n");
		printf("\t\t 7月1日  国际建筑日(International Architecture Day)\n");
		printf("\t\t 7月7日  中国人民抗日战争纪念日\n");
		printf("\t\t 7月11日 世界人口日(World Population Day)\n\n");
		SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);		//恢复文字颜色
		break;
	case 8:
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE);	//蓝字
		printf("\n\t\t 8月1日  中国人民解放军建军节(Army Day)\n");
		printf("\t\t 8月12日 国际青年节(International Youth Day)\n\n");
		SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);		//恢复文字颜色
		break;
	case 9:
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE);	//蓝字
		printf("\n\t\t 9月8日  国际扫盲日(International Anti-illiteracy Day)\n");
		printf("\t\t 9月10日 中国教师节(Teacher's Day)\n");
		printf("\t\t 9月16日 中国脑健康日\n");
		printf("\t\t 9月16日 国际臭氧层保护日(International Day for the Preservation of the Ozone Layer)\n");
		printf("\t\t 9月20日 全国爱牙日\n");
		printf("\t\t 9月21日 世界停火日(World Cease-fire Day)\n");
		printf("\t\t 9月27日 世界旅游日(World Tourism Day)\n");
		printf("\t\t 9月第三个星期二国际和平日(International Peace Day)\n");
		printf("\t\t 9月第三个星期六全国国防教育日\n");
		printf("\t\t 9月第四个星期日国际聋人节(International Day of the Deaf)\n\n");
		SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);		//恢复文字颜色
		break;
	case 10:
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE);	//蓝字
		printf("\n10月1日  中华人民共和国国庆节(National Day)\n");
		printf("\t\t 10月1日  国际音乐日(International Music Day)\n");
		printf("\t\t 10月1日  国际老年人日(International Day of Older Persons)\n");
		printf("\t\t 10月4日  世界动物日(World Animal Day)\n");
		printf("\t\t 10月5日  世界教师日(World Teachers' Day)（联合国教科文组织确立）\n");
		printf("\t\t 10月8日  全国高血压日\n");
		printf("\t\t 10月9日  世界邮政日(World Post Day)\n");
		printf("\t\t 10月10日 世界精神卫生日(World Mental Health Day)\n");
		printf("\t\t 10月14日 世界标准日(World Standards Day)\n");
		printf("\t\t 10月15日 国际盲人节(International Day of the Blind)\n");
		printf("\t\t 10月15日 世界农村妇女日(World Rural Women's Day)\n");
		printf("\t\t 10月16日 世界粮食日(World Food Day)\n");
		printf("\t\t 10月17日 国际消除贫困日(International Day for the Eradication of Poverty)\n");
		printf("\t\t 10月24日 联合国日(United Nations Day)\n");
		printf("\t\t 10月24日 世界发展新闻日(World Development Information Day)\n");
		printf("\t\t 10月28日 中国男性健康日\n");
		printf("\t\t 10月29日 国际生物多样性日(International Biodiversity Day)\n");
		printf("\t\t 10月31日 万圣节(Halloween)\n");
		printf("\t\t 10月的第一个星期一世界住房日(World Habitat Day)\n");
		printf("\t\t 10月的第二个星斯一加拿大感恩节(Thanksgiving Day)\n");
		printf("\t\t 10月第二个星期三国际减轻自然灾害日(International Day for Natural Disaster Reduction)\n");
		printf("\t\t 10月第二个星期四世界爱眼日(World Sight Day)\n\n");
		SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);		//恢复文字颜色
		break;
	case 11:
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE);	//蓝字
		printf("\n\t\t 11月8日  中国记者节\n");
		printf("\t\t 11月9日  消防宣传日\n");
		printf("\t\t 11月14日 世界糖尿病日(World Diabetes Day)\n");
		printf("\t\t 11月17日 国际大学生节\n");
		printf("\t\t 11月25日 国际消除对妇女的暴力日(International Day For the elimination of Violence against Women)\n");
		printf("\t\t 11月最后一个星期四美国感恩节(Thanksgiving Day)\n\n");
		SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);		//恢复文字颜色
		break;
	case 12:
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE);	//蓝字
		printf("\n\t\t 12月1日  世界爱滋病日(World AIDS Day)\n");
		printf("\t\t 12月3日  世界残疾人日(World Disabled Day)\n");
		printf("\t\t 12月4日  全国法制宣传日\n");
		printf("\t\t 12月9日  世界足球日(World Football Day)\n");
		printf("\t\t 12月25日 圣诞节(Christmas Day)\n");
		printf("\t\t 12月29日 国际生物多样性日(International Biological Diversity Day)\n\n");
		SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);		//恢复文字颜色
		break;
	}
}



#include "head.h"

int main()
{
	welcomeToGame();
	return 0;
}

int color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);//更改文字颜色
	return 0;
}

void gotoxy(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);//设置光标位置
}

/*
*   字符画---蛇
*/
void printSnake()
{
	gotoxy(35, 1);
	color(6);
	printf("/^\\/^\\");      //蛇眼睛

	gotoxy(34, 2);
	printf("|__|  O|");      //蛇眼睛

	gotoxy(33, 2);
	color(2);
	printf("_");

	gotoxy(25, 3);
	color(12);
	printf("\\/");      	//蛇信

	gotoxy(31, 3);
	color(2);
	printf("/");

	gotoxy(37, 3);
	color(6);
	printf(" \\_/");     	//蛇眼睛

	gotoxy(41, 3);
	color(10);
	printf(" \\");

	gotoxy(26, 4);
	color(12);
	printf("\\____");   	//舌头

	gotoxy(32, 4);
	printf("_________/");

	gotoxy(31, 4);
	color(2);
	printf("|");

	gotoxy(43, 4);
	color(10);
	printf("\\");

	gotoxy(32, 5);
	color(2);
	printf("\\_______");    //蛇嘴

	gotoxy(44, 5);
	color(10);
	printf("\\");

	gotoxy(39, 6);
	printf("|     |                  \\");  //下面都是画蛇身

	gotoxy(38, 7);
	printf("/      /                   \\");

	gotoxy(37, 8);
	printf("/      /                    \\ \\");

	gotoxy(35, 9);
	printf("/      /                       \\ \\");

	gotoxy(34, 10);
	printf("/     /                          \\  \\");

	gotoxy(33, 11);
	printf("/     /             _----_         \\   \\");

	gotoxy(32, 12);
	printf("/     /           _-~      ~-_         |  |");

	gotoxy(31, 13);
	printf("(      (        _-~    _--_    ~-_     _/  |");

	gotoxy(32, 14);
	printf("\\     ~-____-~    _-~    ~-_    ~-_-~    /");

	gotoxy(33, 15);
	printf("~-_           _-~          ~-_       _-~");

	gotoxy(35, 16);
	printf("~--______-~                ~-___-~");
}

void welcomeToGame()
{
	int n;
	int i, j;
	while (1)
	{
		printSnake();
		gotoxy(43, 18);
		color(11);//水绿色
		printf("贪 吃 蛇 大 作 战");
		color(14);//黄色
		for (i = 20; i <= 26; ++i)	//绘制边框
		{
			for (j = 27; j <= 74; ++j)
			{
				gotoxy(j, i);
				if (i == 20 || i == 26)
					printf("-");
				else if (j == 27 | j == 74)
					printf("|");
			}
		}
		color(12);
		gotoxy(35, 22);
		printf("1.开始游戏");
		gotoxy(55, 22);
		printf("2.游戏说明");
		gotoxy(35, 24);
		printf("3.退出游戏");
		gotoxy(40, 28);
		color(3);
		printf("请选择[1 2 3]:[ ]\b\b");        //\b为退格，使得光标处于[]中间
		color(14);
		scanf("%d", &n);    		//输入选项
		switch (n)
		{
		case 1:
			system("cls");
			createMap();//绘制表
			initSnake();
			createFood();
			keyBoardControl();
			break;
		case 2:
			explation();
			break;
		case 3:
			exit(0);
			break;
		default:
			color(12);
			gotoxy(40, 28);
			printf("请输入1-3之间的数!按任意键返回");
			getch();			//输入任意键
			system("cls");		//清屏
		}
	}
}

/*
 * 创建地图
 */
void createMap()
{
	int i, j;
	color(5);			//深紫色的边框
	for (i = 0; i < 58; i += 2)		//打印上下边框
	{
		gotoxy(i, 0);
		printf("□");
		gotoxy(i, 26);
		printf("□");
	}
	for (i = 1; i < 26; i++)		//打印左右边框
	{
		gotoxy(0, i);
		printf("□");
		gotoxy(56, i);
		printf("□");
	}
	color(3);
	for (i = 2; i < 56; i += 2)	//打印中间网格
	{
		for (j = 1; j < 26; j++)
		{
			gotoxy(i, j);
			printf("■");
		}
	}
}

/*
 *  游戏界面右侧的得分和小提示
 */
void scoreAndTips()
{
	file_out();//读取文件高分记录
	gotoxy(70, 4);
	color(11);
	printf("☆最高记录☆：%d", g_highScore);
	gotoxy(70, 8);
	color(14);
	printf("得分：%d  ", g_score);
	color(12);
	gotoxy(75, 11);
	printf("小 提 示");
	gotoxy(70, 13);
	color(6);
	printf("╬ ┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅ ╬");
	gotoxy(70, 25);
	printf("╬ ┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅ ╬");
	color(15);
	gotoxy(70, 14);
	printf("每个食物得分：%d分", g_add);
	gotoxy(70, 16);
	printf("不能撞墙，不能咬到自己");
	gotoxy(70, 18);
	printf("用↑ ↓ ← →分别控制蛇的移动");
	gotoxy(70, 20);
	printf("F1键加速，F2键减速");
	gotoxy(70, 22);
	printf("空格键暂停游戏");
	gotoxy(70, 24);
	printf("Esc键退出游戏");
}

void file_out()
{
	FILE* fp;
	fp = fopen("save.txt", "a+");
	fscanf(fp, "%d", &g_highScore);
	fclose(fp);
}

/*
 * 初始化蛇身，画蛇身
 */
void initSnake()
{
	SnakeLink tail;
	int i;
	tail = (Snake*)malloc(sizeof(Snake));//从蛇尾开始，头插法，以x,y设定开始的位置
	tail->x = 24;         	//蛇的初始位置（24,5）
	tail->y = 5;
	tail->next = NULL;
	for (i = 1; i <= 4; i++)       //设置蛇身，长度为5
	{
		g_head = (Snake*)malloc(sizeof(Snake)); //初始化蛇头
		g_head->next = tail;        //蛇头的下一位为蛇尾
		g_head->x = 24 + 2 * i;         //设置蛇头位置
		g_head->y = 5;
		tail = g_head;              //蛇头变成蛇尾，然后重复循环
	}
	while (tail != NULL)		//从头到尾，输出蛇身
	{
		gotoxy(tail->x, tail->y);
		color(14);
		printf("★");       //输出蛇身，蛇身使用★组成
		tail = tail->next;    //蛇头输出完毕，输出蛇头的下一位，一直输出到蛇尾
	}
}

/*
 * 随机出现食物
 */
void createFood()
{
	SnakeLink food_1;
	srand((unsigned)time(NULL));        	//初始化随机数
	food_1 = (Snake*)malloc(sizeof(Snake));   //初始化food_1
	while ((food_1->x % 2) != 0)    				//保证其为偶数，使得食物能与蛇头对其，然后食物会出现在网格线上
	{												//食物的x坐标在2-53
		food_1->x = rand() % 52 + 2;              //食物随机出现
	}
	food_1->y = rand() % 24 + 1;//食物的y坐标在1-24
	g_q = g_head;
	while (g_q->next == NULL)
	{
		if (g_q->x == food_1->x && g_q->y == food_1->y) //判断蛇身是否与食物重合
		{
			free(food_1);               //如果蛇身和食物重合，那么释放食物指针
			createFood();               //重新创建食物
			return;
		}
		g_q = g_q->next;
	}
	gotoxy(food_1->x, food_1->y);
	g_food = food_1;
	color(12);
	printf("●");           //输出食物
}

/*
	判断是否咬到自己
*/
int biteSelf()
{	//蛇头和任意结点重合，就是咬到自己
	SnakeLink self;
	self = g_head->next;//蛇头之外的结点
	while (self != NULL)
	{
		if (self->x == g_head->x && self->y == g_head->y)
		{
			return 1;
		}
		self = self->next;
	}
	return 0;
}

/*
	判断是否撞墙
*/
void crossWall()
{
	if (g_head->x == 0 || g_head->x == 56 || g_head->y == 0 || g_head->y == 26)
	{
		g_endGamesStatus = 1;
		endGame();
	}
}

/*
	加速，吃到食物或者F1加速
*/
void speedUp()
{
	if (g_sleepTime >= 50)
	{
		g_sleepTime -= 10;
		g_add += 2;
		if (g_sleepTime == 320)
		{
			g_add = 2;//防止减到1再加回来有错误
		}
	}
}

/*
	减速，F2减速
*/
void speedDown()
{
	if (g_sleepTime < 350)
	{
		g_sleepTime += 30;
		g_add -= 2;
		if (g_sleepTime == 350)
		{
			g_add = 1;//保证最低分1
		}
	}
}

/*
	控制方向
*/
void snakeMove()
{
	SnakeLink nextHead;
	crossWall();
	nextHead = (Snake*)malloc(sizeof(Snake));
	if (g_status == U)
	{
		nextHead->x = g_head->x;
		nextHead->y = g_head->y - 1;
		nextHead->next = g_head;
		g_head = nextHead;
		g_q = g_head;//指向蛇头,加一个结点
		if (nextHead->x == g_food->x && nextHead->y == g_food->y)
		{
			while (g_q != NULL)
			{
				gotoxy(g_q->x, g_q->y);
				color(14);
				printf("★");
				g_q = g_q->next;
			}
			g_score += g_add;
			createFood();
		}
		else
		{
			while (g_q->next->next != NULL)
			{
				gotoxy(g_q->x, g_q->y);
				color(14);
				printf("★");
				g_q = g_q->next;
			}
			gotoxy(g_q->next->x, g_q->next->y);
			color(3);
			printf("■");
			free(g_q->next);//释放最后一个结点
			g_q->next = NULL;
		}
	}
	if (g_status == D)
	{
		nextHead->x = g_head->x;
		nextHead->y = g_head->y + 1;
		nextHead->next = g_head;
		g_head = nextHead;
		g_q = g_head;//指向蛇头
		if (nextHead->x == g_food->x && nextHead->y == g_food->y)
		{
			while (g_q != NULL)
			{
				gotoxy(g_q->x, g_q->y);
				color(14);
				printf("★");
				g_q = g_q->next;
			}
			g_score += g_add;
			createFood();
		}
		else
		{
			while (g_q->next->next != NULL)
			{
				gotoxy(g_q->x, g_q->y);
				color(14);
				printf("★");
				g_q = g_q->next;
			}
			gotoxy(g_q->next->x, g_q->next->y);
			color(3);
			printf("■");
			free(g_q->next);
			g_q->next = NULL;
		}
	}
	if (g_status == L)
	{
		nextHead->x = g_head->x - 2;
		nextHead->y = g_head->y;
		nextHead->next = g_head;
		g_head = nextHead;
		g_q = g_head;//指向蛇头
		if (nextHead->x == g_food->x && nextHead->y == g_food->y)
		{
			while (g_q != NULL)
			{
				gotoxy(g_q->x, g_q->y);
				color(14);
				printf("★");
				g_q = g_q->next;
			}
			g_score += g_add;
			createFood();
		}
		else
		{
			while (g_q->next->next != NULL)
			{
				gotoxy(g_q->x, g_q->y);
				color(14);
				printf("★");
				g_q = g_q->next;
			}
			gotoxy(g_q->next->x, g_q->next->y);
			color(3);
			printf("■");
			free(g_q->next);
			g_q->next = NULL;
		}
	}
	if (g_status == R)
	{
		nextHead->x = g_head->x + 2;
		nextHead->y = g_head->y;
		nextHead->next = g_head;
		g_head = nextHead;
		g_q = g_head;//指向蛇头
		if (nextHead->x == g_food->x && nextHead->y == g_food->y)
		{
			while (g_q != NULL)
			{
				gotoxy(g_q->x, g_q->y);
				color(14);
				printf("★");
				g_q = g_q->next;
			}
			g_score += g_add;
			createFood();
		}
		else
		{
			while (g_q->next->next != NULL)
			{
				gotoxy(g_q->x, g_q->y);
				color(14);
				printf("★");
				g_q = g_q->next;
			}
			gotoxy(g_q->next->x, g_q->next->y);
			color(3);
			printf("■");
			free(g_q->next);
			g_q->next = NULL;
		}
	}
	if (biteSelf() == 1)
	{
		g_endGamesStatus = 2;
		endGame();
	}
}

/*
	控制键盘键
*/
void keyBoardControl()
{
	g_status = R;
	while (1)
	{
		scoreAndTips();
		if (GetAsyncKeyState(VK_UP) && g_status != D)
		{
			g_status = U;
		}
		if (GetAsyncKeyState(VK_DOWN) && g_status != U)
		{
			g_status = D;
		}
		if (GetAsyncKeyState(VK_LEFT) && g_status != R)
		{
			g_status = L;
		}
		if (GetAsyncKeyState(VK_RIGHT) && g_status != L)
		{
			g_status = R;
		}
		if (GetAsyncKeyState(VK_SPACE))
		{
			while (1)
			{
				Sleep(300);
				if (GetAsyncKeyState(VK_SPACE))
				{
					break;
				}
			}
		}
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			g_endGamesStatus = 3;
			endGame();
			break;
		}
		if (GetAsyncKeyState(VK_F1))
		{
			speedUp();
		}
		if (GetAsyncKeyState(VK_F2))
		{
			speedDown();
		}
		Sleep(g_sleepTime);
		snakeMove();
	}
}
/*
 * 失败界面
 */
void lostDraw()
{
	system("cls");
	int i;
	gotoxy(45, 2);
	color(6);
	printf("\\\\\\|///");
	gotoxy(43, 3);
	printf("\\\\");
	gotoxy(47, 3);
	color(15);
	printf(".-.-");
	gotoxy(54, 3);
	color(6);
	printf("//");

	gotoxy(44, 4);
	color(14);
	printf("(");

	gotoxy(47, 4);
	color(15);
	printf(".@.@");

	gotoxy(54, 4);
	color(14);
	printf(")");

	gotoxy(17, 5);
	color(11);
	printf("+------------------------");

	gotoxy(35, 5);
	color(14);
	printf("oOOo");

	gotoxy(39, 5);
	color(11);
	printf("----------");

	gotoxy(48, 5);
	color(14);
	printf("(_)");

	gotoxy(51, 5);
	color(11);
	printf("----------");

	gotoxy(61, 5);
	color(14);
	printf("oOOo");

	gotoxy(65, 5);
	color(11);
	printf("-----------------+");

	for (i = 6; i <= 19; i++)        //竖边框
	{
		gotoxy(17, i);
		printf("|");
		gotoxy(82, i);
		printf("|");
	}

	gotoxy(17, 20);
	printf("+---------------------------------");

	gotoxy(52, 20);
	color(14);
	printf("☆☆☆〃");

	gotoxy(60, 20);
	color(11);
	printf("----------------------+");

}

/*
 * 结束游戏
 */
void endGame()
{
	system("cls");
	if (g_endGamesStatus == 1)
	{

		lostDraw();
		gotoxy(35, 9);
		color(12);
		printf("对不起，您撞到墙了。游戏结束！");
	}
	else if (g_endGamesStatus == 2)
	{

		lostDraw();
		gotoxy(35, 9);
		color(12);
		printf("对不起，您咬到自己了。游戏结束！");
	}
	else if (g_endGamesStatus == 3)
	{
		lostDraw();
		gotoxy(40, 9);
		color(12);
		printf("您已经结束了游戏。");
	}
	gotoxy(43, 12);
	color(13);
	printf("您的得分是 %d", g_score);

	if (g_score >= g_highScore)
	{
		color(10);
		gotoxy(33, 16);
		printf("创纪录啦！最高分被你刷新！！！");
		file_in();              //把最高分写进文件
	}
	else
	{
		color(10);
		gotoxy(33, 16);
		printf("继续努力,你离最高分还差：%d", g_highScore - g_score);
	}
	choose();
}

void choose()
{
	int n;
	gotoxy(25, 23);
	color(12);
	printf("重新玩一局-------1");
	gotoxy(52, 23);
	printf("不玩了，退出-------2");
	gotoxy(46, 25);
	color(11);
	printf("选择：");
	fflush(stdin);
	scanf("%d", &n);
	switch (n)
	{
	case 1:
		system("cls");          //清屏
		g_score = 0;                //分数归零
		g_sleepTime = 200;			//设定初始速度
		g_add = 10;				//使add设定为初值，吃一个食物得分10，然后累加
		printSnake();           //返回欢迎界面
		welcomeToGame();
		break;
	default:
		exit(0);                //退出游戏
		break;
	}
}

void file_in()
{
	FILE* fp;
	fp = fopen("save.txt", "w+");
	fprintf(fp, "%d", g_score);
	fclose(fp);
}

/*
*   游戏说明
*/
void explation()
{
	int i, j = 1;
	system("cls");
	color(13);
	gotoxy(44, 3);
	printf("游戏说明");
	color(2);
	for (i = 6; i <= 22; i++)   //输出上下边框===
	{
		for (j = 20; j <= 75; j++)  //输出左右边框||
		{
			gotoxy(j, i);
			if (i == 6 || i == 22) printf("=");
			else if (j == 20 || j == 75) printf("||");
		}
	}
	color(3);
	gotoxy(30, 8);
	printf("tip1: 不能撞墙，不能咬到自己");
	color(10);
	gotoxy(30, 11);
	printf("tip2: 用↑.↓.←.→分别控制蛇的移动");
	color(14);
	gotoxy(30, 14);
	printf("tip3: F1 为加速，F2 为减速");
	color(11);
	gotoxy(30, 17);
	printf("tip4: 按空格键暂停游戏，再按空格键继续");
	color(4);
	gotoxy(30, 20);
	printf("tip5: Esc ：退出游戏");
	color(15);
	gotoxy(30, 24);
	printf("按任意键返回：");
	getch();                //按任意键返回主界面
	system("cls");
	printSnake();
	welcomeToGame();
}
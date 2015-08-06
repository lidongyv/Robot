#include<iostream>
#include<string.h>
#include<random>
#include<time.h>
using namespace std;
//A 65
#define BLACK 0
#define WHITE 1
struct point{
	int x, y;
};
static point *moveList;//走步记录
static int board[19][19];//本地棋盘记录
static int moveNum =0;//棋盘落子数目

int analysis(int x, int y)
{
	return 1;
}
point * max(int valuelist[25][25]){
	
	point  a[1];
	a[0].x = 1;
	a[0].y = 1;
	return a;
}
void value(int x,int y)
{
	point static valueMove[25][25];//两步最多产生25*25种走法
	int static valueList[25][25];
	valueList[1][1] = analysis(x, y);//将各点估值赋给相应valueList
	point * temp=max(valueList);//将估值最大的两步valueMove赋予moveList,temp用于储存两步的位置便于使用valueMove中的数据

}
void possibleMove_t(int num){
	int static temp = 0;
	while (temp < 2)
	{
		if ((board[moveList[moveNum].x - 1][moveList[moveNum].y - 1] == 0) && (moveList[moveNum].x - 1 >= 0) && (moveList[moveNum].y - 1 >= 0))
		{
			board[moveList[moveNum].x - 1][moveList[moveNum].y - 1] = 1;
			moveNum++;
			moveList[moveNum].x = moveList[moveNum].x - 1;
			moveList[moveNum].y = moveList[moveNum].x - 1;
			temp++;
		}
		if (temp >= 2)//好想用goto...
			break;
		if ((board[moveList[moveNum].x][moveList[moveNum].y - 1] == 0) && (moveList[moveNum].x >= 0) && (moveList[moveNum].y - 1 >= 0))
		{
			board[moveList[moveNum].x][moveList[moveNum].y - 1] = 1;
			moveNum++;
			moveList[moveNum].x = moveList[moveNum].x;
			moveList[moveNum].y = moveList[moveNum].y - 1;
			temp++;
		}
		if (temp >= 2)
			break;
		if ((board[moveList[moveNum].x + 1][moveList[moveNum].y - 1] == 0) && (moveList[moveNum].x + 1 <= 18) && (moveList[moveNum].y - 1 >= 0))
		{
			board[moveList[moveNum].x + 1][moveList[moveNum].y - 1] = 1;
			moveNum++;
			moveList[moveNum].x = moveList[moveNum].x + 1;
			moveList[moveNum].y = moveList[moveNum].y - 1;
			temp++;
		}
		if (temp >= 2)
			break;

		if ((board[moveList[moveNum].x + 1][moveList[moveNum].y] == 0) && (moveList[moveNum].x + 1 <= 18) && (moveList[moveNum].y >= 0))
		{
			board[moveList[moveNum].x + 1][moveList[moveNum].y] = 1;
			moveNum++;
			moveList[moveNum].x = moveList[moveNum].x + 1;
			moveList[moveNum].y = moveList[moveNum].y;
			temp++;
		}
		if (temp >= 2)
			break;
		if ((board[moveList[moveNum].x + 1][moveList[moveNum].y + 1] == 0) && (moveList[moveNum].x <= 18) && (moveList[moveNum].y + 1 <= 18))
		{
			board[moveList[moveNum].x + 1][moveList[moveNum].y + 1] = 1;
			moveNum++;
			moveList[moveNum].x = moveList[moveNum].x + 1;
			moveList[moveNum].y = moveList[moveNum].y + 1;
			temp++;
		}
		if (temp >= 2)
			break;
		if ((board[moveList[moveNum].x][moveList[moveNum].y + 1] == 0) && (moveList[moveNum].x >= 0) && (moveList[moveNum].y + 1 <= 18))
		{
			board[moveList[moveNum].x][moveList[moveNum].y + 1] = 1;
			moveNum++;
			moveList[moveNum].x = moveList[moveNum].x;
			moveList[moveNum].y = moveList[moveNum].y + 1;
			temp++;
		}
		if (temp >= 2)
			break;
		if ((board[moveList[moveNum].x - 1][moveList[moveNum].y] == 0) && (moveList[moveNum].x - 1 >= 0) && (moveList[moveNum].y >= 0))
		{
			board[moveList[moveNum].x - 1][moveList[moveNum].y - 1] = 1;
			moveNum++;
			moveList[moveNum].x = moveList[moveNum].x - 1;
			moveList[moveNum].y = moveList[moveNum].y - 1;
			temp++;
		}
		if (temp <= 2)
			possibleMove_t(moveNum-1);

	}
	temp = 0;
}
void possibleMove(int board[][19])
{//注意假设下子之后需要去掉下的子知道选择出最佳
//搜索范围根据最后两步落子，或者进行全盘搜索，搜索算法需要具体实现
	static int flag = 0;
	flag++;
	while (flag <= 2)
	{
		for (int j = moveList[moveNum].x; j < moveList[moveNum].x + 5; j++)
			for (int k = moveList[moveNum].y; k < moveList[moveNum].y + 5; k++)
			{//注意判断边界减少计算
				value(j, k);
				moveNum++;
				board[j][k] = 1;
				possibleMove(board);
				board[j][k] = 0;
				moveNum--;
			}
	}
	flag = 0;
}
char * move(char *message)//更新本地棋盘并且产生下步落子
{
	moveList[moveNum].x = *(message + 0) - 65;
	moveList[moveNum].y = *(message + 1) - 65;
	board[moveList[moveNum].x][moveList[moveNum].y] = 1;
	moveNum++;
	//srand((unsigned)time(NULL));
	//*(message + 0) = 'A' + rand() % 19;
	//*(message + 1) = 'A' + rand() % 19;
	moveList[moveNum].x = *(message + 2) - 65;
	moveList[moveNum].y = *(message + 3) - 65;
	board[moveList[moveNum].x][moveList[moveNum].y] = 1;
	moveNum++;
	//*(message + 2) = 'A' + rand() % 19 +1;
	//*(message + 3) = 'A' + rand() % 19 +1;
	//moveNum++;
	//接下来的是根据估值进行落子
	//value函数需要进行进一步加工，包括生成所有可能部署并且进行估值选择最佳
	//此处仅进行简单测试不附加value函数具体实现
	//需要注意的是一次下两步棋两步棋使用递归进行调用

	//	possibleMove(board); 测试平台暂不使用
	//测试八个方向随意有空就下
	possibleMove_t(moveNum);

	message[0] = moveList[moveNum - 1].x + 65;
	message[1] = moveList[moveNum - 1].y + 65;
	message[2] = moveList[moveNum].x + 65;
	message[3] = moveList[moveNum].y + 65;
	
	printf("%s", message);
	return message;
}
void stopGame()
{}
void initialGame()
{
	for (int j = 0; j < 19; j++)
	for (int k = 0; k < 19; k++)
		board[j][k] = 0;
	//list[0] = NULL;
}
char * move()
{

	//char * message="jj@@";
	moveList[moveNum].x = 'J' - 65;
	moveList[moveNum].y = 'J' - 65;
	moveNum++;
	return "JJ@@";
}
int main(int argc, char *argv[])
{
	char *step;
	char message[256];
	char *engineName = "OUC-Engine";
	int computerSide;
	while (1)
	{
		fflush(stdout);
		fflush(stdin);
		//scanf_s("%s", message);
		//printf("%s", message);
		//gets_s(message);
		cin >> message;
	//	if (strcmp(message, "test") == 0)
	//		printf("aaa");
		if (strcmp(message, "move") == 0) //接收对手着法
		{
			cin >> message;//gets_s(message);//scanf_s("%s", message);
			step = move(message);//处理对手着法并生成着法，引擎需要实现这个函数
			printf("move %s\n", step);//输出引擎产生着法
		}
		else if (strcmp(message, "new") == 0)//建立新棋局
		{
			cin >> message;//gets_s(message);//scanf_s("%s", message);
			if (strcmp(message, "black") == 0)//执黑
				computerSide = BLACK;
			else//执白
				computerSide = WHITE;
			initialGame(); //初始化对弈，引擎需要实现这个函数
			if (strcmp(message, "black") == 0)
			{
				step = move();//产生第一手着法，引擎需要实现这个函数
				printf("move %s\n", step); //输出第一手着法
			}
		}
		else if (strcmp(message, "name?") == 0)//询问引擎名
		{
			printf("name %s\n", engineName);//应答引擎名
		}
		else if (strcmp(message, "end") == 0)
		{
			stopGame(); //停止对弈，引擎需要实现这个函数
		}
	}
	return 0;
}
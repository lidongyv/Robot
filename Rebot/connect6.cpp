#include<iostream>
#include<string.h>
#include<random>
#include<time.h>
#include <fstream>
//#include"Value.cpp"
using namespace std;

#define BLACK 1
#define WHITE 7
static int board[19][19];//本地棋盘记录 
static int TYPE;
#define NOSTONE 0
#define BYTE int
#define GRID_NUM 19
struct point{
	int x, y;
};
point moveList[400];//走步记录static 

int MoveNum = 0;//棋盘落子数目static 
int NumberOfMyRoad[7];
int NumberOfEnemyRoad[7];
int ScoreOfRoad[7] = { 0, 17, 78, 141, 788, 1030, 100000 };
//A 65
/*
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

	for(int k=0;k<7;k++)
	{
	NumberOfMyRoad[k]=0;
	NumberOfEnemyRoad[k]=0;
	}

	AnalysisHorizon(position,Type);
	AnalysisVertical(position,Type);
	AnalysisLeft(position,Type);
	AnalysisRight(position,Type);

	int score=0;

	if(NumberOfMyRoad[6] > 0)
	{//说明实现六子连珠，给此走法价值为100000，显然游戏也结束
	return 100000;
	}
	if(NumberOfEnemyRoad[4]>0 || NumberOfEnemyRoad[5]>0)
	{//此走法走完后，说明对方再走两子或一子就实现六子连珠，显然，此走法决不可取，给此走法价值为-100000
	return -100000;
	}
	//除去上面两种特殊情形，下面为一般情形
	for(int i=1;i<6;i++)
	score += (NumberOfMyRoad[i]-NumberOfEnemyRoad[i]) * ScoreOfRoad[i];

	return score;
}*/



void possibleMove_t(int moveNum){
	int static temp = 0;//static
	int i = 0;
	int value[3][10];
	srand(clock());
	int searchtime=0;
	while (temp < 2)
	{
		switch (rand() % 8)
	  {
		
		//以下函数可以推荐使用analysis函数进行独立编写
		case 0:
		if ((moveList[moveNum].x - 1 >= 0) && (moveList[moveNum].y - 1 >= 0) &&(board[moveList[moveNum].x - 1][moveList[moveNum].y - 1] == 0) )
		{
			board[moveList[moveNum].x - 1][moveList[moveNum].y - 1] = 1;
			moveList[MoveNum].x = moveList[moveNum].x - 1;
			moveList[MoveNum].y = moveList[moveNum].y - 1;
			temp++;
			MoveNum++;
			value[i][0] = rand();
			break;
			
		}
	//	if (temp >= 2)//好想用goto...
	//		break;
		case 1:
		if ((moveList[moveNum].x >= 0) && (moveList[moveNum].y - 1 >= 0) && (board[moveList[moveNum].x][moveList[moveNum].y - 1] == 0))
		{
			board[moveList[moveNum].x][moveList[moveNum].y - 1] = 1;
			moveList[MoveNum].x = moveList[moveNum].x;
			moveList[MoveNum].y = moveList[moveNum].y - 1;
			temp++; 
			MoveNum++;
			value[i][1] = rand();
			break;
		}
	//	if (temp >= 2)
	//		break;
		case 2:
		if ((moveList[moveNum].x + 1 <= 18) && (moveList[moveNum].y - 1 >= 0) && (board[moveList[moveNum].x + 1][moveList[moveNum].y - 1] == 0))
		{
			board[moveList[moveNum].x + 1][moveList[moveNum].y - 1] = 1;
			moveList[MoveNum].x = moveList[moveNum].x + 1;
			moveList[MoveNum].y = moveList[moveNum].y - 1;
			temp++; 
			MoveNum++;
			value[i][2] = rand();
			break;
		}
	//	if (temp >= 2)
		//	break;
		case 3:
		if ((moveList[moveNum].x + 1 <= 18) && (moveList[moveNum].y >= 0) && (board[moveList[moveNum].x + 1][moveList[moveNum].y] == 0))
		{
			board[moveList[moveNum].x + 1][moveList[moveNum].y] = 1;
		
			moveList[MoveNum].x = moveList[moveNum].x + 1;
			moveList[MoveNum].y = moveList[moveNum].y;
			temp++; 
			MoveNum++;
			value[i][3] = rand();
			break;
		}
	//	if (temp >= 2)
	//		break;
		case 4:
		if ( (moveList[moveNum].x +1<= 18) && (moveList[moveNum].y + 1 <= 18) && (board[moveList[moveNum].x + 1][moveList[moveNum].y + 1] == 0))
		{
			board[moveList[moveNum].x + 1][moveList[moveNum].y + 1] = 1;
			
			moveList[MoveNum].x = moveList[moveNum].x + 1;
			moveList[MoveNum].y = moveList[moveNum].y + 1;
			temp++; 
			MoveNum++;
			value[i][3] = rand();
			break;
		}
	//	if (temp >= 2)
	//		break;
		case 5:
		if ((moveList[moveNum].x >= 0) && (moveList[moveNum].y + 1 <= 18) && (board[moveList[moveNum].x][moveList[moveNum].y + 1] == 0))
		{
			board[moveList[moveNum].x][moveList[moveNum].y + 1] = 1;
			
			moveList[MoveNum].x = moveList[moveNum].x;
			moveList[MoveNum].y = moveList[moveNum].y + 1;
			temp++; 
			MoveNum++;
			value[i][5] = rand();
			break;
		}
	//	if (temp >= 2)
	//		break;
		case 6:
		if ((moveList[moveNum].x - 1 >= 0) && (moveList[moveNum].y +1 <= 18) && (board[moveList[moveNum].x - 1][moveList[moveNum].y+1] == 0))
		{
			board[moveList[moveNum].x - 1][moveList[moveNum].y + 1] = 1;
		
			moveList[MoveNum].x = moveList[moveNum].x - 1;
			moveList[MoveNum].y = moveList[moveNum].y + 1;
			temp++;	
			MoveNum++;
			value[i][6] = rand();
			break;
		}
		case 7:
			if ((moveList[moveNum].x - 1 >= 0) && (moveList[moveNum].y >= 0) && (board[moveList[moveNum].x - 1][moveList[moveNum].y] == 0))
			{
				board[moveList[moveNum].x - 1][moveList[moveNum].y ] = 1;

				moveList[MoveNum].x = moveList[moveNum].x - 1;
				moveList[MoveNum].y = moveList[moveNum].y ;
				temp++;	
				MoveNum++;
				value[i][7] = rand();
				break;
			}
		
		
		searchtime++;
		if (temp <= 2 && searchtime>5)
		{
		
			possibleMove_t(moveNum-1);
			temp = 2;
		
		}
	  }
		
	}
	temp = 0;
}
/*
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
}*/
char * move(char *message)//更新本地棋盘并且产生下步落子
{
	moveList[MoveNum].x = *(message + 0) - 65;
	moveList[MoveNum].y = *(message + 1) - 65;
	board[moveList[MoveNum].x][moveList[MoveNum].y] = 1;
	MoveNum++;
	//srand((unsigned)time(NULL));
	//*(message + 0) = 'A' + rand() % 19;
	//*(message + 1) = 'A' + rand() % 19;
	if (MoveNum>1){
		moveList[MoveNum].x = *(message + 2) - 65;
		moveList[MoveNum].y = *(message + 3) - 65;
		board[moveList[MoveNum].x][moveList[MoveNum].y] = 1;
		MoveNum++;
	}
	
	//*(message + 2) = 'A' + rand() % 19 +1;
	//*(message + 3) = 'A' + rand() % 19 +1;
	//moveNum++;
	//接下来的是根据估值进行落子
	//value函数需要进行进一步加工，包括生成所有可能部署并且进行估值选择最佳
	//此处仅进行简单测试不附加value函数具体实现
	//需要注意的是一次下两步棋两步棋使用递归进行调用

	//	possibleMove(board); 测试平台暂不使用
	//测试八个方向随意有空就下
	possibleMove_t(MoveNum-1);
	 message[2] = 'a';
	 message[3] = 'B';
	*(message + 0) = moveList[MoveNum - 2].x + 65 ;
	*(message + 1) = moveList[MoveNum - 2].y + 65 ;
	*(message + 2) = moveList[MoveNum - 1].x + 65 ;
	*(message + 3) = moveList[MoveNum - 1].y + 65 ;
	
	return  message;
}
void stopGame()
{
	ofstream out;
	out.open("./history.txt",ios::app);
	int i = 0;
	char temp[2];
	while (moveList[i].x != 0)
	{
		temp[0] = moveList[i].x + 65;
		temp[1] = moveList[i].y + 65;
		out <<temp[0]<<temp[1];
		if (i == 0)
			out << "@@";
		i++;
	}
	out << endl;


}
void initialGame()
{
	for (int j = 0; j < 19; j++)
	for (int k = 0; k < 19; k++)
		board[j][k] = 0;
	//list[0] = NULL;
	
}
char * move()
{
	moveList[MoveNum].x = 9;
	moveList[MoveNum].y = 9;
	board[moveList[MoveNum].x][moveList[MoveNum].y] = 1;
	MoveNum++;
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
			 step =  move(message);//处理对手着法并生成着法，引擎需要实现这个函数
			printf("move %s\n", step);//输出引擎产生着法
		}
		else if (strcmp(message, "new") == 0)//建立新棋局
		{
			cin >> message;//gets_s(message);//scanf_s("%s", message);
			if (strcmp(message, "black") == 0)//执黑
				TYPE = BLACK;
			else//执白
				TYPE = WHITE;
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
		else if (strcmp(message, "error") == 0)
		{
			stopGame(); //停止对弈，引擎需要实现这个函数
		
		}
	}
	return 0;
}
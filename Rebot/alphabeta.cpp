//基于内存
#include<iostream>
#include<string.h>
#include<random>
#include<time.h>
#include <fstream>
//#include"Value.cpp"
using namespace std;
#define infinity 1000000000
#define BLACK 1
#define WHITE 7
static int board[19][19];//本地棋盘记录 
static int TYPE;
#define NOSTONE 0
#define BYTE int
#define GRID_NUM 19
#define Depth 1

struct point{
	int x, y;
};
point best[800][2];
int bestmove;
int possiblecount[Depth];
point moveList[400];//走步记录static 
point possiblemove[Depth][800][2];
static int flag[Depth];
int MoveNum = 0;//棋盘落子数目static 
int NumberOfMyRoad[7];
int NumberOfEnemyRoad[7];
int ScoreOfRoad[7] = { 0, 17, 78, 141, 788, 1030, 100000 };




void AnalysisHorizon(int position[][19], int Type)
{
	for (int i = 0; i<19; i++)
	{
		for (int j = 0; j<14; j++)
		{
			int number = position[i][j] + position[i][j + 1] + position[i][j + 2] +
				position[i][j + 3] + position[i][j + 4] + position[i][j + 5];
			if (number == 0 || (number>6 && number % 7 != 0))
				continue;
			if (Type == BLACK)
			{
				if (number<7)
					NumberOfMyRoad[number]++;
				else
					NumberOfEnemyRoad[number / 7]++;
			}
			else
			{
				if (number>6)
					NumberOfMyRoad[number / 7]++;
				else
					NumberOfEnemyRoad[number]++;
			}
		}
	}
}
void AnalysisVertical(int position[][19], int Type)
{
	for (int j = 0; j<19; j++)
	{
		for (int i = 0; i<14; i++)
		{
			int number = position[i][j] + position[i + 1][j] + position[i + 2][j] +
				position[i + 3][j] + position[i + 4][j] + position[i + 5][j];
			if (number == 0 || (number>6 && number % 7 != 0))
				continue;

			if (Type == BLACK)
			{
				if (number<7)
					NumberOfMyRoad[number]++;
				else
					NumberOfEnemyRoad[number / 7]++;
			}
			else
			{
				if (number>6)
					NumberOfMyRoad[number / 7]++;
				else
					NumberOfEnemyRoad[number]++;
			}
		}
	}
}
void AnalysisLeft(int position[][19], int Type)
{
	for (int i = 5; i<19; i++)
	{
		for (int j = 5; j<19; j++)
		{
			int number = position[i][j] + position[i - 1][j - 1] + position[i - 2][j - 2] +
				position[i - 3][j - 3] + position[i - 4][j - 4] + position[i - 5][j - 5];
			if (number == 0 || (number>6 && number % 7 != 0))
				continue;

			if (Type == BLACK)
			{
				if (number<7)
					NumberOfMyRoad[number]++;
				else
					NumberOfEnemyRoad[number / 7]++;
			}
			else
			{
				if (number>6)
					NumberOfMyRoad[number / 7]++;
				else
					NumberOfEnemyRoad[number]++;
			}
		}
	}
}
void AnalysisRight(int position[][19], int Type)
{
	for (int i = 5; i<19; i++)
	{
		for (int j = 0; j<14; j++)
		{
			int number = position[i][j] + position[i - 1][j + 1] + position[i - 2][j + 2] +
				position[i - 3][j + 3] + position[i - 4][j + 4] + position[i - 5][j + 5];
			if (number == 0 || (number>6 && number % 7 != 0))
				continue;

			if (Type == BLACK)
			{
				if (number<7)
					NumberOfMyRoad[number]++;
				else
					NumberOfEnemyRoad[number / 7]++;
			}
			else
			{
				if (number>6)
					NumberOfMyRoad[number / 7]++;
				else
					NumberOfEnemyRoad[number]++;
			}
		}
	}
}

int evaluate(int board[][19] ,int Type){
	//srand(clock());
	//return rand();
	for (int k = 0; k<7; k++)
	{
		NumberOfMyRoad[k] = 0;
		NumberOfEnemyRoad[k] = 0;
	}

	AnalysisHorizon(board, Type);
	AnalysisVertical(board, Type);
	AnalysisLeft(board, Type);
	AnalysisRight(board, Type);

	int score = 0;

	if (NumberOfMyRoad[6] > 0)
	{//说明实现六子连珠，给此走法价值为100000，显然游戏也结束
		return 100000;
	}
	if (NumberOfEnemyRoad[4]>0 || NumberOfEnemyRoad[5]>0)
	{//此走法走完后，说明对方再走两子或一子就实现六子连珠，显然，此走法决不可取，给此走法价值为-100000
		return -100000;
	}
	//除去上面两种特殊情形，下面为一般情形
	for (int i = 1; i<6; i++)
		score += (NumberOfMyRoad[i] - NumberOfEnemyRoad[i]) * ScoreOfRoad[i];

	return score;
}

bool creatmove(int depth){

	possiblecount[depth-1] = 0;
	//for (int k = 0; k < 2;k++)
	int i, j, m, n;
	int wmax=0, wmin=18, hmax=0, hmin=18;
	for (i = 0; i < 19;i++)
		for (j = 0; j < 19;j++)
		if (board[i][j] != NOSTONE)
		{
			if (i>wmax)
				wmax = i;
			if (i < wmin)
				wmin = i;

			if (j>hmax)
				hmax = j;
			if (j < hmin)
				hmin = j;
		}
		if (wmax + 2<18)
			wmax = wmax+2;
		if (wmin - 2 > 0)
			wmin = wmin - 2;
		if (hmax + 2 < 18)
			hmax = hmax + 2;
		if (hmin - 2 > 0)
			hmin = hmin - 2;


		//FORMAL
	for (  i=wmin; i < wmax; i++)
	for (  j=hmin; j < hmax; j++)
	//TO TEST TIME	
		//for (i = wmin; i < wmin+2; i++)
		//for (j = hmin; j < wmin+2; j++)
	{	
		
		
		for ( m =wmin; m < wmax; m++)
		for ( n =hmin; n < hmax; n++)
		{
			if (board[i][j] == NOSTONE){

			possiblemove[depth-1][possiblecount[depth-1]][0].x = i;
			possiblemove[depth-1][possiblecount[depth-1]][0].y = j;
			if (depth == Depth)
		{
			best[possiblecount[depth - 1]][0].x = i;
			best[possiblecount[depth - 1]][0].y = j;
		}
			
		}

			if (board[m][n] == NOSTONE){

				possiblemove[depth - 1][possiblecount[depth - 1]][1].x = m;
				possiblemove[depth - 1][possiblecount[depth - 1]][1].y = n;
				if (depth == Depth)
				{
					best[possiblecount[depth - 1]][1].x = m;
					best[possiblecount[depth - 1]][1].y = n;

				}

			}

			possiblecount[depth - 1]++;
		}
		//possiblecount[depth-1]++;
	}

	if (possiblecount[depth-1] != 0)
		return 1;
	else
		return 0;
}
int typenimy(int type){

	if (TYPE == WHITE)
		return BLACK;
	else
		return WHITE;
}
bool makemove(int depth){//将节点添加到movelist然后添加到棋盘
	if (flag[depth] > possiblecount[depth])
		return false;
	moveList[MoveNum].x = possiblemove[depth][flag[depth]][0].x;
	moveList[MoveNum].y = possiblemove[depth][flag[depth]++][0].y;
	MoveNum++;
	moveList[MoveNum].x = possiblemove[depth][flag[depth]][1].x;
	moveList[MoveNum].y = possiblemove[depth][flag[depth]++][1].y;
	MoveNum++;
	if (depth % 2 == 1)
	{
		board[moveList[MoveNum - 2].x][moveList[MoveNum - 2].y] = TYPE;
		board[moveList[MoveNum - 1].x][moveList[MoveNum - 1].y] = TYPE;
	}
	else
	{
		board[moveList[MoveNum - 2].x][moveList[MoveNum - 2].y] = typenimy(TYPE);
		board[moveList[MoveNum - 1].x][moveList[MoveNum - 1].y] = typenimy(TYPE);
	}
	return true;
}
void unmove(){
	board[moveList[MoveNum - 2].x][moveList[MoveNum - 2].y] = 0;
	board[moveList[MoveNum - 1].x][moveList[MoveNum - 1].y] = 0;
	moveList[MoveNum-1].x = -1;
	moveList[MoveNum-1].y = -1;
	MoveNum--;
	moveList[MoveNum-1].x = -1;
	moveList[MoveNum-1].y = -1;
	MoveNum--;
}
int alphaBeta(int board[][19], int depth, int alpha, int beta)
{
	//to identity the type min or max use deep,deep is 3,so when deep%2=1 max
	//if you want to change deep ,then change the following code where is max and min
	int value=0;
	//flag[depth-1] = 0;

	if (depth == 0 )
	{
		value = evaluate(board,TYPE);
		return value;
	}

	
	creatmove(depth);
	{

		
		if (depth % 2 == 1)//max
		{
			while (makemove(depth-1))
			{
			//flag[depth-1]++;
			value = alphaBeta(board, depth - 1, alpha, beta);	
			unmove();
			if (value > beta)
				return beta;
				
			if (value > alpha)
			{
				if (depth == Depth)
				{
					bestmove = flag[depth - 1]-2;
				}
				alpha = value;
			}
				
			}
		}
		else
		{
			while (makemove( depth-1))
			{
			flag[depth]++;
			value = alphaBeta(board, depth - 1, alpha, beta);
			unmove();
			if (value < alpha)
				return alpha;
			if (value < beta)
			{
			if (depth == Depth)
			{
				bestmove = flag[depth - 1] - 2;
			}
				beta = value;
			}
			}
		}
	}
	

	return value;
}


void search(int num){
	int value;
	value = alphaBeta(board,Depth,-infinity,infinity);
	moveList[MoveNum].x = best[bestmove][0].x;
	moveList[MoveNum].y = best[bestmove][0].y;
	MoveNum++;
	moveList[MoveNum].x = best[bestmove + 1][1].x;
	moveList[MoveNum].y = best[bestmove + 1][1].y;
	MoveNum++;
}



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
	search(MoveNum-1);
	message[2] = 'a';
	message[3] = 'B';
	*(message + 0) = moveList[MoveNum - 2].x + 65;
	*(message + 1) = moveList[MoveNum - 2].y + 65;
	*(message + 2) = moveList[MoveNum - 1].x + 65;
	*(message + 3) = moveList[MoveNum - 1].y + 65;

	return  message;
}
void stopGame()
{
	ofstream out;
	out.open("./history.txt", ios::app);
	int i = 0;
	char temp[2];
	while (moveList[i].x != 0)
	{
		temp[0] = moveList[i].x + 65;
		temp[1] = moveList[i].y + 65;
		out << temp[0] << temp[1];
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
		board[j][k] = NOSTONE;
	//list[0] = NULL;
	for (int i = 0; i < 400; i++)
	{
		moveList[i].x = -1;
		moveList[i].y = -1;
	}

}
char * move()
{
	moveList[MoveNum].x = 9;
	moveList[MoveNum].y = 9;
	board[moveList[MoveNum].x][moveList[MoveNum].y] = 1;
	MoveNum++;
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
			step = move(message);//处理对手着法并生成着法，引擎需要实现这个函数
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
//基于CPU

#include<iostream>
#include<string.h>
#include<random>
#include<time.h>
#include <fstream>
using namespace std;
#define infinity 10000000000
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
point best[2];
int bestmove;
int possiblecount[Depth];
point moveList[400];//走步记录static 
point possiblemove[Depth][800][2];
static int flag[Depth];
int MoveNum = 0;//棋盘落子数目static 
int NumberOfMyRoad[7];
int NumberOfEnemyRoad[7];
int ScoreOfRoad[7] = { 0, 17, 78, 141, 788, 1030, 100000 };
int timeflag=1;



void AnalysisHorizon(int position[][19], int Type)
{;
	int i, j, m, n;
	//提取movelist信息，使用单步中心扫描
	i = moveList[MoveNum - 1].x;
	j = moveList[MoveNum - 1].y;
	m = moveList[MoveNum - 2].x;
	n = moveList[MoveNum - 2].y;
	/*
	if (i > m)
	{
		i = i + m;
		m = i - m;
		i = i - m;
	}
	if (j > n){
		j = j + n;
		n = j - n;
		n - j - n;
	}
	*/
	//中心估值测试
	//扫描横向，只扩展横向扫描区域
	//区域扫描法和中心扫描法的优缺点对比，中心扫描法可以缩小搜索范围到两个11*11的方格中，区域扫描法最多扫描一次19*19的方格
	//棋盘进化的概念，现有棋局都是在过去棋局的进化下产生的，而且假设是通过最优进化产生，六子棋与五子棋的不同之处在于六子棋每次进化两个阶段，综合两阶段的进化结果得到最优值为单步进化最优，采用中心扫描更易得到进化之后的估值，每次得到的num在++之前nun-1都要--，原因是最多在原有棋局上进化一个
	//优化中心扫描：按四个方向扫描，以线为分析基准
	//产生的弊端和优点：采用优化后的中心估值每次只需要扫描4*11次，但是这种扫描方法只适用于按路分析，对于按棋局分析仍然需要使用原有的扫描方法
	//中心扫描和区域扫描比较和结合：待分析
	//if (i - 5 < 0)
	//	i = 0;
	//else i -= 5;
	if (j - 5 < 0)
		j = 0;
	else j -= 5;
	//if (m + 5 > 18)
	//	m = 18;
	//else m += 5;
	if (n + 5 > 18)
		n = 18;
	else n += 5;
	for ( i ; i < m; i++)
	{
		for ( j ; j < n; j++)
		{
			int number = position[i][j] + position[i][j + 1] + position[i][j + 2] +
				position[i][j + 3] + position[i][j + 4] + position[i][j + 5];
			if (number == 0 || (number>6 && number % 7 != 0))
				continue;
			if (Type == BLACK)//mycolor
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
	

}
void AnalysisLeft(int position[][19], int Type)
{
	
}
void AnalysisRight(int position[][19], int Type)
{
	
}
//估值仅需要计算以最后两个落子为中心的构成局面，计算为value+new-old
int evaluate(int Type){
	//srand(clock());
	//return rand();
	

	AnalysisHorizon(board, Type);
	AnalysisVertical(board, Type);
	AnalysisLeft(board, Type);
	AnalysisRight(board, Type);

	int score = 0;

	if (NumberOfMyRoad[6] > 0)
	{//说明实现六子连珠，给此走法价值为100000，显然游戏也结束
		return infinity;
	}
	if (NumberOfEnemyRoad[4]>0 || NumberOfEnemyRoad[5]>0)
	{//此走法走完后，说明对方再走两子或一子就实现六子连珠，显然，此走法决不可取，给此走法价值为-100000
		return -infinity;
	}
	//除去上面两种特殊情形，下面为一般情形
	for (int i = 1; i<6; i++)
		score += (NumberOfMyRoad[i] - NumberOfEnemyRoad[i]) * ScoreOfRoad[i];

	return score;
}
int typenimy(int type){

	if (TYPE == WHITE)
		return BLACK;
	else
		return WHITE;
}

void unmove(){
	board[moveList[MoveNum - 2].x][moveList[MoveNum - 2].y] = 0;
	board[moveList[MoveNum - 1].x][moveList[MoveNum - 1].y] = 0;
	moveList[MoveNum - 1].x = -1;
	moveList[MoveNum - 1].y = -1;
	MoveNum--;
	moveList[MoveNum - 1].x = -1;
	moveList[MoveNum - 1].y = -1;
	MoveNum--;
}
void GeneerateLegalMoves(){
}
bool MovesLeft(){
	return 1;
}
void MakeNextMove(){
	//添加到movelist中去
}
void TimeCheck(){
}
bool TimeOut(){

}
int AlphaBeta(int depth, long alpha, long beta)
{
	//to identity the type min or max use deep,deep is 3,so when deep%2=1 max
	//if you want to change deep ,then change the following code where is max and min
	int value = 0;
	//flag[depth-1] = 0;

	if (depth == 0)//奇数为0偶数为1
	{
		value = evaluate(TYPE);
		return value;
	}
	GeneerateLegalMoves();
	while (MovesLeft()){
		MakeNextMove();
		value = -AlphaBeta(depth-1,-beta,-alpha);
		unmove();
		if (value >= beta)
			return beta;
		if (value > alpha) {
			alpha = value;
		}
	}

	return value;
}


void search(){
	int value = 0;
	best[0].x = 0;
	best[0].y = 0;
	best[1].x = 0;
	best[1].y = 0;
	//value = alphaBeta(Depth, -infinity, infinity);
	for (int depth = 0;; depth++) {
		value = AlphaBeta(depth, -INFINITY, INFINITY);
		if (TimeOut()) {
			break;
		}
	}
	moveList[MoveNum].x = best[0].x;
	moveList[MoveNum].y = best[0].y;
	board[moveList[MoveNum].x][moveList[MoveNum].y] = TYPE;

	MoveNum++;
	moveList[MoveNum].x = best[1].x;
	moveList[MoveNum].y = best[1].y;
	board[moveList[MoveNum].x][moveList[MoveNum].y] = TYPE;
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
	else
	{
		moveList[MoveNum].x = *(message + 0) - 65;
		moveList[MoveNum].y = *(message + 1) - 65;
		board[moveList[MoveNum].x][moveList[MoveNum].y] = 1;
		MoveNum++;
	}
	//接下来的是根据估值进行落子
	//value函数需要进行进一步加工，包括生成所有可能部署并且进行估值选择最佳
	//此处仅进行简单测试不附加value函数具体实现
	//需要注意的是一次下两步棋两步棋使用递归进行调用

	//	possibleMove(board); 测试平台暂不使用
	//测试八个方向随意有空就下
	search();
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
	for (int k = 0; k<7; k++)
	{
		NumberOfMyRoad[k] = 0;
		NumberOfEnemyRoad[k] = 0;
	}
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
//����CPU

#include<iostream>
#include<string.h>
#include<random>
#include<time.h>
#include <fstream>
using namespace std;
#define infinity 10000000000
#define BLACK 1
#define WHITE 7
static int board[19][19];//�������̼�¼ 
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
point moveList[400];//�߲���¼static 
point possiblemove[Depth][800][2];
static int flag[Depth];
int MoveNum = 0;//����������Ŀstatic 
int NumberOfMyRoad[7];
int NumberOfEnemyRoad[7];
int ScoreOfRoad[7] = { 0, 17, 78, 141, 788, 1030, 100000 };
int timeflag=1;



void AnalysisHorizon(int position[][19], int Type)
{;
	int i, j, m, n;
	//��ȡmovelist��Ϣ��ʹ�õ�������ɨ��
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
	//���Ĺ�ֵ����
	//ɨ�����ֻ��չ����ɨ������
	//����ɨ�跨������ɨ�跨����ȱ��Աȣ�����ɨ�跨������С������Χ������11*11�ķ����У�����ɨ�跨���ɨ��һ��19*19�ķ���
	//���̽����ĸ��������ֶ����ڹ�ȥ��ֵĽ����²����ģ����Ҽ�����ͨ�����Ž�����������������������Ĳ�֮ͬ������������ÿ�ν��������׶Σ��ۺ����׶εĽ�������õ�����ֵΪ�����������ţ���������ɨ����׵õ�����֮��Ĺ�ֵ��ÿ�εõ���num��++֮ǰnun-1��Ҫ--��ԭ���������ԭ������Ͻ���һ��
	//�Ż�����ɨ�裺���ĸ�����ɨ�裬����Ϊ������׼
	//�����ı׶˺��ŵ㣺�����Ż�������Ĺ�ֵÿ��ֻ��Ҫɨ��4*11�Σ���������ɨ�跽��ֻ�����ڰ�·���������ڰ���ַ�����Ȼ��Ҫʹ��ԭ�е�ɨ�跽��
	//����ɨ�������ɨ��ȽϺͽ�ϣ�������
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
//��ֵ����Ҫ�����������������Ϊ���ĵĹ��ɾ��棬����Ϊvalue+new-old
int evaluate(int Type){
	//srand(clock());
	//return rand();
	

	AnalysisHorizon(board, Type);
	AnalysisVertical(board, Type);
	AnalysisLeft(board, Type);
	AnalysisRight(board, Type);

	int score = 0;

	if (NumberOfMyRoad[6] > 0)
	{//˵��ʵ���������飬�����߷���ֵΪ100000����Ȼ��ϷҲ����
		return infinity;
	}
	if (NumberOfEnemyRoad[4]>0 || NumberOfEnemyRoad[5]>0)
	{//���߷������˵���Է��������ӻ�һ�Ӿ�ʵ���������飬��Ȼ�����߷�������ȡ�������߷���ֵΪ-100000
		return -infinity;
	}
	//��ȥ���������������Σ�����Ϊһ������
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
	//��ӵ�movelist��ȥ
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

	if (depth == 0)//����Ϊ0ż��Ϊ1
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



char * move(char *message)//���±������̲��Ҳ����²�����
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
	//���������Ǹ��ݹ�ֵ��������
	//value������Ҫ���н�һ���ӹ��������������п��ܲ����ҽ��й�ֵѡ�����
	//�˴������м򵥲��Բ�����value��������ʵ��
	//��Ҫע�����һ����������������ʹ�õݹ���е���

	//	possibleMove(board); ����ƽ̨�ݲ�ʹ��
	//���԰˸����������пվ���
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
		if (strcmp(message, "move") == 0) //���ն����ŷ�
		{
			cin >> message;//gets_s(message);//scanf_s("%s", message);
			step = move(message);//��������ŷ��������ŷ���������Ҫʵ���������
			printf("move %s\n", step);//�����������ŷ�
		}
		else if (strcmp(message, "new") == 0)//���������
		{
			cin >> message;//gets_s(message);//scanf_s("%s", message);
			if (strcmp(message, "black") == 0)//ִ��
				TYPE = BLACK;
			else//ִ��
				TYPE = WHITE;
			initialGame(); //��ʼ�����ģ�������Ҫʵ���������
			if (strcmp(message, "black") == 0)
			{
				step = move();//������һ���ŷ���������Ҫʵ���������
				printf("move %s\n", step); //�����һ���ŷ�
			}
		}
		else if (strcmp(message, "name?") == 0)//ѯ��������
		{
			printf("name %s\n", engineName);//Ӧ��������
		}
		else if (strcmp(message, "end") == 0)
		{
			stopGame(); //ֹͣ���ģ�������Ҫʵ���������

		}
		else if (strcmp(message, "error") == 0)
		{
			stopGame(); //ֹͣ���ģ�������Ҫʵ���������

		}
	}
	return 0;
}
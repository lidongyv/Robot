#include<iostream>
#include<string.h>
#include<random>
#include<time.h>
#include <fstream>
//#include"Value.cpp"
using namespace std;

#define BLACK 1
#define WHITE 7
static int board[19][19];//�������̼�¼ 
static int TYPE;
#define NOSTONE 0
#define BYTE int
#define GRID_NUM 19
struct point{
	int x, y;
};
point moveList[400];//�߲���¼static 

int MoveNum = 0;//����������Ŀstatic 
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
	point static valueMove[25][25];//����������25*25���߷�
	int static valueList[25][25];
	valueList[1][1] = analysis(x, y);//�������ֵ������ӦvalueList
	point * temp=max(valueList);//����ֵ��������valueMove����moveList,temp���ڴ���������λ�ñ���ʹ��valueMove�е�����

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
	{//˵��ʵ���������飬�����߷���ֵΪ100000����Ȼ��ϷҲ����
	return 100000;
	}
	if(NumberOfEnemyRoad[4]>0 || NumberOfEnemyRoad[5]>0)
	{//���߷������˵���Է��������ӻ�һ�Ӿ�ʵ���������飬��Ȼ�����߷�������ȡ�������߷���ֵΪ-100000
	return -100000;
	}
	//��ȥ���������������Σ�����Ϊһ������
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
		
		//���º��������Ƽ�ʹ��analysis�������ж�����д
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
	//	if (temp >= 2)//������goto...
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
{//ע���������֮����Ҫȥ���µ���֪��ѡ������
//������Χ��������������ӣ����߽���ȫ�������������㷨��Ҫ����ʵ��
	static int flag = 0;
	flag++;
	while (flag <= 2)
	{
		for (int j = moveList[moveNum].x; j < moveList[moveNum].x + 5; j++)
			for (int k = moveList[moveNum].y; k < moveList[moveNum].y + 5; k++)
			{//ע���жϱ߽���ټ���
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
	
	//*(message + 2) = 'A' + rand() % 19 +1;
	//*(message + 3) = 'A' + rand() % 19 +1;
	//moveNum++;
	//���������Ǹ��ݹ�ֵ��������
	//value������Ҫ���н�һ���ӹ��������������п��ܲ����ҽ��й�ֵѡ�����
	//�˴������м򵥲��Բ�����value��������ʵ��
	//��Ҫע�����һ����������������ʹ�õݹ���е���

	//	possibleMove(board); ����ƽ̨�ݲ�ʹ��
	//���԰˸����������пվ���
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
		if (strcmp(message, "move") == 0) //���ն����ŷ�
		{
			cin >> message;//gets_s(message);//scanf_s("%s", message);
			 step =  move(message);//��������ŷ��������ŷ���������Ҫʵ���������
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
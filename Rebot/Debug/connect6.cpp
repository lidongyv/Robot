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
static point *moveList;//�߲���¼
static int board[19][19];//�������̼�¼
static int moveNum =0;//����������Ŀ

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
		if (temp >= 2)//������goto...
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
}
char * move(char *message)//���±������̲��Ҳ����²�����
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
	//���������Ǹ��ݹ�ֵ��������
	//value������Ҫ���н�һ���ӹ��������������п��ܲ����ҽ��й�ֵѡ�����
	//�˴������м򵥲��Բ�����value��������ʵ��
	//��Ҫע�����һ����������������ʹ�õݹ���е���

	//	possibleMove(board); ����ƽ̨�ݲ�ʹ��
	//���԰˸����������пվ���
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
				computerSide = BLACK;
			else//ִ��
				computerSide = WHITE;
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
	}
	return 0;
}
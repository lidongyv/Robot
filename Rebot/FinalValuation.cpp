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
#define FORCE 100
#define six 0
#define live_five 1
#define sleep_five 3
#define live_four 2
#define sleep_four 4
#define live_three 5
#define sleep_three 7
#define live_two 6
#define sleep_two 8
#define live_one 9
#define sleep_one 10
#define blank 11
//�������ŵĹ�ֵ�ͻ��ڱ���Ĺ�ֵ���������ͳ���ì�ܣ����汾�����������ͽ��з���
typedef const struct{
	int SIX = 10000;
	int LIVE_FIVE = 8000;
	int MID_FIVE = 5000;
	int LIVE_FOUR = 7000;
	int MID_FOUR = 5000;
	int SLEEP_FIVE = 3500;
	int SLEEP_FOUR = 3500;
	int LIVE_THREE = 700;
	int LIVE_TWO = 700;
	int SLEEP_THREE = 350;
	int SLEEP_TWO = 350;
	int LIVE_ONE = 35;
	int SLEEP_ONE = 10;
	int BLANK = 0;


}evaluationclass;
static int board[19][19];//�������̼�¼ 
int area[15];//���ͼ�ⴰ��
//int analysis[8];//���ͷ�������
static int TYPE;
int mytype = TYPE;
int enemy;
int rightnum;
int leftnum;
int countall;
int enemyright;
int enemycountall;
int enemyleft;
#define NOSTONE 0
#define BYTE int
#define GRID_NUM 19
#define Depth 1
struct _HASH{
	int road[12];
	int enemyroad[12];
	__int64 key;
	int value;
	__int64 next;
	//__int64 root;
	int deep;
	point bestmove[100];
};
_HASH status;
struct point{
	int x, y;
};
point best[2];

int bestmove;
int possiblecount[Depth];
point moveList[400];//�߲���¼static 
point possiblemove[Depth][800][2];
//static int flag[Depth];
int MoveNum = 0;//����������Ŀstatic 
evaluationclass evaluation;
int timeflag = 1;
int enemycountnum(){
	bool flag = true;
	int c = 1;
	enemyright = 1;
	enemycountall = 1;
	enemyleft = 1;
	int breaknum = 1;
	//ͬ��������һ���ϵ㣬�Ѳ�����ڶϵ����Բ������ٲ���
	while (flag)
	{
		if (c>0)
		{
			if ((area[7] != area[7 + c]) && (area[7 + c] != NOSTONE))
			{
				enemycountall++;
				c++;
			}
			else
			if ((area[7] != area[7 + c]) && (area[7] + c == NOSTONE) && (breaknum > 0) && (area[7 + c - 1] == area[7 + c + 1]))
			{
				c++;
				c++;
				breaknum--;
			}
			else
			{
				enemyright = c;
				c = -1;

			}
		}
		else
		{
			if ((area[7] != area[7 + c]) && (area[7 + c] != NOSTONE))
			{
				enemycountall++;
				c--;
			}
			else
			if ((area[7] != area[7 + c]) && (area[7] + c == NOSTONE) && (breaknum > 0) && (area[7 + c - 1] == area[7 + c + 1]))
			{
				c--;
				c--;
				breaknum--;
			}
			else
			{
				enemyleft = c+1;
				flag = false;
			}


		}
	}
	return countall;

}
int countnum(){
	bool flag = true;
	int c = 1;
	rightnum = 1;
	countall = 1;
	int breaknum = 1;
	while (flag)
	{
		if (c>0)
		{
			if (area[7] == area[7 + c])
			{
				countall++;
				c++;
			}
			else
			if ((area[7] + c == NOSTONE) && (breaknum > 0) && (area[7] == area[7 + c + 1]))
			{
				c++;
				c++;
				breaknum--;
			}
			else
			{
				rightnum = c;
				c = -1;
				if (countall > 3)
					breaknum = (breaknum > 0) ? breaknum = 1 : breaknum = 1;
			}
		}
		else
		{
			if (area[7] == area[7] + c)
			{
				countall++;
				c--;
			}
			else
			if ((area[7] + c == NOSTONE) && (breaknum > 0) && (area[7] == area[7 + c - 1]))
			{
				c--;
				c--;
				breaknum--;
			}
			else
			{
				leftnum = c+1;
				flag = false;
			}


		}
	}
	return countall;

}
void enemychecksix(){



}
void enemycheckfive(){}
void enemycheckfour()
{
	int right = rightnum;
	int left = enemyleft;
	int count = enemycountall;
	int analysis[10];
	//���հ��ж���ʽ
	if (right - left == count)
	{
		for (int i = 0; i < 9; i++)
			analysis[i] = area[7 + left - 2];
		switch (-left){
		case 0:
			if (analysis[7] == enemy || analysis[8] == enemy && analysis[1] == enemy)
				;
			else
			if (analysis[7] == enemy || analysis[8] == enemy || analysis[1] == enemy)
			if (mytype == TYPE)
			{
				status.enemyroad[7]--;


			}
			else
			{
				status.road[7]--;

			}
			else
			if (mytype == TYPE)
			{
				status.enemyroad[9]--;
				status.enemyroad[7]++;


			}
			else
			{
				status.road[9]--;
				status.road[7]++;

			}
			break;
		case 1:
			if (analysis[1] != enemy&&analysis[7] != enemy)
				if (mytype == TYPE)
				{
					status.enemyroad[9]--;
					status.enemyroad[4]++;
					status.enemyroad[2]++;

				}
				else
				{
					status.road[9]--;
					status.road[4]++;
					status.road[2]++;
				}
			else
			if (analysis[1] == enemy&&analysis[7] == enemy)
			if (mytype == TYPE)
			{
				status.enemyroad[9]--;			
			}
			else
			{
				status.road[9]--;
			}
			else
			if (analysis[1]==enemy)
				if (mytype == TYPE)
				{
					status.enemyroad[7]--;
					status.enemyroad[4]++;
				

				}
				else
				{
					status.road[7]--;
					status.road[4]++;
					
				}
			else
				if (mytype == TYPE)
				{
					status.enemyroad[7]--;
					status.enemyroad[2]++;

				}
				else
				{
					status.road[7]--;					
					status.road[2]++;
				}
		case 2:
			if (analysis[1] != enemy&&analysis[7] != enemy)
			if (mytype == TYPE)
			{
				status.enemyroad[9]--;
				status.enemyroad[3]++;
				status.enemyroad[3]++;

			}
			else
			{
				status.road[9]--;
				status.road[3]++;
				status.road[3]++;
			}
			else
			if (analysis[1] == enemy&&analysis[7] == enemy)
				;
			else
			if (analysis[1] == enemy)
			if (mytype == TYPE)
			{
				status.enemyroad[7]--;
				status.enemyroad[3]++;


			}
			else
			{
				status.road[7]--;
				status.road[3]++;

			}
			else
			if (mytype == TYPE)
			{
				status.enemyroad[7]--;
				status.enemyroad[3]++;

			}
			else
			{
				status.road[7]--;
				status.road[3]++;
			}
			break;
		case 3:;
			if (analysis[1] != enemy&&analysis[7] != enemy)
			if (mytype == TYPE)
			{
				status.enemyroad[9]--;
				status.enemyroad[4]++;
				status.enemyroad[2]++;

			}
			else
			{
				status.road[9]--;
				status.road[4]++;
				status.road[2]++;
			}
			else
			if (analysis[1] == enemy&&analysis[7] == enemy)
				;
			else
			if (analysis[1] == enemy)
			if (mytype == TYPE)
			{
				status.enemyroad[7]--;
				status.enemyroad[2]++;


			}
			else
			{
				status.road[7]--;
				status.road[2]++;

			}
			else
			if (mytype == TYPE)
			{
				status.enemyroad[7]--;
				status.enemyroad[4]++;

			}
			else
			{
				status.road[7]--;
				status.road[4]++;
			}
			break;
		case 4:;
			if (analysis[7] == enemy || analysis[8] == enemy)
			if (mytype == TYPE)
			{
				status.enemyroad[7]--;


			}
			else
			{
				status.road[7]--;

			}
			else
			if (mytype == TYPE)
			{
				status.enemyroad[9]--;
				status.enemyroad[7]++;


			}
			else
			{
				status.road[9]--;
				status.road[7]++;

			}
			break;
		}
	}

	else
	{
		for (int i = 0; i < 9; i++)
			analysis[i] = area[7 + left - 2];
		switch (-left)
		{
		case 0:;
			if (analysis[9] == enemy || analysis[8] == enemy && analysis[1] == enemy)
			if (mytype == TYPE)
			{
				status.enemyroad[9]--;
			}
			else
			{
				status.road[9]--;

			}
			else
			if (analysis[9] == enemy || analysis[8] == enemy || analysis[1] == enemy)
			if (mytype == TYPE)
			{
				status.enemyroad[9]--;


			}
			else
			{
				status.road[9]--;

			}
			else
			if (mytype == TYPE)
			{
				status.enemyroad[9]--;
				status.enemyroad[7]++;


			}
			else
			{
				status.road[9]--;
				status.road[7]++;

			}
			break;
		case 1:;
			if (analysis[1] != enemy&&analysis[8]!=enemy)
				if (mytype == TYPE)
				{
					status.enemyroad[9]--;
					status.enemyroad[4]++;
					status.enemyroad[2]++;

				}
				else
				{
					status.road[9]--;
					status.road[4]++;
					status.road[2]++;
				}
			else
			if (analysis[1] == enemy&&analysis[8] == enemy)
				;
			else
			if (analysis[1]==enemy)
				if (mytype == TYPE)
				{
					status.enemyroad[7]--;
					status.enemyroad[3]++;


				}
				else
				{
					status.road[7]--;
					status.road[3]++;

				}
			else
				if (mytype == TYPE)
				{
					status.enemyroad[7]--;
					status.enemyroad[3]++;

				}
				else
				{
					status.road[7]--;
					status.road[3]++;
				}
			break;
		case 2:;

			if (analysis[3] = NOSTONE)
				if (analysis[1] != enemy&&analysis[8] != enemy)
				if (mytype == TYPE)
				{
					status.enemyroad[9]--;
					status.enemyroad[4]++;
					status.enemyroad[2]++;

				}
				else
				{
					status.road[9]--;
					status.road[4]++;
					status.road[2]++;
				}
				else
				if (analysis[1] == enemy&&analysis[8] == enemy)
					;
				else
				if (analysis[1] == enemy)
				if (mytype == TYPE)
				{
					status.enemyroad[7]--;
					status.enemyroad[3]++;


				}
				else
				{
					status.road[7]--;
					status.road[3]++;

				}
				else
				if (mytype == TYPE)
				{
					status.enemyroad[7]--;
					status.enemyroad[3]++;

				}
				else
				{
					status.road[7]--;
					status.road[3]++;
				}
			else
				if (analysis[1] != enemy&&analysis[8] != enemy)
				if (mytype == TYPE)
				{
					status.enemyroad[9]--;
					status.enemyroad[3]++;
					status.enemyroad[3]++;

				}
				else
				{
					status.road[9]--;
					status.road[3]++;
					status.road[3]++;
				}
				else
				if (analysis[1] == enemy&&analysis[8] == enemy)
					;
				else	
					if (mytype == TYPE)
					{
						status.enemyroad[7]--;
						status.enemyroad[3]++;


					}
					else
					{
						status.road[7]--;
						status.road[3]++;

					}
				
			break;
		case 3:;
			if (analysis[6] = NOSTONE)
					if (analysis[1] != enemy&&analysis[8] != enemy)
					if (mytype == TYPE)
					{
						status.enemyroad[9]--;
						status.enemyroad[4]++;
						status.enemyroad[2]++;

					}
					else
					{
						status.road[9]--;
						status.road[4]++;
						status.road[2]++;
					}
				else
				if (analysis[1] == enemy&&analysis[8] == enemy)
					;
				else
				if (analysis[1] == enemy)
				if (mytype == TYPE)
				{
					status.enemyroad[7]--;
					status.enemyroad[3]++;


				}
				else
				{
					status.road[7]--;
					status.road[3]++;

				}
				else
				if (mytype == TYPE)
				{
					status.enemyroad[7]--;
					status.enemyroad[3]++;

				}
				else
				{
					status.road[7]--;
					status.road[3]++;
				}
		else
			if (analysis[1] != enemy&&analysis[8] != enemy)
			if (mytype == TYPE)
			{
				status.enemyroad[9]--;
				status.enemyroad[3]++;
				status.enemyroad[3]++;

			}
			else
			{
				status.road[9]--;
				status.road[3]++;
				status.road[3]++;
			}
			else
			if (analysis[1] == enemy&&analysis[8] == enemy)
				;
			else
			if (mytype == TYPE)
			{
				status.enemyroad[7]--;
				status.enemyroad[3]++;


			}
			else
			{
				status.road[7]--;
				status.road[3]++;

			}

			break;
		case 4:;
			if (analysis[1] != enemy&&analysis[8] != enemy)
			if (mytype == TYPE)
			{
				status.enemyroad[9]--;
				status.enemyroad[4]++;
				status.enemyroad[2]++;

			}
			else
			{
				status.road[9]--;
				status.road[4]++;
				status.road[2]++;
			}
			else
			if (analysis[1] == enemy&&analysis[8] == enemy)
			if (mytype == TYPE)
			{
				status.enemyroad[9]--;
			}
			else
			{
				status.road[9]--;
	
			}
			else
			if (analysis[8] == enemy)
			if (mytype == TYPE)
			{
				status.enemyroad[7]--;
				status.enemyroad[3]++;


			}
			else
			{
				status.road[7]--;
				status.road[3]++;

			}
			else
			if (mytype == TYPE)
			{
				status.enemyroad[7]--;
				status.enemyroad[3]++;

			}
			else
			{
				status.road[7]--;
				status.road[3]++;
			}
			break;
		case 5:;
			if (analysis[1] == enemy || analysis[2] == enemy && analysis[8] == enemy)
				if (mytype == TYPE)
				{
					status.enemyroad[9]--;
				}
				else
				{
					status.road[9]--;

				}
			else
			if (analysis[7] == enemy || analysis[8] == enemy || analysis[1] == enemy)
			if (mytype == TYPE)
			{
				status.enemyroad[9]--;


			}
			else
			{
				status.road[9]--;

			}
			else
			if (mytype == TYPE)
			{
				status.enemyroad[9]--;
				status.enemyroad[7]++;


			}
			else
			{
				status.road[9]--;
				status.road[7]++;

			}
			break;
		}
	}

}
void enemycheckthree(){

	int right = rightnum;
	int left = enemyleft;
	int count = enemycountall;
	int analysis[8];
	if (right - left == count)
	{
		if (left == 0)
		{
			for (int i = 0; i < 8; i++)
				analysis[i] = area[7 + i];
			if (analysis[4] == enemy || analysis[5] == enemy || analysis[6] == enemy || analysis[7]==enemy)
				if (mytype == TYPE)
				{
					status.enemyroad[4]--;
					

				}
				else
				{
					status.road[4]--;
					
				}
			else
			{
				if (mytype == TYPE)
				{
					status.enemyroad[6]--;
					status.enemyroad[4]++;


				}
				else
				{
					status.road[6]--;
					status.road[4]++;

				}
			}
		}
		else
		if (right == 1)
		{

			
				for (int i = 0; i < 8; i++)
				analysis[i] = area[i];
				if (analysis[0] == enemy || analysis[1] == enemy || analysis[2] == enemy || analysis[3] == enemy)
				if (mytype == TYPE)
				{
					status.enemyroad[4]--;


				}
				else
				{
					status.road[4]--;

				}
				else
				{
					if (mytype == TYPE)
					{
						status.enemyroad[6]--;
						status.enemyroad[4]++;


					}
					else
					{
						status.road[6]--;
						status.road[4]++;

					}
				}
			

		}
		else
		{

			//�����з���ֱ�ӽ�7+left��Ϊ���
			for (int i = 0; i < 8; i++)
				analysis[i] = area[7 + left - 2];
			if ((analysis[1] != enemy) && (analysis[6] != enemy) && (analysis[0] != enemy) && (analysis[7] != enemy))
			{
				if (mytype == TYPE)
				{
					status.enemyroad[6]--;
					status.enemyroad[1]++;
					status.enemyroad[3]++;


				}
				else
				{
					status.road[6]--;
					status.road[1]++;
					status.road[3]++;
				}
			}
			else
			if ((analysis[0 == enemy] || analysis[1] == enemy) && (analysis[6] == enemy || analysis[7] == enemy))

				;	
			else
			{
				if (mytype == TYPE)
				{
					status.enemyroad[4]--;
				//	status.enemyroad[1]++;
					status.enemyroad[3]++;


				}
				else
				{
					status.road[4]--;
				//	status.road[1]++;
					status.road[3]++;
				}
			}
		}

	}
	else
	{
		if (left == 0)
		{
		}
		else
		if (right == 1)
		{
		}
		else
		{
		}
	}
}
void enemychecktwo(){
	int right = rightnum;
	int left = enemyleft;
	int count = enemycountall;
	int analysis[8];
	if (right - left == count)
	{//���ӿ�
		if (left == 0)//��0
			{
			for (int i = 0; i < 8; i++)
				analysis[i] = area[7 + i];
			if ((analysis[3] == enemy) || (analysis[4] == enemy) || (analysis[5] == enemy) || (analysis[6] == enemy) || (analysis[7] == enemy))
			{
				if (mytype == TYPE)
				{
					status.enemyroad[3]--;

				}
				else
				{
					status.road[3]--;
				}
			}
			else
			{
				if (mytype == TYPE)
				{
					status.enemyroad[5]--;
					status.enemyroad[3]++;

				}
				else
				{
					status.road[5]--;
					status.road[3]++;
				}
			}
			}
			else
			if (right == 1)//��0
			{
				for (int i = 0; i < 8; i++)
					analysis[i] = area[i];
				if ((analysis[3] == enemy) || (analysis[4] == enemy) || (analysis[0] == enemy) || (analysis[1] == enemy) || (analysis[2] == enemy))
				{
					if (mytype == TYPE)
					{
						status.enemyroad[3]--;

					}
					else
					{
						status.road[3]--;
					}
				}
				else
				{
					if (mytype == TYPE)
					{
						status.enemyroad[5]--;
						status.enemyroad[3]++;

					}
					else
					{
						status.road[5]--;
						status.road[3]++;
					}
				}
			}
			else//��һ��

			{
				for (int i = 0; i < 8; i++)
					analysis[i] = area[7-2 + i];
				if ((((analysis[0] == enemy) || (analysis[1] == enemy)) && (analysis[5] != enemy) && (analysis[6] != enemy) && (analysis[7] != enemy)) || ((analysis[0] != enemy) && (analysis[1] != enemy) && ((analysis[5] == enemy) || (analysis[6] == enemy) || (analysis[7] == enemy))))
				{
					if (mytype == TYPE)
					{
						status.enemyroad[3]--;

					}
					else
					{
						status.road[3]--;
					}
				}
				else
				{	
					if ((analysis[0] != enemy) && (analysis[1] != enemy) && (analysis[5] != enemy) && (analysis[6] != enemy) && (analysis[7] != enemy))
					if (mytype == TYPE)
					{
						status.enemyroad[5]--;
						status.enemyroad[3]++;

					}
					else
					{
						status.road[5]--;
						status.road[3]++;
					}
				}
			}
	}
	else
	{//��һ����
		if (left == 0)//��0
		{
			for (int i = 0; i < 8; i++)
				analysis[i] = area[7 + i];
			if ((analysis[4] == enemy) || (analysis[5] == enemy) || (analysis[6] == enemy) || (analysis[7] == enemy))
			{
				if (mytype == TYPE)
				{
					status.enemyroad[3]--;

				}
				else
				{
					status.road[3]--;
				}
			}
			else
			{
				if (mytype == TYPE)
				{
					status.enemyroad[5]--;
					status.enemyroad[3]++;

				}
				else
				{
					status.road[5]--;
					status.road[3]++;
				}
			}
		}
		else
		if (right == 1)//��0
		{
			for (int i = 0; i < 8; i++)
				analysis[i] = area[ i];
			if ((analysis[3] == enemy) || (analysis[0] == enemy) || (analysis[1] == enemy) || (analysis[2] == enemy))
			{
				if (mytype == TYPE)
				{
					status.enemyroad[3]--;

				}
				else
				{
					status.road[3]--;
				}
			}
			else
			{
				if (mytype == TYPE)
				{
					status.enemyroad[5]--;
					status.enemyroad[3]++;

				}
				else
				{
					status.road[5]--;
					status.road[3]++;
				}
			}
		}
		else//��һ��
		{
			for (int i = 0; i < 8; i++)
				analysis[i] = area[7 +left- 2 + i];
			//��
			if ((((analysis[0] == enemy) || (analysis[1] == enemy)) && (analysis[6] != enemy) && (analysis[7] != enemy)) || ((analysis[0] != enemy) && (analysis[1] != enemy) && ( (analysis[6] == enemy) || (analysis[7] == enemy))))
			{
				if (mytype == TYPE)
				{
					status.enemyroad[2]--;
					
				}
				else
				{
					status.road[2]--;
				
				}
			}
			else
			{//��
				if ((analysis[0] != enemy) && (analysis[1] != enemy) && (analysis[6] != enemy) && (analysis[7] != enemy) )
				if (mytype == TYPE)
				{
					status.enemyroad[3]--;
					status.enemyroad[1]++;
					status.enemyroad[3]--;
					status.enemyroad[1]++;

				}
				else
				{
					status.road[3]--;
					status.road[1]++;
					status.road[3]--;
					status.road[1]++;
				}
			}
		}

	}
	

}
void enemycheckone(){
	int right = rightnum;
	int left = enemyleft;
	int count = enemycountall;
	int analysis[8];
	if (right - left == count)
	{
		if (right == 1)
		{
			for (int i = 0; i < 8; i++){
				analysis[i] = area[i];
			}
			if ((analysis[0] == mytype)  || (analysis[2] == mytype) || (analysis[3] == mytype) || (analysis[4] == mytype) || (analysis[5] == mytype) || (analysis[1] == mytype))
			{
				if (mytype == TYPE)
				{
					status.enemyroad[1]--;

				}
				else
				{
					status.road[1]--;
				}

			}
			else
			{
				if (mytype == TYPE)
				{
					status.enemyroad[2]--;

				}
				else
				{
					status.road[2]--;
				}

			}

		}
		if (left==0)
		{
			for (int i = 0; i < 8; i++){
				analysis[i] = area[ i];
			}
			if ((analysis[0] == mytype)  || (analysis[1] == mytype) || (analysis[2] == mytype) || (analysis[3] == mytype) || (analysis[4] == mytype) )
			{
				if (mytype == TYPE)
				{
					status.enemyroad[1]--;

				}
				else
				{
					status.road[1]--;
				}

			}
			else
			{
				if (mytype == TYPE)
				{
					status.enemyroad[1]++;
					status.enemyroad[2]--;

				}
				else
				{
					status.road[1]++;
					status.road[2]--;
				}

			}

		}
	}
		else
		{
			if (right == 1)
			{
				for (int i = 0; i < 8; i++){
					analysis[i] = area[ i];
				}
				if ((analysis[1] == mytype) || (analysis[2] == mytype) || (analysis[3] == mytype) || (analysis[4] == mytype) || (analysis[0] == mytype) )
				{
					if (mytype == TYPE)
					{
						status.enemyroad[1]--;

					}
					else
					{
						status.road[1]--;
					}

				}
				else
				{
					if (mytype == TYPE)
					{
						status.enemyroad[1]++;
						status.enemyroad[2]--;

					}
					else
					{
						status.road[1]++;
						status.road[2]--;
					}

				}

			}
			if (left == 0)
			{
				for (int i = 0; i < 8; i++){
					analysis[i] = area[7 + i];
				}
				if ((analysis[6] == mytype) || (analysis[7] == mytype) || (analysis[3] == mytype) || (analysis[4] == mytype) || (analysis[5] == mytype))
				{
					if (mytype == TYPE)
					{
						status.enemyroad[1]--;

					}
					else
					{
						status.road[1]--;
					}

				}
				else
				{
					if (mytype == TYPE)
					{
						status.enemyroad[1]++;
						status.enemyroad[2]--;

					}
					else
					{
						status.road[2]++;
						status.road[2]--;
					}

				}

			}

		}


	
}
void checksixbreak(){
	bool flag = true;
	int c = 1;
	int left;
	int right;
	int count;
	while (flag)
	{
		if (c>0)
		{
			if (area[7] == area[7 + c])
			{
				count++;
				c++;
			}

			else
			{
				right = c;
				c = -1;
			}
		}
		else
		{
			if (area[7] == area[7] + c)
			{
				count++;
				c--;
			}

			else
			{

				flag = false;
			}
		}
	}
	countall = count;
	rightnum = right;
	leftnum = left;
	switch (count){
	case 15:
	case 14:
	case 13:
	case 12:
	case 11:
	case 10:
	case 9:
	case 8:
	case 7:
	case 6:
		checksix(); break;
	case 5:checkfive(); break;
	case 4:checkfour(); break;
	case 3:checkthree(); break;
	case 2:checktwo(); break;
	case 1:checkone(); break;
	}


}
void checksix(){
	//for (int c = 0; c < 6; c++){
	//	if ((area[c] + area[1 + c] + area[2 + c] + area[3 + c] + area[4 + c] + area[5 + c]) == 6 * mytype)
	//		//���ʹ���6ʤ��
	//		;
	//}
	//evaluation.SIX;	
	

	int breaknum = 1;
	int left = leftnum;
	int right=rightnum;
	int count=countall;
	if (right - left == count)
	{
		if (mytype == TYPE)
		{
		status.road[11]++;
		}
		else
		{
			status.enemyroad[11]++;
		}
	}
	else
	{
		checksixbreak();

	}
	


}
void checkfive(){
	int analysis[8];
	//����
	int left = leftnum;
	int right = rightnum;
	int count = countall;
	//for (int j = 1; j <=2;j++)
	//for (int i = 0, a = left; i < 8; i++)
	//{
	//	analysis[j-1][i] = area[left - j + i];
	//}
	//if ((analysis[0][6] != enemy&&analysis[0][0] != enemy) || (analysis[1][7] != enemy&&analysis[1][1] != enemy))
	//	evaluation.LIVE_FIVE;//����
	//else if ((analysis[0][6] == enemy&&analysis[0][0] == enemy) || (analysis[1][7] == enemy&&analysis[1][1] == enemy))
	//	evaluation.BLANK;//����
	//else evaluation.SLEEP_FIVE;//����
	//�Ľ�
	if (right - left == count)
	{
		for (int i = 0; i < 9; i++)
			{
				analysis[i] = area[7 + left - 2 + i];
			}
			if ((analysis[1] == enemy) && (analysis[7] == enemy))
				evaluation.BLANK;//����
			
			else if ((analysis[1] != enemy) && (analysis[7] != enemy))
			{//evaluation.LIVE_FIVE;//����
				if (mytype == TYPE){
					status.road[10]++;
					status.road[9]--;
				}
				else{
					status.enemyroad[10]++;
					status.enemyroad[9]--;
				}
			}
			else //evaluation.SLEEP_FIVE;//����
			{//evaluation.LIVE_FIVE;//����
				if (mytype == TYPE){
					status.road[8]++;
					status.road[7]--;
				}
				else{
					status.enemyroad[8]++;
					status.enemyroad[7]--;
				}
			}
	}
	else
	{//�ɻ��Ļ������Ľ���������Ҫ�ڽ����жϣ��ж������Ƿ��ڼ������
			if (mytype == TYPE){
				status.road[8]++;
				status.road[7]--;
			}
			else{
				status.enemyroad[8]++;
				status.enemyroad[7]--;
			}
		
	}

}
void checkfour(){
	int analysis[8];

	int left = leftnum;
	int right = rightnum;
	int count = countall;
	if (right - left == count)
	{
		for (int i = 0; i < 8; i++){
				analysis[i] = area[7 + left - 2 + i];
			}
			//�ж�4
		if (((analysis[0] == enemy) && (analysis[6] == enemy)) || ((analysis[1] == enemy) && (analysis[7] == enemy)) || ((analysis[1] == enemy) && (analysis[6] == enemy)))
				evaluation.BLANK;//����
		else if ((((analysis[1] == enemy) || (analysis[0] == enemy)) && (analysis[6] != enemy) && (analysis[7] != enemy)) || (((analysis[6] == enemy) || (analysis[7] == enemy)) && (analysis[1] != enemy) && (analysis[0] != enemy)))
				//evaluation.SLEEP_FOUR;
		{
			if (mytype == TYPE)
			{
				status.road[7]++;
				status.road[4]--;
			}
			else
			{
				status.enemyroad[7]++;
				status.enemyroad[4]--;
			}

		}
			else 
				//evaluation.LIVE_FOUR;
			{
				if (mytype == TYPE)
				{
					status.road[9]++;
					status.road[6]--;
				}
				else
				{
					status.enemyroad[9]++;
					status.enemyroad[5]--;
				}

			}
	}
	else
	{
		for (int i = 0; i < 9; i++){
			analysis[i] = area[7 + left - 2 + i];
		}
		//�ж�4
		if (((analysis[1] == enemy) && (analysis[7] == enemy)))
			evaluation.BLANK;//����
		else if ((((analysis[1] == enemy) ) && (analysis[8] != enemy) && (analysis[7] != enemy)) || (((analysis[7] == enemy)) && (analysis[1] != enemy) && (analysis[0] != enemy)))
			//evaluation.SLEEP_FOUR;
		{
			if (mytype == TYPE)
			{
				status.road[7]++;
				status.road[4]--;
			}
			else
			{
				status.enemyroad[7]++;
				status.enemyroad[4]--;
			}

		}
		else
			//evaluation.LIVE_FOUR;
		if (analysis[1] != enemy&&analysis[7]!=enemy)
		{
			if (mytype == TYPE)
			{
				status.road[9]++;
				status.road[6]--;
			}	
			else
			{
				status.enemyroad[9]++;
				status.enemyroad[5]--;
			}

		}
	}
	

	//��������,û��Ҫ
}
void checkthree(){
	int analysis[9];

	int left = leftnum;
	int right = rightnum;
	int count = countall;
	if ( right-left == count)
	{
			for (int i = 0; i < 9; i++){
					analysis[i] = area[7 - left - 3 + i];
				}
				//����
				if (((analysis[1] == enemy || analysis[2] == enemy) && (analysis[7] == enemy || analysis[6] == enemy))
					|| ((analysis[0] == enemy) && (analysis[6] == enemy)) || ((analysis[2] == enemy) && (analysis[8] == enemy)))
					evaluation.BLANK;
				//�޸��߼�
				else if (((analysis[0] != enemy && analysis[1] != enemy&& analysis[2] != enemy) && (analysis[7] != enemy && analysis[6] != enemy))
					&& ((analysis[0] != enemy && analysis[1] != enemy) && (analysis[7] != enemy && analysis[6] != enemy&&analysis[8] != enemy)))
					//evaluation.LIVE_THREE;
				{
					if (mytype == TYPE)
					{
						status.road[6]++;
						status.road[5]--;
					}
					else
					{
						status.enemyroad[6]++;
						status.enemyroad[5]--;
					}

				}
				else
					//evaluation.SLEEP_THREE;
				{
					if (mytype == TYPE)
					{
						status.road[4]++;
						status.road[3]--;
					}
					else
					{
						status.enemyroad[4]++;
						status.enemyroad[3]--;
					}

				}

	}
	else{

		for (int i = 0; i < 8; i++){
			analysis[i] = area[7 + left - 2 + i];
		}
		//����
		if (((analysis[0] == enemy) && (analysis[6] == enemy)) || ((analysis[1] == enemy) && (analysis[7] == enemy)) || ((analysis[1] == enemy) && (analysis[6] == enemy)))
			evaluation.BLANK;
		//�޸��߼�
		else if (((analysis[0] != enemy && analysis[1] != enemy) && (analysis[7] != enemy && analysis[6] != enemy)))
			//evaluation.LIVE_THREE;
		{
			if (mytype == TYPE)
			{
				status.road[6]++;
				status.road[5]--;
			}
			else
			{
				status.enemyroad[6]++;
				status.enemyroad[5]--;
			}

		}
		else
			//evaluation.SLEEP_THREE;
		{
			if (mytype == TYPE)
			{
				status.road[4]++;
				status.road[3]--;
			}
			else
			{
				status.enemyroad[4]++;
				status.enemyroad[3]--;
			}

		}

	}
	



}
void checktwo(){
	int analysis[8];

	
	int right = rightnum;
	int count = countall;
	int left = leftnum;
	
	//����
	if (right - left==count)
	{
			for (int i = 0; i < 8; i++)
			{
			analysis[i] = area[7 + left - 3 + i];
			}

	
			if (((analysis[1] == enemy) || (analysis[2] == enemy)) && (analysis[5] == enemy) || (analysis[6] == enemy))
				evaluation.BLANK;
			else if (((analysis[1] != enemy) && (analysis[2] != enemy)) && (analysis[5] != enemy) && (analysis[6] != enemy) && (analysis[0] != enemy || analysis[7] != enemy))
				//evaluation.LIVE_TWO;��ٻ�������
			{
				if (mytype == TYPE)
				{
					status.road[5]++;
					status.road[2]--;
				}
				else
				{
					status.enemyroad[5]++;
					status.enemyroad[2]--;
				}

			}
			else //evaluation.SLEEP_TWO;
			{
				if (mytype == TYPE)
				{
					status.road[3]++;
					status.road[1]--;
				}
				else
				{
					status.enemyroad[3]++;
					status.enemyroad[1]--;
				}
			}
	}
	else
	{
		for (int i = 0; i < 9; i++)
		{
			analysis[i] = area[7 + left - 3 + i];
		}
		if (((analysis[1] == enemy) || (analysis[2] == enemy)) && (analysis[7] == enemy) || (analysis[6] == enemy))
			evaluation.BLANK;
		else if (((analysis[1] != enemy) && (analysis[2] != enemy)) && (analysis[7] != enemy) && (analysis[6] != enemy) && (analysis[0] != enemy || analysis[7] != enemy))
			//evaluation.LIVE_TWO;��ٻ�������
		{
			if (mytype == TYPE)
			{
				status.road[5]++;
				status.road[2]--;
			}
			else
			{
				status.enemyroad[5]++;
				status.enemyroad[2]--;
			}

		}
		else //evaluation.SLEEP_TWO;
		{
			if (mytype == TYPE)
			{
				status.road[3]++;
				status.road[1]--;
			}
			else
			{
				status.enemyroad[3]++;
				status.enemyroad[1]--;
			}
		}
	}
}
void checkone(){
	int analysis[9];

	int left = countall - rightnum;
	int right = rightnum;
	int count = countall;
	int left = leftnum;
	for (int i = 0; i < 9; i++){
		analysis[i] = area[3 + i];
	}
	//��һ
	if (((analysis[2] == enemy) || (analysis[3] == enemy) || (analysis[1] == enemy)) && ((analysis[5] == enemy) || (analysis[6] == enemy) || (analysis[7] == enemy)))
		evaluation.BLANK;
	else if ((((analysis[2] != enemy) && (analysis[3] != enemy) && (analysis[1] != enemy)) && ((analysis[5] != enemy) && (analysis[6] != enemy)) && (analysis[0] != enemy || analysis[7] != enemy))
		|| (((analysis[2] != enemy) && (analysis[3] != enemy)) && ((analysis[5] != enemy) && (analysis[6] != enemy) && (analysis[7] != enemy)) && (analysis[1] != enemy || analysis[8] != enemy)))
		//evaluation.LIVE_ONE;
	{
		if (mytype == TYPE)
			status.road[2]++;
		else
		{
			status.enemyroad[2]++;
		}

	}
	else// evaluation.SLEEP_ONE;
	{
		if (mytype == TYPE)
			status.road[1]++;
		else
		{
			status.enemyroad[1]++;
		}

	}
}
void AnalysisHorizon(int position[][19], int Type)
{

	int i, j, m, n;
	//��ȡmovelist��Ϣ��ʹ�õ�������ɨ��
	i = moveList[MoveNum - 1].x;
	j = moveList[MoveNum - 1].y;
	m = moveList[MoveNum - 2].x;
	n = moveList[MoveNum - 2].y;

	//���Ĺ�ֵ����
	//ɨ�����ֻ��չ����ɨ������
	//����ɨ�跨������ɨ�跨����ȱ��Աȣ�����ɨ�跨������С������Χ������11*11�ķ����У�����ɨ�跨���ɨ��һ��19*19�ķ���
	//���̽����ĸ��������ֶ����ڹ�ȥ��ֵĽ����²����ģ����Ҽ�����ͨ�����Ž�����������������������Ĳ�֮ͬ������������ÿ�ν��������׶Σ��ۺ����׶εĽ�������õ�����ֵΪ�����������ţ���������ɨ����׵õ�����֮��Ĺ�ֵ��ÿ�εõ���num��++֮ǰnun-1��Ҫ--��ԭ���������ԭ������Ͻ���һ��
	//�Ż�����ɨ�裺���ĸ�����ɨ�裬����Ϊ������׼
	//�����ı׶˺��ŵ㣺�����Ż�������Ĺ�ֵÿ��ֻ��Ҫɨ��2*4*11�Σ���������ɨ�跽��ֻ�����ڰ�·���������ڰ���ַ�����Ȼ��Ҫʹ��ԭ�е�ɨ�跽��
	//����ɨ�������ɨ��ȽϺͽ�ϣ�������
	//��Ҫע����Ƿ���֮���numberofroadֻ��Ӱ������Ӧ���ӽڵ㣬���ڵ���������û����������Ӧ�����û��������numberofroad�����Խ��з���
	//�������ķ���
	//ʵ�������ڵ�����numberofroad����ֱ��ʹ��
	//����ɨ�裬��unmoveһ���㣬Ȼ������ٴν���ɨ��

	//������ʹ�ü̳и���������ô���ռ任ȡ����ʱ���˼·
	position[m][n] = 0;

	//��һ��
	for (int a = -7, b = 0; a <= 7; a++, b++)
	{
		if ((j + a>0) && (j + a<18))
			area[b] = position[i][j + a];
		else
			area[b] = enemy;
	}
	switch (countnum()){

	case 15:
	case 14:
	case 13:
	case 12:
	case 11:
	case 10:
	case 9:
	case 8:
	case 7:
	case 6:
		checksix(); break;
	case 5:checkfive(); break;
	case 4:checkfour(); break;
	case 3:checkthree(); break;
	case 2:checktwo(); break;
	case 1:checkone(); break;
	}
	switch (enemycountnum()-1){
	case 14:
	case 13:
	case 12:
	case 11:
	case 10:
	case 9:
	case 8:
	case 7:
	case 6:
		enemychecksix(); break;
	case 5:enemycheckfive(); break;
	case 4:enemycheckfour(); break;
	case 3:enemycheckthree(); break;
	case 2:enemychecktwo(); break;
	case 1:enemycheckone(); break;


	}
	//�ڶ���
	position[m][n] = mytype;
	for (int a = -7, b = 0; a <= 7; a++, b++)
	{
		if ((m + a>0) && (m + a<18))
			area[b] = position[m][n + a];
		else
			area[b] = enemy;
	}
	switch (countnum()){
	case 17:
	case 16:
	case 15:
	case 14:
	case 13:
	case 12:
	case 11:
	case 10:
	case 9:
	case 8:
	case 7:
	case 6:
		checksix(); break;
	case 5:checkfive(); break;
	case 4:checkfour(); break;
	case 3:checkthree(); break;
	case 2:checktwo(); break;
	case 1:checkone(); break;
	}
	switch (enemycountnum() - 1){
	case 14:
	case 13:
	case 12:
	case 11:
	case 10:
	case 9:
	case 8:
	case 7:
	case 6:
		enemychecksix(); break;
	case 5:enemycheckfive(); break;
	case 4:enemycheckfour(); break;
	case 3:enemycheckthree(); break;
	case 2:enemychecktwo(); break;
	case 1:enemycheckone(); break;


	}


}
void AnalysisVertical(int position[][19], int Type)
{
	int i, j, m, n;
	//��ȡmovelist��Ϣ��ʹ�õ�������ɨ��
	i = moveList[MoveNum - 1].x;
	j = moveList[MoveNum - 1].y;
	m = moveList[MoveNum - 2].x;
	n = moveList[MoveNum - 2].y;
	position[m][n] = 0;

	//��һ��
	for (int a = -7, b = 0; a <= 7; a++, b++)
	{
		if ((i + a>0) && (i + a<18))
			area[b] = position[i + a][j];
		else
			area[b] = enemy;
	}
	switch (countnum()){
	case 17:
	case 16:
	case 15:
	case 14:
	case 13:
	case 12:
	case 11:
	case 10:
	case 9:
	case 8:
	case 7:
	case 6:
		checksix(); break;
	case 5:checkfive(); break;
	case 4:checkfour(); break;
	case 3:checkthree(); break;
	case 2:checktwo(); break;
	case 1:checkone(); break;
	}
	switch (enemycountnum() - 1){
	case 14:
	case 13:
	case 12:
	case 11:
	case 10:
	case 9:
	case 8:
	case 7:
	case 6:
		enemychecksix(); break;
	case 5:enemycheckfive(); break;
	case 4:enemycheckfour(); break;
	case 3:enemycheckthree(); break;
	case 2:enemychecktwo(); break;
	case 1:enemycheckone(); break;


	}
	//�ڶ���
	position[m][n] = mytype;
	for (int a = -7, b = 0; a <= 7; a++, b++)
	{
		if ((m + a>0) && (m + a<18))
			area[b] = position[m][n + a];
		else
			area[b] = enemy;
	}
	switch (countnum()){
	case 17:
	case 16:
	case 15:
	case 14:
	case 13:
	case 12:
	case 11:
	case 10:
	case 9:
	case 8:
	case 7:
	case 6:
		checksix(); break;
	case 5:checkfive(); break;
	case 4:checkfour(); break;
	case 3:checkthree(); break;
	case 2:checktwo(); break;
	case 1:checkone(); break;
	}
	switch (enemycountnum() - 1){
	case 14:
	case 13:
	case 12:
	case 11:
	case 10:
	case 9:
	case 8:
	case 7:
	case 6:
		enemychecksix(); break;
	case 5:enemycheckfive(); break;
	case 4:enemycheckfour(); break;
	case 3:enemycheckthree(); break;
	case 2:enemychecktwo(); break;
	case 1:enemycheckone(); break;


	}


}
void AnalysisLeft(int position[][19], int Type)
{
	int i, j, m, n;
	//��ȡmovelist��Ϣ��ʹ�õ�������ɨ��
	i = moveList[MoveNum - 1].x;
	j = moveList[MoveNum - 1].y;
	m = moveList[MoveNum - 2].x;
	n = moveList[MoveNum - 2].y;
	position[m][n] = 0;

	//��һ��
	for (int a = -7, b = 0; a <= 7; a++, b++)
	{
		if ((i + a>0) && (i + a<18) && (j + a>0) && (j + a<18))
			area[b] = position[i + a][j + a];
		else
			area[b] = enemy;
	}
	switch (countnum()){
	case 17:
	case 16:
	case 15:
	case 14:
	case 13:
	case 12:
	case 11:
	case 10:
	case 9:
	case 8:
	case 7:
	case 6:
		checksix(); break;
	case 5:checkfive(); break;
	case 4:checkfour(); break;
	case 3:checkthree(); break;
	case 2:checktwo(); break;
	case 1:checkone(); break;
	}
	switch (enemycountnum() - 1){
	case 14:
	case 13:
	case 12:
	case 11:
	case 10:
	case 9:
	case 8:
	case 7:
	case 6:
		enemychecksix(); break;
	case 5:enemycheckfive(); break;
	case 4:enemycheckfour(); break;
	case 3:enemycheckthree(); break;
	case 2:enemychecktwo(); break;
	case 1:enemycheckone(); break;


	}
	//�ڶ���
	position[m][n] = mytype;
	for (int a = -7, b = 0; a <= 7; a++, b++)
	{
		if ((m + a>0) && (m + a<18) && (n + a>0) && (n + a<18))
			area[b] = position[m + a][n + a];
		else
			area[b] = enemy;
	}
	switch (countnum()){
	case 17:
	case 16:
	case 15:
	case 14:
	case 13:
	case 12:
	case 11:
	case 10:
	case 9:
	case 8:
	case 7:
	case 6:
		checksix(); break;
	case 5:checkfive(); break;
	case 4:checkfour(); break;
	case 3:checkthree(); break;
	case 2:checktwo(); break;
	case 1:checkone(); break;
	}
	switch (enemycountnum() - 1){
	case 14:
	case 13:
	case 12:
	case 11:
	case 10:
	case 9:
	case 8:
	case 7:
	case 6:
		enemychecksix(); break;
	case 5:enemycheckfive(); break;
	case 4:enemycheckfour(); break;
	case 3:enemycheckthree(); break;
	case 2:enemychecktwo(); break;
	case 1:enemycheckone(); break;


	}
}
void AnalysisRight(int position[][19], int Type)
{
	int i, j, m, n;
	//��ȡmovelist��Ϣ��ʹ�õ�������ɨ��
	i = moveList[MoveNum - 1].x;
	j = moveList[MoveNum - 1].y;
	m = moveList[MoveNum - 2].x;
	n = moveList[MoveNum - 2].y;
	position[m][n] = 0;

	//��һ��
	for (int a = -7, b = 0; a <= 7; a++, b++)
	{
		if ((i - a>0) && (i - a<18) && (j + a>0) && (j + a<18))
			area[b] = position[i - a][j + a];
		else
			area[b] = enemy;
	}
	switch (countnum()){
	case 17:
	case 16:
	case 15:
	case 14:
	case 13:
	case 12:
	case 11:
	case 10:
	case 9:
	case 8:
	case 7:
	case 6:
		checksix(); break;
	case 5:checkfive(); break;
	case 4:checkfour(); break;
	case 3:checkthree(); break;
	case 2:checktwo(); break;
	case 1:checkone(); break;
	}
	switch (enemycountnum() - 1){
	case 14:
	case 13:
	case 12:
	case 11:
	case 10:
	case 9:
	case 8:
	case 7:
	case 6:
		enemychecksix(); break;
	case 5:enemycheckfive(); break;
	case 4:enemycheckfour(); break;
	case 3:enemycheckthree(); break;
	case 2:enemychecktwo(); break;
	case 1:enemycheckone(); break;


	}
	//�ڶ���
	position[m][n] = mytype;
	for (int a = -7, b = 0; a <= 7; a++, b++)
	{
		if ((m - a>0) && (m - a<18) && (n + a>0) && (n + a<18))
			area[b] = position[m - a][n + a];
		else
			area[b] = enemy;
	}
	switch (countnum()){
	case 17:
	case 16:
	case 15:
	case 14:
	case 13:
	case 12:
	case 11:
	case 10:
	case 9:
	case 8:
	case 7:
	case 6:
		checksix(); break;
	case 5:checkfive(); break;
	case 4:checkfour(); break;
	case 3:checkthree(); break;
	case 2:checktwo(); break;
	case 1:checkone(); break;
	}
	switch (enemycountnum() - 1){
	case 14:
	case 13:
	case 12:
	case 11:
	case 10:
	case 9:
	case 8:
	case 7:
	case 6:
		enemychecksix(); break;
	case 5:enemycheckfive(); break;
	case 4:enemycheckfour(); break;
	case 3:enemycheckthree(); break;
	case 2:enemychecktwo(); break;
	case 1:enemycheckone(); break;


	}
}
//��ֵ����Ҫ�����������������Ϊ���ĵĹ��ɾ��棬����Ϊvalue+new-old
int evaluate(int Type){



	AnalysisHorizon(board, Type);
	AnalysisVertical(board, Type);
	AnalysisLeft(board, Type);
	AnalysisRight(board, Type);
	int score = 0;
	score = (status.road[0] - status.enemyroad[0])*evaluation.BLANK +
		(status.road[1] - status.enemyroad[1])*evaluation.SLEEP_ONE +
		(status.road[2] - status.enemyroad[2])*evaluation.LIVE_ONE +
		(status.road[3] - status.enemyroad[3])*evaluation.SLEEP_TWO +
		(status.road[4] - status.enemyroad[4])*evaluation.SLEEP_THREE +
		(status.road[5] - status.enemyroad[5])*evaluation.LIVE_TWO +
		(status.road[6] - status.enemyroad[6])*evaluation.LIVE_THREE +
		(status.road[7] - status.enemyroad[7])*evaluation.SLEEP_FOUR +
		(status.road[8] - status.enemyroad[8])*evaluation.SLEEP_FIVE +
		(status.road[9] - status.enemyroad[9])*evaluation.LIVE_FOUR +
		(status.road[10] - status.enemyroad[10])*evaluation.LIVE_FIVE +
		(status.road[11] - status.enemyroad[11])*evaluation.SIX;
	//
	if (mytype == Type)
	{
		return score;
		/*if (score > 0)
		return score;
		else return -score;*/
	}
	else
	{
		return -score;
		/*	if (score>0)
		return -score;
		else return score;*/
	}
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
bool MovesLeft(){//��������Ľ�Stss���ŵ�
	return 1;
}
void MakeNextMove(){
	//��ӵ�movelist��ȥ
	//ʵ��������
	mytype = typenimy(mytype);
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

	if (depth == 0)
	{
		value = evaluate(TYPE);
		return value;
	}
	GeneerateLegalMoves();

	while (MovesLeft()){

		MakeNextMove();
		value = -AlphaBeta(depth - 1, -beta, -alpha);
		unmove();
		//���������typeΪ����enemyΪ��
		//if (((mytype == TYPE) && value > 0) || ((mytype != TYPE) && value < 0))
		{
			if (value >= beta)
				return value;
			if (value > alpha) {
				alpha = value;
			}
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
		//���ϴεõ������ŵ㿪ʼ���������ڲ�����֦
		mytype = TYPE;
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
	for (int k = 0; k<12; k++)
	{
		status.enemyroad[k] = 0;
		status.road[k] = 0;
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
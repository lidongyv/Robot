#include"define.cpp"

int value( int Type)
{
	for (int k = 0; k<7; k++)
	{
		NumberOfMyRoad[k] = 0;
		NumberOfEnemyRoad[k] = 0;
	}

	AnalysisHorizon(board ,Type);
	AnalysisVertical(board, Type);
	AnalysisLeft(board, Type);
	AnalysisRight(board, Type);

	int score = 0;

	if (NumberOfMyRoad[6] > 0)
	{//˵��ʵ���������飬�����߷���ֵΪ100000����Ȼ��ϷҲ����
		return 100000;
	}
	if (NumberOfEnemyRoad[4]>0 || NumberOfEnemyRoad[5]>0)
	{//���߷������˵���Է��������ӻ�һ�Ӿ�ʵ���������飬��Ȼ�����߷�������ȡ�������߷���ֵΪ-100000
		return -100000;
	}
	//��ȥ���������������Σ�����Ϊһ������
	for (int i = 1; i<6; i++)
		score += (NumberOfMyRoad[i] - NumberOfEnemyRoad[i]) * ScoreOfRoad[i];

	return score;
}
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
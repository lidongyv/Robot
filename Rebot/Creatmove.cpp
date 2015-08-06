#include"define.cpp"
#include<Windows.h>
int m_nMoveCount;
int IsValidPosition(int position[19][19], int i, int j)
{
	if (j - 2 >= 0 && position[i][j - 2] != NOSTONE)  return 1;//左边
	if (j - 1 >= 0 && position[i][j - 1] != NOSTONE)  return 1;
	if (j + 2<19 && position[i][j + 2] != NOSTONE)  return 1;//右边
	if (j + 1<19 && position[i][j + 1] != NOSTONE)  return 1;
	if (i - 2 >= 0 && position[i - 2][j] != NOSTONE)  return 1;//上面
	if (i - 1 >= 0 && position[i - 1][j] != NOSTONE)  return 1;
	if (i + 2<19 && position[i + 2][j] != NOSTONE)  return 1;//下面
	if (i + 1<19 && position[i + 1][j] != NOSTONE)  return 1;


	if (i - 2 >= 0 && j - 2 >= 0 && position[i - 2][j - 2] != NOSTONE)  return 1;//左上边
	if (i - 1 >= 0 && j - 1 >= 0 && position[i - 1][j - 1] != NOSTONE)  return 1;
	if (i + 2<19 && j + 2<19 && position[i + 2][j + 2] != NOSTONE)  return 1;//右下边
	if (i + 1<19 && j + 1<19 && position[i + 1][j + 1] != NOSTONE)  return 1;
	if (i - 2 >= 0 && j + 2<19 && position[i - 2][j + 2] != NOSTONE)  return 1;//右上面
	if (i - 1 >= 0 && j + 1<19 && position[i - 1][j + 1] != NOSTONE)  return 1;
	if (i + 2<19 && j - 2 >= 0 && position[i + 2][j - 2] != NOSTONE)  return 1;//左下面
	if (i + 1<19 && j - 1 >= 0 && position[i + 1][j - 1] != NOSTONE)  return 1;


	/*if(i-2>=0&&j-1>=0&&position[i-2][j-1]!=NOSTONE)  return 1;
	if(i-2>=0&&j+1<19&&position[i-2][j+1]!=NOSTONE)  return 1;
	if(i-1>=0&&j-2>=0&&position[i-1][j-2]!=NOSTONE)  return 1;
	if(i-1>=0&&j+2<19&&position[i-1][j+2]!=NOSTONE)  return 1;
	if(i+1<19&&j-2>=0&&position[i+1][j-2]!=NOSTONE)  return 1;
	if(i+1<19&&j+2<19&&position[i+1][j+2]!=NOSTONE)  return 1;
	if(i+2<19&&j-1>=0&&position[i+2][j-1]!=NOSTONE)  return 1;
	if(i+2<19&&j+1<19&&position[i+2][j+1]!=NOSTONE)  return 1;*/

	return 0;
}
int CreatePossibleMove(BYTE position[GRID_NUM][GRID_NUM], int nPly, int Type)
{
	//此函数前19行代码特别讲解
	int i_min = 19, i_max = 0, j_min = 19, j_max = 0;
	for (int ii = 0; ii<19; ii++)
	{
		for (int jj = 0; jj<19; jj++)
		{
			if (position[ii][jj] != NOSTONE)
			{
				if (ii<i_min) i_min = ii;
				if (ii>i_max) i_max = ii;
				if (jj<j_min) j_min = jj;
				if (jj>j_max) j_max = jj;
			}
		}
	}
	i_min -= 2, i_max += 3, j_min -= 2, j_max += 3;
	if (i_min <= 0)  i_min = 0;
	if (i_max >= 19) i_max = 19;
	if (j_min <= 0)  j_min = 0;
	if (j_max >= 19) j_max = 19;


	//前面代码特别讲解
	//以下是生成所有走法及他们的价值
	int		i1, j1, i2, j2;
	m_nMoveCount = 0;
	for (i1 = i_min; i1 < i_max; i1++)
	for (j1 = j_min; j1 < j_max; j1++)
	{
		if (position[i1][j1] == (BYTE)NOSTONE)//第一步棋
		{
			int i = (j1 + 1) / j_max, j = (j1 + 1) % j_max;
			i2 = i1 + i;
			j2 = j;
			for (; i2 < i_max; i2++, j2 = j_min)
			for (; j2 < j_max; j2++)
			{

				if (position[i2][j2] == (BYTE)NOSTONE)//第二步棋
				{
					BOOL a1 = IsValidPosition(position, i1, j1);
					position[i1][j1] = Type;
					BOOL a2 = IsValidPosition(position, i2, j2);
					position[i1][j1] = NOSTONE;
					BOOL b1 = IsValidPosition(position, i2, j2);
					position[i2][j2] = Type;
					BOOL b2 = IsValidPosition(position, i1, j1);
					position[i2][j2] = NOSTONE;

					if (a1 + a2 != 2 && b1 + b2 != 2)
						continue;
					m_MoveList[nPly][m_nMoveCount].StonePos1.x = j1;
					m_MoveList[nPly][m_nMoveCount].StonePos1.y = i1;
					m_MoveList[nPly][m_nMoveCount].StonePos2.x = j2;
					m_MoveList[nPly][m_nMoveCount].StonePos2.y = i2;

					position[i1][j1] = Type;//在棋盘上放第一步棋子
					position[i2][j2] = Type;//在棋盘上放第二步棋子

					//下面一条语句是获得此走法的价值
					m_MoveList[nPly][m_nMoveCount].Score = m_pEvel->Eveluate(position, Type);

					if (m_MoveList[nPly][m_nMoveCount].Score == 100000)
					{//若此走法价值为100000，则说明此走法实现六子连珠，即游戏结束
						//很显然，此走法是最优走法，将其付给走法链的第一个元素，然后return
						m_MoveList[nPly][0].StonePos1.x = j1;
						m_MoveList[nPly][0].StonePos1.y = i1;
						m_MoveList[nPly][0].StonePos2.x = j2;
						m_MoveList[nPly][0].StonePos2.y = i2;
						m_MoveList[nPly][0].Score = 100000;
						position[i1][j1] = NOSTONE;//撤销刚下在棋盘上的第一步棋子
						position[i2][j2] = NOSTONE;//撤销刚下在棋盘上的第二步棋子
						return 1;
					}
					position[i1][j1] = NOSTONE;//撤销刚下在棋盘上的第一步棋子
					position[i2][j2] = NOSTONE;//撤销刚下在棋盘上的第二步棋子
					m_nMoveCount++;
				}
			}
		}
	}
	//下面三条语句对所有走法的价值经过从大到小的排序，显然m_MoveList[2][0]是最优走法，不用理解，知道干啥就行

	HistoryHeuristic->MergeSort(m_MoveList[nPly], m_nMoveCount, 0);
	return m_nMoveCount;
}

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
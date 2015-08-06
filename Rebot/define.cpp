
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
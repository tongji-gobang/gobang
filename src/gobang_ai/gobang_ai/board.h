#pragma once

#define BROAD_SIZE 15  //棋盘大小
#define COM 1    //computer 
#define HUM 2	//human 
#define EMPTY 0 //empty 


//各种棋型代表的分数
#define ONE 10
#define	TWO  100
#define	THREE  1000
#define	FOUR  100000
#define	FIVE 10000000
#define	BLOCKED_ONE  1
#define	BLOCKED_TWO  10
#define BLOCKED_THREE  100
#define	BLOCKED_FOUR  10000





#include<iostream>
#include <vector>
#include<algorithm>
using namespace std;


struct point
{
	int pos[2];		//该点所在位置
	int scoreCom;	//若这一点放电脑所执棋得分
	int scoreHum;	//若这一点放人类所执棋得分
	int score;		//scoreCom和scoreHum中更大的那个
	int role;		//此位置若有棋 role则是该位置棋的颜色

};

class board {
public:
	int board[BROAD_SIZE][BROAD_SIZE]; 	   //棋盘二维数组
	int count;								//好像是记录回合数的 
	vector<point> currentSteps;				//记录下的棋的坐标 栈的记录方式
	vector<point> allSteps;					//好像和上面的一样的
	int scoreCom[BROAD_SIZE][BROAD_SIZE];	//电脑棋盘各个棋子代表分数
	int scoreHum[BROAD_SIZE][BROAD_SIZE];	//人类玩家棋盘各个棋子分数
	int scoreCache[3][4][BROAD_SIZE][BROAD_SIZE];	//计分时所用到的缓存数组，四个维度分别是角色（3种）/方向（4种）/行/列
													//至于这样定义的理由 以及具体用途暂时未知
	vector<point> stepsTail;				// 用来存储悔棋步骤，以便放弃悔棋，重新加载棋盘（大概是这样的功能）


	//生成着棋点
	vector<point> gen(int role, bool onlyThrees = false, bool starSpread = false);

	//下子，无返回
	void put(point p, int role);

	//移除棋子，无返回
	void remove(point p);

	void backward();
	void forward();

	// Minimax Search
	int Negmax(vector<struct point>& candidates, int role, int depth, int alpha, int beta );
	struct point Deeping( vector<struct point>& candidates, int role, int depth );
	struct point DepthSearchAll( int role, int depth );

	// io
	int CommandPrint() const;
};
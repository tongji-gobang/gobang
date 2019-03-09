#pragma once

#define BROAD_SIZE 15  //棋盘大小
#define COM 1    //computer 
#define HUM 2	//human 
#define EMPTY 0 //empty 



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
using namespace std;


struct point
{
	int pos[2];
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

	vector<point> gen(int role, bool onlyThrees = false, bool starSpread = false);

	//下子，无返回
	void put(point p, int role);

	//移除棋子，无返回
	void remove(point p);

};
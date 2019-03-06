#pragma once

#define BROAD_SIZE 15  //棋盘大小
#define COM 1    //computer 
#define HUM 2	//human 
#define EMPTY 0 //empty 
#define point int[2]  //定义新类型point 代表棋子坐标 本来应该用typedef的

#include<iostream>
#include <vector>
using namespace std;

class board {
public:
	int board[BROAD_SIZE][BROAD_SIZE]; 	   //棋盘二维数组
	int count;								//好像是记录回合数的 
	vector<point> currentSteps;				//记录下的棋的坐标 栈的记录方式
	vector<point> allSteps;					//好像和上面的一样的
	int scoreCom[BROAD_SIZE][BROAD_SIZE];	//电脑棋盘各个棋子代表分数
	int scoreHum[BROAD_SIZE][BROAD_SIZE];	//人类玩家棋盘各个棋子分数


	vector<point> gen(int role, bool onlyThrees = false, bool starSpread = false);

};
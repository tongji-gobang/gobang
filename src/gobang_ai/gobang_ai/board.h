#pragma once

#define BROAD_SIZE 15
#define COM 1    //computer
#define HUM 2	//human
#define EMPTY 0 //empty
#define point int[2]

#include<iostream>
#include <vector>
using namespace std;

class board {
public:
	int board[BROAD_SIZE][BROAD_SIZE]; 	
	int count;
	vector<point> currentSteps;
	vector<point> allSteps;



	vector<point> gen(int role, bool onlyThrees = false, bool starSpread = false);

};
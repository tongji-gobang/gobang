#pragma once

//#include "board.h" //需要使用board size宏定义，但board也需要zobrist.h
#include<stdlib.h> //随机数
#include<time.h> //种子

struct Zobrist {
public:
	unsigned int com[15 *15];	
	unsigned int hum[15 *15];
	unsigned int code;

	Zobrist(); //构造函数
	
	unsigned int go(int x, int y, int role); 
};

#pragma once

//#include "board.h" //��Ҫʹ��board size�궨�壬��boardҲ��Ҫzobrist.h
#include<cstdlib>//�����
#include<ctime>//����
#include<cstdio>

using namespace std;
struct Zobrist {
public:
	unsigned int com[15 *15];	
	unsigned int hum[15 *15];
	unsigned int code;

	Zobrist(); //���캯��
	
	unsigned int go(int x, int y, int role); 
};

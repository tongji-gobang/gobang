
#include "zobrist.h"

Zobrist::Zobrist()
{
	int i;//32位 
	srand(time(NULL));
	
	for (i = 0; i < 15 * 15; i++) {
		com[i] <<= 32;
		com[i] |= rand();
		
		hum[i] <<= 32;
		hum[i] |= rand();
	}

	code = rand();
	code <<= 32;
	code |= rand();
}

unsigned int Zobrist::go(int x, int y, int role)
{
	int index = 15 * x + y;
	this->code ^= (role == COM ? com[index] : hum[index]); //需要board宏定义
	return this->code;
}


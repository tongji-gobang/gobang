#pragma once

#define BROAD_SIZE 15  //���̴�С
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
	int board[BROAD_SIZE][BROAD_SIZE]; 	   //���̶�ά����
	int count;								//�����Ǽ�¼�غ����� 
	vector<point> currentSteps;				//��¼�µ�������� ջ�ļ�¼��ʽ
	vector<point> allSteps;					//����������һ����
	int scoreCom[BROAD_SIZE][BROAD_SIZE];	//�������̸������Ӵ������
	int scoreHum[BROAD_SIZE][BROAD_SIZE];	//����������̸������ӷ���
	int scoreCache[3][4][BROAD_SIZE][BROAD_SIZE];	//�Ʒ�ʱ���õ��Ļ������飬�ĸ�ά�ȷֱ��ǽ�ɫ��3�֣�/����4�֣�/��/��
													//����������������� �Լ�������;��ʱδ֪

	vector<point> gen(int role, bool onlyThrees = false, bool starSpread = false);

	//���ӣ��޷���
	void put(point p, int role);

	//�Ƴ����ӣ��޷���
	void remove(point p);

};
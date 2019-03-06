#pragma once

#define BROAD_SIZE 15  //���̴�С
#define COM 1    //computer 
#define HUM 2	//human 
#define EMPTY 0 //empty 
#define point int[2]  //����������point ������������ ����Ӧ����typedef��

#include<iostream>
#include <vector>
using namespace std;

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

};
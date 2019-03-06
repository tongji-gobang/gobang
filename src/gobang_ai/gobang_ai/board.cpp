#include"board.h"


bool hasNeighber(int x, int y, int distance, int count,int board[BROAD_SIZE][BROAD_SIZE]) {
	int startX = x - distance;
	int endX = x + distance;
	int startY = y - distance;
	int endY = y + distance;

	for (int i = startX; i <= endX; i++) {
		if (i < 0 || i >= BROAD_SIZE)
			continue;
		for (int j = startY; j <= endY; j++) {
			if (j < 0 || j >= BROAD_SIZE) continue;
			if (i == x&&j == y) continue;
			if (board[i][j] == EMPTY) {
				count--;
				if (count <= 0)
					return true;
			}
		}
	}
	return false;
}


vector<int[2]> board::gen(int role, bool onlyThrees = false, bool starSpread = false) {
	if (this->count <= 0) {
		vector<int[2]> a = { {7,7} };
		return a;
	}
	vector<int[2]> fives ;
	vector<int[2]> comfours ;
	vector<int[2]> humfours ;
	vector<int[2]> comblockedfours ;
	vector<int[2]> humblockedfours ;
	vector<int[2]> comtwothrees ;
	vector<int[2]> humtwothrees ;
	vector<int[2]> comthrees ;
	vector<int[2]> humthrees ;
	vector<int[2]> comtwos ;
	vector<int[2]> humtwos ;
	vector<int[2]> neighbors ;


	//��������Ϣ���Ƶ�tempBroad
	int tempBroad[BROAD_SIZE][BROAD_SIZE];
	for (int i = 0; i < BROAD_SIZE; i++)
		for (int j = 0; j < BROAD_SIZE; j++)
			tempBroad[i][j] = this->board[i][j];

	//����ɫ��ת ����������Ϊ������ı��ɫΪ��� ��֮��Ȼ
	int reverseRole;
	if (role == HUM)
		role = COM;
	else
		role = HUM;




	//��������Ѱ�������
	for (int i = 0; i < BROAD_SIZE; i++) {
		for (int j = 0; j < BROAD_SIZE ; j++) {
			if (this->board[i][j] == EMPTY) {

				//�ж���Ϸ����6�غ�֮�� ��������Χ1*1������������ 6�غ��Ժ���Χ2*2������������
 				if (this->allSteps.size < 6) {
					if (!hasNeighber(i, j, 1, 1, this->board)) continue;
				}
				else if (!hasNeighber(i, j, 2, 2, this->board))continue;

				int scoreCom=this->scoreCom[i][j];
				int scoreHum = this->scoreHum[i][j];
				int max=scoreCom;
				if (max < scoreHum)
					max = scoreHum;




			}//end of if
		}
	}



}

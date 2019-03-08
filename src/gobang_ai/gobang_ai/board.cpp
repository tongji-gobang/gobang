#include"board.h"


/*��ʾ�ڵ�ǰλ����һ�����Ӻ�ķ���
*Ϊ�����ܿ��ǣ�������һ��dir������
*���û�д�����Ĭ�ϼ��������ĸ�����
*�������ֵ����ֻ��������һ�������ֵ
*/
#define UNDEFINED -1

int scorePoint(board &b, int px, int py, int role, int dir = UNDEFINED)
{
	int result = 0, radius = 8, empty = 0, count = 0,
		block = 0, secondCount = 0;//��һ�������count
	int len = BROAD_SIZE;
	int i, t;

	//dir=0ʱ��������y����Ʒ�
	if (dir == UNDEFINED || dir == 0) {
		//reset
		count = 1;
		block = 0;
		empty = -1;
		secondCount = 0;

		//��y���ӵķ�����
		for (i = py + 1;; i++) {
			if (i >= len) {
				block++;
				break;
			}
			t = b.board[px][i];
			if (t == EMPTY) {
				if (empty == -1 && i < len - 1 && b.board[px][i + 1] == role) {
					empty = count;
					continue;
				}
				else
					break;
			}
			if (t == role) {
				count++;
				continue;
			}
			else {
				block++;
				break;
			}
		}//end of for

		 //��y��С�ķ�����
		for (i = py - 1;; i--) {
			if (i < 0) {
				block++;
				break;
			}
			t = b.board[px][i];
			if (t == EMPTY) {
				if (empty == -1 && i > 0 && b.board[px][i - 1] == role) {
					empty = 0;//ע��������0����Ϊ�Ǵ��������ߵ�
					continue;
				}
				else
					break;
			}
			if (t == role) {
				secondCount++;
				//ԭ����empty !== -1 && empty ++ ��֪����
				continue;
			}
			else {
				block++;
				break;
			}
		}//end of for

		count += secondCount;
		b.scoreCache[role][0][px][py] = countToScore(count, block, empty);
	}//end of if

	result += b.scoreCache[role][0][px][py];
}



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

				int p[2] = {i,j};


				if (scoreCom >= FIVE) {
					fives.push_back(p);
				}
				else if (scoreHum >= FIVE) {
					fives.push_back(p);
				}
				else if (scoreCom >= FOUR) {
					comfours.push_back(p);
				}
				else if (scoreHum >= FOUR) {
					humfours.push_back(p);
				}
				else if (scoreCom >= BLOCKED_FOUR) {
					comblockedfours.push_back(p);
				}
				else if (scoreHum >= BLOCKED_FOUR) {
					humblockedfours.push_back(p);
				}
				else if (scoreCom >= 2 * THREE) {
					//�ܳ�˫��Ҳ��
					comtwothrees.push_back(p);
				}
				else if (scoreHum >= 2 * THREE) {
					humtwothrees.push_back(p);
				}
				else if (scoreCom >= THREE) {
					comthrees.push_back(p);
				}
				else if (scoreHum >= THREE) {
					humthrees.push_back(p);
				}
				else if (scoreCom >= TWO) {
					comtwos.insert(comtwos.begin(),p);
				}
				else if (scoreHum >= TWO) {
					humtwos.insert(humtwos.begin(), p);
				}
				else neighbors.push_back(p);


			}//end of if
		}
	}

	//���ܳ�5 ���ɱ���س�5��
	if (fives.size) return fives;

	//���л��ķ��ػ��ĵ�
	if (role == COM&&comfours.size) return comfours;
	if (role == HUM&&humfours.size) return humfours;

	// �����л��ĳ��ģ��Լ����Ķ�û����ֻ���Ƕ������ ����ʱ������ľͲ��ÿ�����)
	if (role == COM && humfours.size && !comblockedfours.size) return humfours;
	if (role == HUM && comfours.size && !humblockedfours.size) return comfours;




	// �����л����Լ��г��ģ��򶼿�����
	vector<point> four;
	vector<point> blockfour;

	if (role == COM) {
		four.insert(four.begin(), comfours.begin(), comfours.end());
		four.insert(four.end(), humfours.begin(), humfours.end());
	}
	else {
		four.insert(four.begin(), humfours.begin(), humfours.end());
		four.insert(four.end(), comfours.begin(), comfours.end());
	}

	if (role == COM) {
		blockfour.assign(comblockedfours.begin(), comblockedfours.end());
		blockfour.insert(blockfour.end(), humblockedfours.begin(), humblockedfours.end());
	}
	else {
		blockfour.assign(humblockedfours.begin(), humblockedfours.end());
		blockfour.insert(blockfour.end(), comblockedfours.begin(), comblockedfours.end());
	}

	if (four.size) {
		four.insert(four.end(), blockfour.begin(), blockfour.end());
		return four;
	}



	//��ʱ˫��һ����û�л��� ���Խ����� ˫�� ���� ��Ҫ����
	vector<point> result;
	if (role == COM) {
		result.assign(comtwothrees.begin(), comtwothrees.end());
		result.insert(result.end(), humtwothrees.begin(), humtwothrees.end());
		result.insert(result.end(), comblockedfours.begin(), comblockedfours.end());
		result.insert(result.end(), humblockedfours.begin(), humblockedfours.end());
		result.insert(result.end(), comthrees.begin(), comthrees.end());
		result.insert(result.end(), humthrees.begin(), humthrees.end());
	}
	else
	{
		result.assign(humtwothrees.begin(), humtwothrees.end());
		result.insert(result.end(), comtwothrees.begin(), comtwothrees.end());
		result.insert(result.end(), humblockedfours.begin(), humblockedfours.end());
		result.insert(result.end(), comblockedfours.begin(), comblockedfours.end());
		result.insert(result.end(), humthrees.begin(), humthrees.end());
		result.insert(result.end(), comthrees.begin(), comthrees.end());
	}
	//˫������
	if (comtwothrees.size || humtwothrees.size) return result;
	//��onlyThrees����Ϊtrue ��ֻ���ش��ڵ��ڻ����ĵ�
	if (onlyThrees) return result;




	vector<point>twos;
	if (role == COM) {
		twos.assign(comtwos.begin(), comtwos.end());
		twos.insert(twos.begin(), humtwos.begin(), humtwos.end());
	}
	else {
		twos.assign(humtwos.begin(), humtwos.end());
		twos.insert(twos.begin(), comtwos.begin(), comtwos.end());
	}


}

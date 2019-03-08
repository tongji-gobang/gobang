#include"board.h"


/*表示在当前位置下一个棋子后的分数
*为了性能考虑，增加了一个dir参数，
*如果没有传入则默认计算所有四个方向，
*如果传入值，则只计算其中一个方向的值
*/
#define UNDEFINED -1

int scorePoint(board &b, int px, int py, int role, int dir = UNDEFINED)
{
	int result = 0, radius = 8, empty = 0, count = 0,
		block = 0, secondCount = 0;//另一个方向的count
	int len = BROAD_SIZE;
	int i, t;

	//dir=0时，好像是y方向计分
	if (dir == UNDEFINED || dir == 0) {
		//reset
		count = 1;
		block = 0;
		empty = -1;
		secondCount = 0;

		//往y增加的方向走
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

		 //往y减小的方向走
		for (i = py - 1;; i--) {
			if (i < 0) {
				block++;
				break;
			}
			t = b.board[px][i];
			if (t == EMPTY) {
				if (empty == -1 && i > 0 && b.board[px][i - 1] == role) {
					empty = 0;//注意这里是0，因为是从右往左走的
					continue;
				}
				else
					break;
			}
			if (t == role) {
				secondCount++;
				//原文是empty !== -1 && empty ++ 不知何意
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


	//将棋盘信息复制到tempBroad
	int tempBroad[BROAD_SIZE][BROAD_SIZE];
	for (int i = 0; i < BROAD_SIZE; i++)
		for (int j = 0; j < BROAD_SIZE; j++)
			tempBroad[i][j] = this->board[i][j];

	//将角色反转 若现在是作为电脑则改变角色为玩家 反之亦然
	int reverseRole;
	if (role == HUM)
		role = COM;
	else
		role = HUM;




	//遍历棋盘寻找下棋点 
	for (int i = 0; i < BROAD_SIZE; i++) {
		for (int j = 0; j < BROAD_SIZE ; j++) {
			if (this->board[i][j] == EMPTY) {

				//判断游戏进行6回合之内 若棋子周围1*1无棋子则跳过 6回合以后周围2*2无棋子则跳过
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
					//能成双三也行
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

	//若能成5 则必杀返回成5点
	if (fives.size) return fives;

	//若有活四返回活四点
	if (role == COM&&comfours.size) return comfours;
	if (role == HUM&&humfours.size) return humfours;

	// 对面有活四冲四，自己冲四都没，则只考虑对面活四 （此时对面冲四就不用考虑了)
	if (role == COM && humfours.size && !comblockedfours.size) return humfours;
	if (role == HUM && comfours.size && !humblockedfours.size) return comfours;




	// 对面有活四自己有冲四，则都考虑下
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



	//此时双方一定都没有活四 所以将锁四 双三 活三 都要考虑
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
	//双三返回
	if (comtwothrees.size || humtwothrees.size) return result;
	//若onlyThrees参数为true 则只返回大于等于活三的点
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

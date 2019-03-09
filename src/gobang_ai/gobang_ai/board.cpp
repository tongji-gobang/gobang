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


vector<point> board::gen(int role, bool onlyThrees = false, bool starSpread = false) {
	if (this->count <= 0) {
		vector<point> a = { {7,7} };
		return a;
	}
	vector<point> fives ;
	vector<point> comfours ;
	vector<point> humfours ;
	vector<point> comblockedfours ;
	vector<point> humblockedfours ;
	vector<point> comtwothrees ;
	vector<point> humtwothrees ;
	vector<point> comthrees ;
	vector<point> humthrees ;
	vector<point> comtwos ;
	vector<point> humtwos ;
	vector<point> neighbors ;


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

				point p = {i,j};


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

// 下子函数，需要zobrist函数
void board::put(point p, int role)
{
	//p.role = role
	
	printf("%s put [%d,%d]", (role == COM ? "Com" : "Hum"), p.pos[0], p.pos[1]);
	board[p.pos[0]][p.pos[1]] = role;//在棋盘上做好标记，说是role下的
	zobrist.go(p[0], p[1], role);//未实现
	updateScore(p);//未实现
	currentSteps.push_back(p);
	allSteps.push_back(p);
	//stepsTail = [];
	count++;

}

void board::remove(point p)
{
	int role = board[p.pos[0]][p.pos[1]];//看是悔谁的棋
	printf("%s remove [%d,%d]", (role == COM ? "Com" : "Hum"), p.pos[0], p.pos[1]);
	zobrist.go(p[0], p[1], role);//未实现
	updateScore(p);//未实现
	currentSteps.pop_back();
	allSteps.pop_back();
	//stepsTail = [];
	count--;

}

/*
	* 悔棋
*/
void board::backward()
{
	if ( this->allSteps.size() < 2 )
		return ;
	for ( int i = 0; i < 2; ++i )
	{
		auto s = this->allSteps[this->allSteps.size() - 1];
		this->remove(s);
		this->stepsTail.push_back(s);		// stepsTail
	}
}

/*
	* 前进
*/
void board::forward()
{
	if ( this->stepsTail.size() < 2 )
		return ;

	for ( int i = 0; i < 2; ++i )
	{
		auto s = this->stepsTail[this->stepsTail.size() - 1];
		this->stepsTail.pop_back();
		this->put( s, s.role );
	}
}
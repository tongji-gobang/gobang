#include"board.h"
#define UNDEFINED -2
/*表示在当前位置下一个棋子后的分数
 *为了性能考虑，增加了一个dir参数，
 *如果没有传入则默认计算所有四个方向，
 *如果传入值，则只计算其中一个方向的值
 */
int scorePoint(board &b, const int px, const int py, const int role, const int dir = UNDEFINED)
{
	int result = 0, radius = 8, empty = 0, count = 0,
		block = 0, secondCount = 0;//另一个方向的count
	int len = BROAD_SIZE;
	int i, t;
	int x, y;
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
				//原文是empty !== -1 && empty ++
				if (empty != -1)
					empty++;
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

	//dir=1时，x方向计分
	if (dir == UNDEFINED || dir == 1) {
		//reset
		count = 1;
		block = 0;
		empty = -1;
		secondCount = 0;

		for (i = px + 1;; i++) {
			if (i >= len) {
				block++;
				break;
			}
			t = b.board[i][py];
			if (t == EMPTY) {
				if (empty == -1 && i < len - 1 && b.board[i + 1][py] == role) {
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

		for (i = px - 1;; i--) {
			if (i < 0) {
				block++;
				break;
			}
			t = b.board[i][py];
			if (t == EMPTY) {
				if (empty == -1 && i > 0 && b.board[i - 1][py] == role) {
					empty = 0;
					continue;
				}
				else
					break;
			}
			if (t == role) {
				secondCount++;
				//原文是empty !== -1 && empty ++
				if (empty != -1)
					empty++;
				continue;
			}
			else {
				block++;
				break;
			}

			count += secondCount;
			b.scoreCache[role][1][px][py] = countToScore(count, block, empty);
		}//end of for
	}//end of if

	result += b.scoreCache[role][1][px][py];

	//dir=2时，xy同时增大的斜向
	if (dir == UNDEFINED || dir == 2) {
		//reset
		count = 1;
		block = 0;
		empty = -1;
		secondCount = 0;

		for (i = 1;; i++) {
			x = px + i;
			y = py + i;
			if (x >= len || y >= len) {
				block++;
				break;
			}
			t = b.board[x][y];
			if (t == EMPTY) {
				if (empty == -1 && x < len - 1 && y < len - 1 && b.board[x + 1][y + 1] == role) {
					empty == count;
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

		for (i = 1;; i++) {
			x = py - i;
			y = py - i;
			if (x < 0 || y < 0) {
				block++;
				break;
			}
			t = b.board[x][y];
			if (t == EMPTY) {
				if (empty == -1 && x > 0 && y > 0 && b.board[x - 1][y - 1] == role) {
					empty = 0;
					continue;
				}
				else
					break;
			}
			if (t == role) {
				secondCount++;
				//原文是empty !== -1 && empty ++
				if (empty != -1)
					empty++;
				continue;
			}
			else {
				block++;
				break;
			}
		}//end of for

		count += secondCount;
		b.scoreCache[role][2][px][py] = countToScore(count, block, empty);
	}//end of if

	result += b.scoreCache[role][2][px][py];

	//dir=3时，xy变化相反的斜向
	if (dir == UNDEFINED || dir == 3) {
		//reset
		count = 1;
		block = 0;
		empty = -1;
		secondCount = 0;

		for (i = 1;; i++) {
			x = px + i;
			y = py - i;
			if (x < 0 || y < 0 || x >= len || y >= len) {
				block++;
				break;
			}
			t = b.board[x][y];
			if (t == EMPTY) {
				if (empty == -1 && x < len - 1 && y < len - 1 && b.board[x + 1][y - 1] == role) {
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

		for (i = 1;; i++) {
			x = px - i;
			y = py + i;
			if (x < 0 || y < 0 || x >= len || y >= len) {
				block++;
				break;
			}
			t = b.board[x][y];
			if (t == EMPTY) {
				if (empty == -1 && x > 0 && y > 0 && b.board[x - 1][y - 1] == role) {
					empty = 0;
					continue;
				}
				else
					break;
			}
			if (t == role) {
				secondCount++;
				//原文是empty !== -1 && empty ++
				if (empty != -1)
					empty++;
				continue;
			}
			else {
				block++;
				break;
			}
		}//end of for

		count += secondCount;
		b.scoreCache[role][3][px][py] = countToScore(count, block, empty);
	}//end of if
	result += b.scoreCache[role][3][px][py];

	return result;
}

int countToScore(int count, int block, int empty = UNDEFINED)
{
	if (empty == UNDEFINED)
		empty = 0;

	//没有空位
	if (empty <= 0) {
		if (count >= 5)
			return FIVE;
		if (block == 0) {
			switch (count) {
				case 1:
					return ONE;
				case 2:
					return TWO;
				case 3:
					return THREE;
				case 4:
					return FOUR;
			}
		}

		if (block == 1) {
			switch (count) {
				case 1:
					return BLOCKED_ONE;
				case 2:
					return BLOCKED_TWO;
				case 3:
					return BLOCKED_THREE;
				case 4:
					return BLOCKED_FOUR;
			}
		}
	}
	else if (empty == 1 || empty == count - 1) {//第一个是空位
		if (count >= 6)
			return FIVE;
		if (block == 0) {
			switch (count) {
				case 2:
					return TWO / 2;
				case 3:
					return THREE;
				case 4:
					return BLOCKED_FOUR;
				case 5:
					return FOUR;
			}
		}

		if (block == 1) {
			switch (count) {
				case 2:
					return BLOCKED_TWO;
				case 3:
					return BLOCKED_THREE;
				case 4:
					return BLOCKED_FOUR;
				case 5:
					return BLOCKED_FOUR;
			}
		}
	}
	else if (empty == 2 || empty == count - 2) {//第二个是空位
		if (count >= 7)
			return FIVE;
		if (block == 0) {
			switch (count) {
				case 3:
					return THREE;
				case 4:
				case 5:
					return BLOCKED_FOUR;
				case 6:
					return FOUR;
			}
		}

		if (block == 1) {
			switch (count) {
				case 3:
					return BLOCKED_THREE;
				case 4:
					return BLOCKED_FOUR;
				case 5:
					return BLOCKED_FOUR;
				case 6:
					return FOUR;
			}
		}

		if (block == 2) {
			switch (count) {
				case 4:
				case 5:
				case 6:
					return BLOCKED_FOUR;
			}
		}
	}
	else if (empty == 3 || empty == count - 3) {
		if (count >= 8)
			return FIVE;
		if (block == 0) {
			switch (count) {
				case 4:
				case 5:
					return THREE;
				case 6:
					return BLOCKED_FOUR;
				case 7:
					return FOUR;
			}
		}

		if (block == 1) {
			switch (count) {
				case 4:
				case 5:
				case 6:
					return BLOCKED_FOUR;
				case 7:
					return FOUR;
			}
		}

		if (block == 2) {
			switch (count) {
				case 4:
				case 5:
				case 6:
				case 7:
					return BLOCKED_FOUR;
			}
		}
	}
	else if (empty == 4 || empty == count - 4) {
		if (count >= 9)
			return FIVE;
		if (block == 0) {
			switch (count) {
				case 5:
				case 6:
				case 7:
				case 8:
					return FOUR;
			}
		}

		if (block == 1) {
			switch (count) {
				case 4:
				case 5:
				case 6:
				case 7:
					return BLOCKED_FOUR;
				case 8:
					return FOUR;
			}
		}

		if (block == 2) {
			switch (count) {
				case 5:
				case 6:
				case 7:
				case 8:
					return BLOCKED_FOUR;
			}
		}
	}
	else if (empty == 5 || empty == count - 5)
		return FIVE;

	return 0;
}

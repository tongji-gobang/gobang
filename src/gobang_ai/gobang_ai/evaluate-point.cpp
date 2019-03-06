#include"board.h"
#define UNDEFINED -1
/*表示在当前位置下一个棋子后的分数
 *为了性能考虑，增加了一个dir参数，
 *如果没有传入则默认计算所有四个方向，
 *如果传入值，则只计算其中一个方向的值
 */
int scorePoint(const board &b, int px, int py, int role, int dir = UNDEFINED)
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
	}//end of if
}


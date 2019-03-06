#include"board.h"
#define UNDEFINED -1
/*��ʾ�ڵ�ǰλ����һ�����Ӻ�ķ���
 *Ϊ�����ܿ��ǣ�������һ��dir������
 *���û�д�����Ĭ�ϼ��������ĸ�����
 *�������ֵ����ֻ��������һ�������ֵ
 */
int scorePoint(const board &b, int px, int py, int role, int dir = UNDEFINED)
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
	}//end of if
}


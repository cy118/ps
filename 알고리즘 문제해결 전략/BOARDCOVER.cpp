#include <iostream>

using namespace std;

/*
* problem ID : BOARDCOVER
* from algospot.com
*
* 2017.12.26 TUE
*/

int height, width;
int moving[4][2][2]
= { {{0,1}, {1,0}},
		{{0,1}, {1,1}},
		{{1,0}, {1,1}},
		{{1,-1}, {1,0}} };

/* cover with shape 0 ~ 3 when iscover is -1, otherwise, uncover it */
bool cover(int board[20][20], int h, int w, int shape, int iscover) {
	board[h][w] += iscover;  // cover or uncover the first block

	int iscovered = true;
	for (int bl = 0; bl < 2; ++bl) {
		int newh = h + moving[shape][bl][0];
		int neww = w + moving[shape][bl][1];;
		if (newh >= height || neww >= width || newh < 0 || neww < 0) iscovered = false;
		else if ((board[newh][neww] += iscover) < 0) iscovered = false;
	}
	return iscovered;
}

/* count the # of cases that board can be covered */
int cntcases(int board[20][20], int blknum) {
	if (blknum == 0)  return 1;  // check if no blocks needed

	/* find first block */
	int fsth, fstw;
	bool find = false;
	for (int h = 0; h < height; ++h) {
		for (int w = 0; w < width; ++w) {
			if (board[h][w]) {
				fsth = h;
				fstw = w;
				find = true;
				break;
			}
		}
		if (find)  break;
	}

	/* check if the first block can be matched */
	int ret = 0;
	for (int shape = 0; shape < 4; ++shape) {
		if (cover(board, fsth, fstw, shape, -1))
			ret += cntcases(board, blknum - 1);
		cover(board, fsth, fstw, shape, 1);
	}
	return ret;
}

int main() {
	int board[20][20];
	int casenum;

	cin >> casenum;

	while (casenum-- > 0) {
		char bd;
		int whitenum = 0;

		cin >> height >> width;

		/* get the board */
		for (int h = 0; h < height; ++h) {
			for (int w = 0; w < width; ++w) {
				cin >> bd;
				if (bd == '#')  board[h][w] = false;
				else {
					whitenum++;
					board[h][w] = true;
				}
			}
		}

		/* cnt the # of board cover */
		if (whitenum % 3 != 0)  printf("0\n");
		else {
			int blocknum = whitenum/3;
			printf("%d\n", cntcases(board, blocknum));
		}
	}
}

/*
 * if need, printboard() can print the board status
 * void printboard(int board[20][20]) {
 *	for (int h = 0; h < height; ++h) {
 *		for (int w = 0; w < width; ++w) {
 *			if (board[h][w] <= 0) printf("# ");
 *			else printf("^ ");
 *		}
 *		printf("\n");
 *	}
 * }
 */
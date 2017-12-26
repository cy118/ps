#include <iostream>
#include <string>
#include <CoreWindow.h> // for visualization

using namespace std;

/* 
 * problem ID : BOGGLE
 * from algospot.com 
 * 
 * 2017.12.24 SUN
 * this code uses brute-force search,
 * so it can be too slow
 */

#define BOARDX 5
#define BOARDY 5

int movexy[8][2] = { {-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1} };
int getroad[BOARDX*BOARDY][2];
int cntroad = 0;
char board[BOARDY][BOARDX]
= { {'F','O','N','E','C'},
		{'A','I','F','E','M'},
		{'D','A','N','D','E'},
		{'F','I','C','E','E'},
		{'A','Y','C','E','E'} };

bool hasWord(int y, int x, string word) {
	getroad[++cntroad][0] = y;  // watch out! getroad[0] saves nothing!
	getroad[cntroad][1] = x;

	if (y > BOARDY - 1 || x > BOARDX - 1 || y < 0 || x < 0)
		return false;  // check the range

	if (word.at(0) != board[y][x])
		return false;  // check the first word

	if (word.size() == 1)
		return true;  // if the word size is 1, return true

	for (int i = 0; i < 8; ++i)
		if (board[y + movexy[i][0]][x + movexy[i][1]] == word.at(1)) {
			if (hasWord(y + movexy[i][0], x + movexy[i][1], word.substr(1)))
				return true;
			else cntroad--;
		}
	return false;
}

void printroad(int cnt) {
	if (cnt > cntroad)  return; // done print road

	int y = getroad[cnt][0];
	int x = getroad[cnt][1];
	for (int yc = 0; yc < BOARDY; ++yc) {
		for (int xc = 0; xc < BOARDX; ++xc) {
			if (x == xc && y == yc) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				printf("%c ", board[yc][xc]);
			} else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				printf("%c ", board[yc][xc]);
			}
		}
		printf("\n");
	}
	Sleep(400);
	system("cls");
	printroad(cnt+1);
}

int main() {
	if (hasWord(0, 0, "FINDMEFINDCY")) {
		printroad(1);
		printf("got it!\n");
	}	else printf("there's no word here\n");
}
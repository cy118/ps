#include <iostream>
#include <string>

using namespace std;

/*
* problem ID : QUADTREE
* from algospot.com
*
* 2017.12.30 SAT
*/

int pos = 0;
string reverse(string str) {
	pos++;
	if (str.at(pos) != 'x')
		return string(1, str.at(pos));
	string upperleft = reverse(str);
	string upperright = reverse(str);
	string lowerleft = reverse(str);
	string lowerright = reverse(str);
	return "x" + lowerleft + lowerright + upperleft + upperright;
}

int main() {
	int casenum;
	cin >> casenum;

	while (casenum-- > 0) {
		pos = -1;
		string qdtr;
		cin >> qdtr;
		cout << reverse(qdtr) << endl;
	}
}

/*
 * below code is not used in the solution,
 * but gives some impression about how the split conquest is done
 * It saves the whole blocks in the depdtr char array
 */

/* 
#include <math.h>
#include <algorithm>

#define MAX_SIZE 1000
char depdtr[MAX_SIZE][MAX_SIZE];

// decompress the input and save it at depdtr which means decompreesed puard tree
void decompress(string::iterator& it, int y, int x, int size) {
	char str = *(it++);
	if (str != 'x') {
		for (int dy = 0; dy < size; dy++)
			for (int dx = 0; dx < size; dx++) {
				depdtr[y + dy][x + dx] = str;
		}
	}
	else {
		int newsize = size / 2;
		decompress(it, y, x, newsize);
		decompress(it, y, x + newsize, newsize);
		decompress(it, y + newsize, x, newsize);
		decompress(it, y + newsize, x + newsize, newsize);
	}
}

// get the depth of quad-block-tree
int getsize(string str) {
	int xcnt = 0;
	int ret = 0;
	int needcnt = 1;

	for (int i = 0; i < str.size(); ++i) {
		if (str.at(i) == 'x') {
			needcnt += 3;
			xcnt ++;
		}
		else {
			needcnt--;
			if (needcnt == 3 || needcnt == 2 || needcnt == 1) {
				ret = max(xcnt, ret);
				xcnt = 1;
			}
		}
	}
	return ret;
} */
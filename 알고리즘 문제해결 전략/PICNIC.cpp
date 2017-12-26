#include <iostream>

using namespace std;

/*
 * problem ID : PICNIC
 * from algospot.com
 *
 * 2017.12.26 TUE
 */

int ppnum;
bool friends[10][10];

int cntpairs(bool ispair[10]) {
	/* check if every friends have their pair */ 
	int fst = -1;
	for (int p = 0; p < ppnum; ++p) {
		if (!ispair[p]) {
			fst = p;
			break;
		}
	}
	if (fst == -1) return 1;

	/* find pair */
	int ret = 0;
	for (int snd = fst; snd < ppnum; ++snd) {
		if (!ispair[snd] && friends[fst][snd]) {
				ispair[fst] = ispair[snd] = true;
				ret += cntpairs(ispair);
				ispair[fst] = ispair[snd] = false;
		}
	}
	return ret;
}

int main() {
	int casenum, friendnum;
	cin >> casenum;
	
	while (casenum-- > 0) {
		cin >> ppnum;
		cin >> friendnum;

		/* initialize friend list */
		for (int p1 = 0; p1 < 10; ++p1) {
			for (int p2 = 0; p2 < 10; ++p2)
				friends[p1][p2] = false;
		}

		/* get friends list */
		while (friendnum-- > 0) {
			int fr1, fr2;
			cin >> fr1;
			cin >> fr2;

			if (fr1 > fr2)  friends[fr2][fr1] = true;
			else friends[fr1][fr2] = true;
		}

		/* cnt num */
		bool ispair[10];
		for (int i = 0; i < 10; ++i) ispair[i] = false;
		printf("%d\n", cntpairs(ispair));
	}	
}


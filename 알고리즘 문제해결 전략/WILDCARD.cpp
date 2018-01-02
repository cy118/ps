#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

/*
* problem ID : WILDCARD
* from algospot.com
*
* 2018.01.02 TUE
*/

string wild;
int wildlen;  // indicates the length of string wild
int cache[50][100];
// cache[a][b] indicates, if file start at b match with wild start at a

/*
 * returns if file start at fp(file pointer)
 * matches wih wild start at wp(wild pointer)
 */
int ismatch(string file, int wp, int fp) {
	if (fp == file.size() && wp == wildlen)  return 1;  // means all file name char have been passed
	else if (fp == file.size()) {
		int tmpwp = wp;
		while (tmpwp < wildlen)  if (wild.at(tmpwp++) != '*') return 0;
		return 1;
	}
	if (wp == wildlen) return 0;

	int& ret = cache[wp][fp];  // uses memorization
	if (ret != -1)  return ret;

	ret = false;
	char wildch = wild.at(wp);
	if (wildch == '*')
		ret = ismatch(file, wp, fp+1) || ismatch(file, wp+1, fp) || ismatch(file, wp+1, fp+1);
	else if (wildch == '?')
		ret = ismatch(file, wp+1, fp+1);
	else if (file.at(fp) == wild.at(wp))
		ret = ismatch(file, wp+1, fp+1);
	else
		return ret = false;
	return ret;
}

int main() {
	int casenum;

	cin >> casenum;

	while (casenum-- > 0) {
		cin >> wild;
		wildlen = wild.size();
		int filenum;
		cin >> filenum;
		int ansnum = 0;
		string ans[100];
		while (filenum-- > 0) {
			string fn;
			cin >> fn;
			for (int i = 0; i < 50; ++i) for (int j = 0; j < 100; ++j) cache[i][j] = -1;
			if (ismatch(fn, 0, 0) == 1)  ans[ansnum++] = fn;
		}
		sort(ans, ans + ansnum);
		for (int i = 0; i < ansnum; ++i)  cout << ans[i] << endl;
	}
}
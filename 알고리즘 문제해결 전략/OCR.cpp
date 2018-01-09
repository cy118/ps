#pragma warning(disable:4996)
#include <iostream>
#include <stdio.h>
#include <string>
#include <algorithm>

using namespace std;

/*
 * problem ID : OCR
 * from algospot.com
 *
 * 2017.01.09 TUE
 */


/* 
 * wn: the number of words
 * p: the possibility of each words
 * injp: the possibility of word j is the next word of i
 * iisjp: the possibility of word i is classified as j
 * n: the number of words in a sentence
 * i: the index of each words in a sentence
 */
int wn;
double p[500], injp[500][500], iisjp[500][500];
int n, sen[100];

double cache[502][102];
int ans[502][102];

/* 
 * return possibility of sentence guessing when last word is 'last',
 * and current index of sentence is 'wp'
 */
double calp(int last, int wp) {
	if (wp == n)  return 1;

	double& ret = cache[last+1][wp];
	if (ret != -1)  return ret;

	ret = 0;
	if (last == -1)  for (int i = 0; i < wn; ++i) {
		double tmp = p[i] * iisjp[i][sen[wp]] * calp(i, wp + 1);
		if (tmp > ret) {
			ans[last+1][wp] = i;
			ret = tmp;
		}
	}
	else for (int i = 0; i < wn; ++i) {
		double tmp = injp[last][i] * iisjp[i][sen[wp]] * calp(i, wp + 1);
		if (tmp > ret) {
			ans[last+1][wp] = i;
			ret = tmp;
		}
	}
	return ret;
}

/* print the answer caculated at calp */
void getans(int i, int last, string words[500]) {
	if (i == n) {
		printf("\n");
		return;
	}
	cout << words[ans[last+1][i]] <<" ";
	getans(i + 1, ans[last+1][i], words);
}

int main() {
	int sn;  //the number of sentence
	string words[500];

	/* get inputs */
	scanf("%d %d", &wn, &sn);
	for (int i = 0; i < wn; ++i)  cin >> words[i];
	for (int i = 0; i < wn; ++i)  scanf("%lf", &p[i]);
	for (int i = 0; i < wn; ++i)  for (int j = 0; j < wn; ++j)  scanf("%lf", &injp[i][j]);
	for (int i = 0; i < wn; ++i)  for (int j = 0; j < wn; ++j)  scanf("%lf", &iisjp[i][j]);

	while (sn-- > 0) {
		string tmp;
		for (int k = 0; k < 502; ++k)  for (int j = 0; j < 102; ++j)  cache[k][j] = -1;

		scanf("%d", &n);
		/* saves the sentense as their words index */
		for (int i = 0; i < n; ++i) {
			cin >> tmp;
			sen[i] = find(words, words+wn, tmp)-words;
		}
		calp(-1, 0);
		getans(0, -1, words);
	}
}
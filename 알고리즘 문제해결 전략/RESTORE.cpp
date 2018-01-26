#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

/*
 * problem ID : RESTORE
 * from algospot.com
 *
 * 2017.01.26 FRI
 * this is nusty code...
 */

int k;  // number of strings provided
string parts[15];  // saves the strings provided

int cache[15][1 << 15];
int overlap[15][15];  // overlap[i][j] indicates the length of overlap parts[i] - parts[j]

int removed;

/* 
 * calculates the most longest overlap length,
 * when 'last' is last string of previously made sequence,
 * and used are already used 
 */
int restore(int last, int used) {
	if (used == (1 << k) - 1)  return 0;
	
	int& ret = cache[last][used];
	if (ret != -1)  return ret;

	ret = 0;
	for (int next = 0; next < k; ++next) {
		if ((used & (1 << next)) == 0) {
			ret = max(ret, overlap[last][next] + restore(next, used + (1 << next)));
		}
	}
	return ret;
}

/* 
 * reconstruct the strings to a return 
 * shortest string sequence using restore
 */
string reconstruct(int last, int used) {
	if (used == (1 << k) - 1)  return "";

	for (int next = 0; next < k; ++next) {
		if ((used & (1 << next)) == 0) {
			int isIt = overlap[last][next] + restore(next, used + (1 << next));
			if (isIt == restore(last, used)) {
				return (parts[next].substr(overlap[last][next])
					+ reconstruct(next, used + (1 << next)));
			}
		}
	}
	return "isFail";
}

/* find a first element of final sequence */
int getFirst() {
	int ret, max = -100;
	for (int i = 0; i < k; ++i) {
		int cmp = restore(i, 1 << i);
		if (cmp > max) {
			max = cmp;
			ret = i;
		}
	}
	return ret;
}

/* calculate the overlap length between parts[idx1] and parts[idx2] */
void caloverlap(int idx1, int idx2) {
	if (idx1 == idx2) {
		overlap[idx1][idx2] = -1;
		return;
	}

	overlap[idx1][idx2] = 0;
	string str1 = parts[idx1], str2 = parts[idx2];
	int strlen1 = str1.length(), strlen2 = str2.length();
	int maxOver = 0;
	for (int i = 1; i <= strlen2; ++i) {
		for (int j = i-1; j >= 0; --j) {
			if (strlen1 - i + j < 0)  break;
			if (str2.at(j) != str1.at(strlen1 - i + j)) {
				break;
			}
			else maxOver++;
		}
		
		if (maxOver == i && maxOver > overlap[idx1][idx2])  overlap[idx1][idx2] = maxOver;
		maxOver = 0;
	}
}

/* check if a string contains the other */
void isContain(int idx1, int idx2) {
	string str1 = parts[idx1], str2 = parts[idx2];
	if (str1.length() < str2.length())  return isContain(idx2, idx1);
	if (!str2.compare("ABCDEFGabc"))  return;

	if (str1.find(str2) != string::npos) {
		parts[idx2] = "ABCDEFGabc";
		removed++;
	}
}

int main() {
	int cn;

	cin >> cn;

	while (cn-- > 0) {
		removed = 0;
		cin >> k;
		for (int i = 0; i < k; ++i) {
			cin >> parts[i];
			int cnt = 0;
			for (int j = 0; j < i; ++j)
				isContain(i, j);
		}
		
		int pass = k-1;
		for (int i = 0; i < k; ++i) {
			if (!parts[i].compare("ABCDEFGabc")) {
				for (int j = pass; j > i; --j) {
					if (!parts[j].compare("ABCDEFGabc")) {
					} else {
						parts[i] = parts[j];
						pass = j - 1;
						break;
					}
				}	
			}
		}
		k -= removed;
		
		for (int i = 0; i < k; ++i)  for (int j = 0; j < k; ++j)
			caloverlap(i, j);
		for (int i = 0; i < k; ++i)  for (int j = 0; j < (1 << 15); ++j)
			cache[i][j] = -1;
		int first = getFirst();
		cout << parts[first] + reconstruct(first, 1 << first) << "\n";
	}
}
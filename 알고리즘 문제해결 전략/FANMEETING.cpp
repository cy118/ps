#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/*
 * problem ID : FANMEETING
 * from algospot.com
 *
 * 2018.01.02 TUE
 * change the problem to multiplication problem,
 * then uses karatsuba algorithm to handle big numbers
 *
 * this code cannot pass the judge online
 * it causes time exceed
 */

void addb(vector<int>& a, vector<int>& b, int k);  // returns a + b * 10^k
void subb(vector<int>& a, vector<int>& b);  // returns a - b
vector<int> mulb(vector<int> a, vector<int> b);  // returns a * b used when a and b are small

/* karatsuba multiplication returns a * b in O(n^lg3) time */
vector<int> karatsuba(vector<int> a, vector<int> b) {  
	int lena = a.size();
	int lenb = b.size();
	if (lena == 0 || lenb == 0)  return vector<int>();
	if (lena < lenb) return karatsuba(b, a);
	if (lena <= 50)  return mulb(a, b);
	int halfl = lena / 2;

	vector<int> a0(a.begin(), a.begin()+halfl);
	vector<int> a1(a.begin()+halfl, a.end());
	vector<int> b0(b.begin(), b.begin()+min<int>(halfl, lenb));
	vector<int> b1(b.begin()+min<int>(halfl, lenb), b.end());

	vector<int> z0, z1, z2;
	z0 = karatsuba(a0, b0);
	z2 = karatsuba(a1, b1);
	addb(a0, a1, 0);
	addb(b0, b1, 0);
	z1 = karatsuba(a0, b0);
	subb(z1, z0);
	subb(z1, z2);
	addb(z0, z1, halfl);
	addb(z0, z2, halfl + halfl);
	return z0;
}

/* 
 * cnt the # of cases that all members hug with fans
 * female = 0, male = 1
 * so, only when the result of multiplication is 0, it means hug
 */
int cnthug(vector<int> mem, vector<int> fan) {
	reverse(mem.begin(), mem.end());
	vector<int> mul = karatsuba(fan, mem);

	int cnt = 0;
	// the range of this for loop is tricky to think
	for (int i = mem.size()-1; i < fan.size(); ++i) {
		if (mul.at(i) == 0)  cnt++;
	}
	return cnt;
}

int main() {
	int casenum;
	
	cin >> casenum;

	while (casenum-- > 0) {
		vector<int> mem, fan;
		string tmp;
		cin >> tmp;
		for (int i = 0; i < tmp.size(); ++i)
			if (tmp.at(i) == 'F')  mem.push_back(0);
			else  mem.push_back(1);
		cin >> tmp;
		for (int i = 0; i < tmp.size(); ++i)
			if (tmp.at(i) == 'F')  fan.push_back(0);
			else  fan.push_back(1);
			printf("%d\n", cnthug(mem, fan));
	}
}

/* should carefully add it */
void addb(vector<int>& a, vector<int>& b, int k) {;
	a.resize(max(a.size(), b.size()+k));

	for (int i = 0; i < b.size(); ++i)
		a.at(i+k) += b.at(i);
}

void subb(vector<int>& a, vector<int>& b) {
	for (int i = 0; i < b.size(); ++i)
		a.at(i) -= b.at(i);
}

vector<int> mulb(vector<int> a, vector<int> b) {
	vector<int> c(a.size() + b.size() + 1, 0);
	for (int i = 0; i < a.size(); ++i)
		for (int j = 0; j < b.size(); ++j)
			c[i + j] += a[i] * b[j];
	return c;
}

/* this simple vector printing function is useful when debugging */
/*void printvec(vector<int> vec) {
	for (int i = 0; i < vec.size(); ++i) {
		printf("%d ", vec.at(i));
	}
	printf("\n");
}*/
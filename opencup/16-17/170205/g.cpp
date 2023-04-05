#include <bits/stdc++.h>

using namespace std; 

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;

int main() {
	int t = 0;
	cin >> t;
	if (t == 0) {
		printf("1 1\n1 2 3\n");
	} else {
		printf("4 11\n");
		printf("1 2 3\n");
		printf("1 2 4\n");
		printf("1 2 5\n");
		printf("1 2 6\n");
		printf("10 11 12\n");
		printf("10 13 14\n");
		printf("10 15 16\n");
		printf("10 17 18\n");
		printf("11 13 15\n");
		printf("3 4 7\n");
		printf("3 4 %d\n", t == 2 ? 6 : 5);
	}
}
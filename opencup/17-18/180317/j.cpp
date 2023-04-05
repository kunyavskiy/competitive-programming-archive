#include <bits/stdc++.h>

using namespace std; 

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;

int main() {
	int n;
	cin >> n;
	pair<int, int> z(n, 0);
	for (int i = 0; i <= n; i++) {
		int x = i, y = n;
		while (x <= y) {
			pair<int, int> tmp(x + y, x);
			z = min(z, tmp);
			int z = y - x;
			y = x, x = z;
		}
		pair<int, int> tmp(x + y, x);
		// printf("--- %d %d ---> %d %d\n", x, y, i, n);
		z = min(z, tmp);
	}
	cout << z.second << " " << z.first - z.second << endl;
}
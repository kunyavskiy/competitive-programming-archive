#include <bits/stdc++.h>

using namespace std; 

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;

int main() {
	int h, w;
	cin >> h >> w;
	if (h == 1) {
		forn(i, w)
			putchar('0' + (i % 2 == 0 || i == w - 1));
	} else if (w == 1) {
		forn(i, h) {
			putchar('0' + (i % 2 == 0 || i == h - 1));
			puts("");
		}
	} else {
		forn(i, h) {
			forn(j, w)
				putchar('0' + ((i == 0 && j % 2 == (w - 1) % 2) || (j == 0 && i % 2 == (h - 1) % 2)));
			puts("");
		}
	}
}

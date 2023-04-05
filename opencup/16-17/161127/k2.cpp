#include <bits/stdc++.h>

using namespace std; 

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define sz(a) (int)(a).size()

typedef long long ll;

const int N = 1e6;

char s[N + 1], s0[N + 1];
int n;
vector<int> v;

void flip( int i ) {
	if (sz(v) >= n / 3) return;
	printf("flip %d\n", i);
	s[i] ^= 1, s[i + 1] ^= 1;
	v.push_back(i + 1);
}

bool check() {
	int res = 0;
	forn(i, n - 1) res += (s[i] != s[i + 1]);
	printf("get %s\n", s);
	return res >= 2 * n / 3;
}

void one_more() {
	for (int i = 0; i + 3 < n; i += 3) {
		int j = i;
		while (j < i + 3 && s[j] == s[j + 1])
			j++;
		if (j >= i + 3)
			flip(i + 1);
		else {
			int k = j + 1;
			while (k < i + 3 && s[k] == s[k + 1])
				k++;
			if (k >= i + 3) {
				if (j == i) 	flip(i + 2), i--;
				if (j == i + 1) flip(i + 1);
				if (j == i + 2) flip(i + 2);
			}
			else {
				i = k + 1 - 3;
			}
		}
	}
}

void one_more2() {
	for (int i = n - 1; i - 3 >= 0; i -= 3) {
		int j = i;
		while (j > i - 3 && s[j] == s[j - 1])
			j--;
		if (j <= i - 3)
			flip(i - 2);
		else {
			int k = j - 1;
			while (k > i - 3 && s[k] == s[k - 1])
				k--;
			if (k <= i - 3) {
				if (j == i) 	flip(i - 3), i++;
				if (j == i - 1) flip(i - 2);
				if (j == i - 2) flip(i - 3);
			}
		}
	}
}

bool solve1() {
	v.clear();
	strcpy(s, s0);
	forn(_, 2) forn(t, 1)
		for (int i = 0; i + 1 < n; i++) {
			int df = (i > 0 && s[i - 1] == s[i]) + (s[i] != s[i + 1]) + (i + 2 < n && s[i + 1] == s[i + 2]) - 
				((i > 0 && s[i - 1] != s[i]) + (s[i] != s[i + 1]) + (i + 2 < n && s[i + 1] != s[i + 2]));
			if (df >= 2 - t && sz(v) < n / 3) {
				// printf("df=%d: ", df);
				flip(i);
			}
		}
	one_more();
	return check();
}

bool solve4() {
	v.clear();
	strcpy(s, s0);
	one_more2();
	forn(_, 2) forn(t, 2)
		for (int i = 0; i + 1 < n; i++) {
			int df = (i > 0 && s[i - 1] == s[i]) + (s[i] != s[i + 1]) + (i + 2 < n && s[i + 1] == s[i + 2]) - 
				((i > 0 && s[i - 1] != s[i]) + (s[i] != s[i + 1]) + (i + 2 < n && s[i + 1] != s[i + 2]));
			if (df >= 2 - t && sz(v) < n / 3) {
				// printf("df=%d: ", df);
				flip(i);
			}
		}
	one_more();
	return check();
}

bool solve2() {
	v.clear();
	strcpy(s, s0);
	if (strcmp(s, "001000") == 0) flip(1);
	forn(_, 2) forn(t, 2)
		for (int i = 0; i + 1 < n; i++) {
			int df = (i > 0 && s[i - 1] == s[i]) + (s[i] != s[i + 1]) + (i + 2 < n && s[i + 1] == s[i + 2]) - 
				((i > 0 && s[i - 1] != s[i]) + (s[i] != s[i + 1]) + (i + 2 < n && s[i + 1] != s[i + 2]));
			if (df >= 2 - t && sz(v) < n / 3) {
				// printf("df=%d: ", df);
				flip(i);
			}
		}
	one_more();
	return check();
}

bool solve3() {
	v.clear();
	strcpy(s, s0);
	forn(_, 2) forn(t, 2)
		for (int i = n - 2; i > 0; i--) {
			int df = (i > 0 && s[i - 1] == s[i]) + (s[i] != s[i + 1]) + (i + 2 < n && s[i + 1] == s[i + 2]) - 
				((i > 0 && s[i - 1] != s[i]) + (s[i] != s[i + 1]) + (i + 2 < n && s[i + 1] != s[i + 2]));
			if (df >= 2 - t && sz(v) < n / 3) {
				// printf("df=%d: ", df);
				flip(i);
			}
		}
	one_more();
	return check();
}

int main() {
//	scanf("%s", s);
//	n = strlen(s);
	n = 9;
	forn(pr, 1 << (n - 1)) {
	forn(i, n) s[i] = '0' + ((pr >> i) & 1);
	printf("check %s\n", s);
	if (strcmp(s, "000") == 0) continue;
	strcpy(s0, s);
	assert(solve1() || solve2() || solve3() || solve4());
	}
	// printf("%d\n", sz(v));
	// for (int x : v) printf("%d ", x);
}

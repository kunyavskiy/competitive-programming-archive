#include <bits/stdc++.h>

using namespace std; 

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define sz(a) (int)(a).size()

typedef long long ll;

const int N = 1e6;

char s[N + 1];
int n;
vector<int> v;

void flip( int i ) {
	s[i] ^= 1, s[i + 1] ^= 1;
	v.push_back(i + 1);
}

int main() {
	scanf("%s", s);
	n = strlen(s);

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
				if (j == i) 	flip(i + 2);
				if (j == i + 1) flip(i + 1);
				if (j == i + 2) flip(i + 2);
			}
		}
	}

	forn(t, 10)
		if (sz(v) < n / 3) {
			int mi = 0, opt = 0;
			for (int i = 1; i + 2 < n; i++) {
				int df = (s[i - 1] == s[i]) + (s[i] != s[i + 1]) + (s[i + 1] == s[i + 2]) - 
					((s[i - 1] != s[i]) + (s[i] != s[i + 1]) + (s[i + 1] != s[i + 2]));
				if (df > opt)
					opt = df, mi = i;
			}
			if (opt > 0) {
				fprintf(stderr, "opt=%d, mi=%d\n", opt, mi + 1);
				flip(mi);
			}
		}
	printf("%d\n", sz(v));
	for (int x : v) printf("%d ", x);
}

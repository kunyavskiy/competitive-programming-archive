#include <bits/stdc++.h>

using namespace std; 

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;

const int N = 1e7;

int p[N], f[N];
string s[N];

int inc( int i ) {
	for (; i < N; i |= i + 1)
		f[i]++;
}
int get( int i ) {
	int res = 0;
	for (; i >= 0; i &= i + 1, i--)
		res += f[i];
	return res;
}

bool s_less( int i, int j ) {
	return s[i] < s[j];
}

int main() {
	int n;
	cin >> n;
	forn(i, n)
		p[i] = i, s[i] = to_string(i + 1);
	sort(p, p + n, s_less);

	long long ans = 0;
	forn(i, n) {
		ans += i - get(p[i]);
		inc(p[i]);
	}
	cout << ans << endl;
}
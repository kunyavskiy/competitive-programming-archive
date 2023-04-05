#include <bits/stdc++.h>

using namespace std; 

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;

const int N = 1e4 + 1;

int n, p, f[N], res[N], inv[N], fact[N], inv_fact[N];

void add( int &a, int b ) { if ((a += b) >= p) a -= p; }
int mul( int a, int b ) { return (ll)a * b % p; }

int main() {
	cin >> n >> p;
	inv[1] = 1;
	for (int i = 2; i <= n; i++) {
		inv[i] = mul(inv[p % i], p - p / i);
		// printf("inv[%d] = %d\n", i, inv[i]);
	}
	inv_fact[0] = fact[0] = 1;
	forn(i, n) {
		fact[i + 1] = mul(fact[i], i + 1);
		inv_fact[i + 1] = mul(inv_fact[i], inv[i + 1]);
	}
	f[0] = 1;
	for (int k = 1; k <= n; k++) {
		for (int i = k; i <= n; i++) {
			f[i] = mul(f[i - 1], i - 1);
			add(f[i], f[i - k]);//mul(fact[i - 1], inv_fact[i - k])));
			f[i] = mul(f[i], inv[i]);
		}
		res[k] = mul(f[n], fact[n]);
		f[k] = 0;
	}
	for (int k = 2; k <= n; k++) 
		add(res[k - 1], p - res[k]);
	int sum = 0;
	for (int k = 1; k <= n; k++) 
		add(sum, mul(res[k], k));
	printf("%d\n", mul(sum, inv_fact[n]));
}
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <cstdlib>
#include <cstdio>
#include <stack>
#include <algorithm>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <iterator>
#include <functional>
#include <bitset>
#include <ctime>
#include <cassert>
#define pb push_back
#define mp make_pair      
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
using namespace std;
 
typedef long long ll;
typedef long double ld;

const int MOD = 1000000007;

int mul(int a, int b) {
	return (int)((a * 1LL * b) % MOD);
}

int pow(int a, int b) {
	int res = 1;
	while (b) {
		if (b & 1) res = mul(res, a);
		a = mul(a, a);
		b >>= 1;
 	}
 	return res;
}

int inv(int a) {
	return pow(a, MOD - 2);
}

void add(int& a, int b) {
	if ((a += b) >= MOD) a -= MOD;
}

const int MAXK = 2510;

class PermutationCounts {

vector<int> f;
vector<int> invf;

int cnk(int n, int k) {
	return mul(f[n], mul(invf[k], invf[n-k]));
}


int dp[MAXK][MAXK];
vector<int> pos;

int solve(int l, int r) {
	if (r - l <= 1) 
		return 1;
	int& ans = dp[l][r];
	if (ans != -1) return ans;
	ans = 0;
	eprintf("l = %d[%d], r = %d[%d]\n", l, pos[l], r, pos[r]);
	for (int i = l + 1; i < r; i++) {
		int lf = pos[i] - pos[l] - 1;
		int rg = pos[r] - pos[i] - 1;
		int coef = cnk(lf + rg, lf);
		int ansl = solve(l, i);
		int ansr = solve(i, r);
		eprintf("max in %d[%d]: %d %d %d\n", i, pos[i], coef, ansl, ansr);
		coef = mul(coef, mul(ansl, ansr));
		add(ans, coef);
	}
	return ans;
}

public:
    int countPermutations(int n, vector <int> pos) {
        pos.insert(pos.begin(), 0);
        for (int& x : pos)
        	x++;
        pos.push_back(n);
        this->pos = pos;
        f.resize(n+1);
        invf.resize(n+1);
        f[0] = invf[0] = 1;
        for (int i = 1; i <= n; i++) {
        	f[i] = mul(f[i-1], i);
        	invf[i] = inv(f[i]);
        }
        memset(dp, -1, sizeof(dp));
        return solve(0, (int)pos.size()-1);
    }
};

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

int mmul(int a, int b) {
	return (a * 1LL * b) % MOD;
}

void madd(int& a, int b) {
	if ((a += b) >= MOD) a -= MOD;
}

int mpow(int a, int b) {
	if (!b) return 1;
	if (b & 1) return mmul(mpow(a, b-1), a);
	return mpow(mmul(a, a), b/2);
}

class Seatfriends {


vector<int> fs;
vector<int> ifs;

void Precalc(int n){
	fs = vector<int>(n+1);
	ifs = vector<int>(n+1);
	fs[0] = ifs[0] = 1;
	for (int i = 1; i < n; i++) {
		fs[i] = mmul(fs[i-1], i);
		ifs[i] = mpow(fs[i], MOD-2);
	}
}

int cnk(int n, int k){
	if (n < k || n < 0 || k < 0) return 0;
	return mmul(fs[n], mmul(ifs[k], ifs[n-k]));
}

int cnkrep(int n, int k){
	return cnk(n + k - 1, k - 1);
}


public:
    int countseatnumb(int n, int k, int g) {
        vector<int> dyn(g+1);
        dyn[0] = 1;
        for (int i = 0; i < k; i++) {
        	vector<int> ndyn(g+1);
        	for (int j = 0; j <= g; j++) {
        		if (j > 0) madd(ndyn[j-1], mmul(j * (j-1), dyn[j]));
        		if (j < g) madd(ndyn[j+1], dyn[j]);
        		madd(ndyn[j], mmul(dyn[j], 2*j));
        	}
        	dyn = ndyn;
        }
        Precalc(2*n);
        int ans = 0;
        for (int i = 1; i <= g; i++) {
        	int cur = dyn[i];
        	cur = mmul(cur, fs[i-1]);
        	cur = mmul(cur, cnkrep(n - k - i + (n == k), i));
        	if (n != k)
	        	cur = mmul(cur, n);
        	madd(ans, cur);
        }
        return ans;
    }
};

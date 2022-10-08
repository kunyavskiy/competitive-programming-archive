//#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <cstdlib>
#include <cstdio>
#include <iterator>
#include <functional>
#include <bitset>
#define mp make_pair
#define pb push_back

//#define DEBUG

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

#if ( ( _WIN32 || __WIN32__ ) && __cplusplus < 201103L)
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "F"

#ifdef LOCAL
static struct __timestamper {
    string what;
    __timestamper(const char* what) : what(what){};
    __timestamper(const string& what) : what(what){};
	~__timestamper(){
        TIMESTAMPf("%s", what.data());
	}
} __TIMESTAMPER("end");
#else 
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;


const int MOD = 998244353;
const int ROOT = 3;

int mpow(int a, int b){
	if (!b) return 1;
	if (b & 1) return (mpow(a, b-1) * 1LL * a) % MOD;
	int temp = mpow(a, b/2);
	return (temp * 1LL * temp) % MOD;
}

bool checkRoot(int x){
	return mpow(x, (MOD - 1) / 7) != 1 && mpow(x, (MOD - 1) / 17) != 1 && mpow(x, (MOD - 1) / 2) != 1; 
}

const int MROOT = 19;
int roots[(1<<MROOT) + 10];
int brev[(1<<MROOT) + 10];


int bit_reverse(int x,int n){
	int res = 0;
	for (int i = 0; i < n; i++)
		res |= ((x >> i) & 1) << (n - i - 1);
	return res;	
}

void PreCalcRoots(){
	roots[0] = 1;
	assert((MOD-1) % MROOT);
	roots[1] = mpow(ROOT, (MOD-1) / (1<<MROOT));
	assert(mpow(roots[1],(1<<MROOT)/2) == MOD-1);
	for (int i = 2; i < (1<<MROOT); i++)
		roots[i] = (roots[i-1] * 1LL * roots[1]) % MOD;
	for (int i = 0; i < (1<<MROOT); i++)
		brev[i] = bit_reverse(i, MROOT);
}

inline void butterfly(int& a, int& b, int x){
	int temp = (a + x * 1LL* b) % MOD;
	b = ((a - x * 1LL * b) % MOD + MOD) % MOD;
	a = temp;
}

void eprint(vector<int> a){
	for (int i = 0; i < (int)a.size(); i++)
		eprintf("%d ", a[i]);
	eprintf("\n");	
}

void fft(vector<int>& a, bool inv){
	int n = __builtin_ctz(a.size());
	assert(n <= MROOT);
	assert((int)a.size() == (1<<n));
	for (int i = 0; i < (1<<n); i++){
	    int temp = brev[i] >> (MROOT - n);
		if (temp > i)
			swap(a[i], a[temp]);
	}	
	for (int step = 0; step < n; step++){
		int pos = 0;
		int dlt = inv ? -1 : 1;
		dlt *= 1<<(MROOT - step - 1);
	    for (int i = 0; i < (1<<n); i++){
	    	if ((i ^ (1<<step)) > i)  {
	    	  butterfly(a[i], a[i ^ (1<<step)], roots[pos]);
	    	}
      	    pos = (pos + dlt) & ((1<<MROOT)-1);
	    }
	}
}


vector<int> multiply_slow(vector<int> a, vector<int> b){
	vector<int> res(a.size()+b.size());
	for (int i = 0; i < (int)a.size(); i++)
		for (int j = 0; j < (int)b.size(); j++)
			res[i+j] = (res[i+j] + a[i] * 1LL * b[j]) % MOD;
	return res;
}

vector<int> multiply(vector<int> a, vector<int> b){
	#ifdef DEBUG
		vector<int> res_slow = multiply_slow(a, b);
	#endif
	int rsz = a.size() + b.size();
	int rsz2 = 1;
	while (rsz2 < rsz) rsz2 *= 2;
	a.resize(rsz2);
	b.resize(rsz2);
	fft(a, false);
	fft(b, false);
	for (int i = 0; i < (int)a.size(); i++)
		a[i] = (a[i] * 1LL * b[i]) % MOD;
	fft(a, true);
	int in = mpow(a.size(), MOD - 2);
	for (int i = 0; i < (int)a.size(); i++)
		a[i] = (a[i] * 1LL * in) % MOD;
	#ifdef DEBUG
	    while (res_slow.size() < a.size()) res_slow.pb(0);
		assert(a == res_slow);
	#endif
	return a;	
}

vector<int> inverse(vector<int> a){
	assert(a[0] != 0);
	vector<int> x(1, mpow(a[0], MOD - 2));

	while (x.size() < a.size()) {
		vector<int> sq = multiply(x, x);
		vector<int> nx = multiply(sq, vector<int>(a.begin(), a.begin() + min(a.size(), sq.size())));
		x.resize(sq.size());
		for (int i = 0; i < (int)x.size(); i++) {
			x[i] = (x[i] * 2LL - nx[i] + MOD) % MOD;
		}
		#ifdef DEBUG
			vector<int> temp = multiply(x, a);
			temp.resize(x.size());
			assert(temp[0] == 1);
			for (int i = 1; i < (int)temp.size(); i++)
				assert(temp[i] == 0);
		#endif
	}
	return x;
}

const int MAXN = 257000;

int facs[MAXN];
int ifacs[MAXN];

void PreCalcFacs(){
	facs[0] = ifacs[0] = 1;
	for (int i = 1; i < MAXN; i++){
		facs[i] = (facs[i-1] * 1LL * i) % MOD;
		ifacs[i] = mpow(facs[i], MOD - 2);
	}
}

int cnk(int n, int k){
	if (n < 0 || k < 0 || k > n) return false;
	int res = facs[n];
	res = (res * 1LL * ifacs[k]) % MOD;
	res = (res * 1LL * ifacs[n-k]) % MOD;
	return res;
}

ll get2(int x1, int x2, int t){
	int dlt = t - abs(x1 - x2);
	if (dlt < 0 || dlt % 2) return 0;
	return cnk(t, dlt / 2);
}

ll get1(int x1, int x2, int y1, int y2, int t){
	return (get2(x1 + y1, x2 + y2, t) * 1LL * get2(x1 - y1, x2 - y2, t)) % MOD;
}

int get(int x1, int x2, int y1, int y2, int t){
	return (get1(x1, x2, y1, y2, t) - 
	        get1(x1,-x2, y1, y2, t) - 
	        get1(x1, x2, y1,-y2, t) + 
	        get1(x1,-x2, y1,-y2, t) +
	        3LL * MOD) % MOD;
}



int main(){
	assert(checkRoot(ROOT));
	PreCalcRoots();
	PreCalcFacs();
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif
  
//    eprintf("%I64d\n", get1(0, 0, 1, 1, 6));
//    return 0;

    int x1, y1, x2, y2, t;
    scanf("%d %d %d %d %d",&x1,&y1,&x2,&y2, &t);

    vector<int> res(t+1);
    vector<int> res0(t+1);

    for (int i = 0; i <= t; i++){
    	res[i] = get(x1, x2, y1, y2, i);
    	res0[i] = get(x2, x2, y2, y2, i);
    }

    eprint(res);
    eprint(res0);

	res = multiply(res, inverse(res0));

	printf("%d\n", res[t]);
      
    return 0;
}
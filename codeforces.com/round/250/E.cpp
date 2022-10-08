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

#define TASKNAME "E"

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
const int ROOT = 2;

int mpow(int a, int b){
	if (!b) return 1;
	if (b & 1) return (mpow(a, b-1) * 1LL * a) % MOD;
	int temp = mpow(a, b/2);
	return (temp * 1LL * temp) % MOD;
}

bool checkRoot(int x){
	return mpow(x, (MOD - 1) / 7) != 1 && mpow(x, (MOD - 1) / 17) != 1 && mpow(x, (MOD - 1) / 2);
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
	roots[0] = 0;
	roots[1] = pow(ROOT, (MOD-1) / MROOT);
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
	    	if ((i ^ (1<<step)) > i) 
	    	  butterfly(a[i], a[i ^ (1<<step)], roots[pos]);
      	    pos = (pos + dlt) & ((1<<MROOT)-1);
	    }
	}
}

vector<int> multiply(vector<int> a, vector<int> b){
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
	return a;	
}

vector<int> solve(vector<int> v){
	if (v.size() == 1){
		assert(v[0] != 0);
		return vector<int>(1, mpow(v[0], MOD-2));
	}
	int size = v.size();
	vector<int> p1 = vector<int>(v.begin(), v.begin()+size / 2);
	vector<int> q1 = solve(p1);

	vector<int> pq1 = multiply(v, q1);
	pq1.resize(size);
	for (int i = 1; i < size; i++)
		pq1[i] = (MOD - pq1[i]) % MOD;
	pq1[0] = (1 + pq1[0]) % MOD;

	for (int i = 0; i < size / 2; i++)
		assert(pq1[i] == 0);
	vector<int> temp(pq1.begin()+size/2, pq1.end());
	vector<int> q2 = multiply(temp, q1);
	q1.insert(q1.end(), q2.begin(), q2.end());
	return q1;
}




int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif

  	assert(checkRoot(ROOT));
  	PreCalcRoots();

  	int n, m;
  	scanf("%d %d",&n,&m);
  	int m2 = 1;
  	while (m2 <= m) m2 *= 2;
  	vector<int> p(m2);
  	for (int i = 0; i < n; i++){
  		int x;
  		scanf("%d",&x);
  		if (x < m2)
  			p[x] = 1;
  	}
  	p[0] = 1;

      
  return 0;
}
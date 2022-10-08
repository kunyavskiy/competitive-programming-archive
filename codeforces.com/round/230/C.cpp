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

#define TASKNAME "C"

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

const int MOD = 1000000007;

struct Matrix {
	vector<vector<int> > v;
	vector<int>& operator[](int id){
		return v[id];
	}
	Matrix(int n, int m):v(n, vector<int>(m, 0)){
	}
};

Matrix operator*(Matrix a, Matrix b){
	assert(a.v[0].size() == b.v.size());
	Matrix res(a.v.size(), b.v[0].size());
	for (int i = 0; i < (int)a.v.size(); i++)
	for (int j = 0; j < (int)b.v[0].size(); j++)
	for (int k = 0; k < (int)a.v[0].size(); k++)
		res[i][j] = (res[i][j] + a[i][k] * 1LL * b[k][j]) % MOD;
	return res;
}

Matrix operator^(Matrix a, ll b){
	assert(a.v.size() == a.v[0].size());
	Matrix res(a.v.size(), a.v.size());
	for (int i = 0; i < (int)a.v.size(); i++)
		res[i][i] = 1;

	for (; b > 0; b >>= 1){
		if (b & 1) res = res * a;
		a = a * a;
	}

	return res;
}


int cnk[50][50];


int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif


  	cnk[0][0] = 1;
  	for (int i = 0; i < 50; i++)
  		for (int j = 0; j < 50; j++){
  			if (i) cnk[i][j] = (cnk[i][j] + cnk[i-1][j]) % MOD;
  			if (i && j) cnk[i][j] = (cnk[i][j] + cnk[i-1][j-1]) % MOD;
  		}

  	ll n; int k;
  	scanf(LLD"%d",&n,&k);

  	Matrix a(2 * k + 3, 2 * k + 3);
  	Matrix b(2 * k + 3, 1);

  	for (int i = 0; i < 2*k + 2; i++)
  		b[i][0] = 1;

  	for (int i = 0; i <= k; i++){
  		for (int j = 0; j <= i; j++){
  			a[i][j + k + 1] = cnk[i][j];
  			a[i + k + 1][j] = cnk[i][j];
  			a[i + k + 1][j + k + 1] = cnk[i][j];
  		}
  	}

  	b[2*k+2][0] = 1;
  	a[2*k+2] = a[2*k+1];
  	a[2*k+2][2*k+2] = 1;

/*	 for (int i = 0; i < n; i++){
	 	Matrix tmp = (a ^ i) * b;
	 	for (int j = 0; j <= 2*k + 2; j++)
	 		eprintf("%d ", tmp[j][0]);
	 	eprintf("\n");
	 }*/

	 b = (a ^ (n - 1)) * b;

	 printf("%d\n", b[2*k+2][0]);	
     return 0;         
}
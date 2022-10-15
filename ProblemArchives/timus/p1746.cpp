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

#define TASKNAME "1746"

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


struct Matrix {
  vector< vector<int> > v;
  Matrix(int n, int t){
    v.resize(n, vector<int>(n));
    for (int i = 0; i < n; i++)
      v[i][i] = t;
  }
  vector<int>& operator[](int x) { return v[x];}
  const vector<int>& operator[](int x) const { return v[x];}
  int size() const { return v.size();}
};

int MOD;

int mmul(int a, int b){
  return (a * 1LL * b) % MOD;
}

void madd(int& a, int b){
  if ((a += b) >= MOD) a -= MOD;
}

Matrix operator*(const Matrix& a, const Matrix& b){
  Matrix res(a.size(), 0);
  for (int i = 0; i < a.size(); i++)
    for (int j = 0; j < a.size(); j++)
      for (int k = 0; k < a.size(); k++)
        madd(res[i][j], mmul(a[i][k], b[k][j]));
  return res;
}

Matrix operator^(Matrix a, unsigned long long n) {
  Matrix res(a.size(), 1);
  while (n) {
    if (n & 1) res = res * a;
    a = a * a;
    n >>= 1;
  }
  return res;
}

int q;
int t[55][55];

int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif

  	int n,m,d;
  	scanf("%d %d %d %d",&n,&m,&d,&MOD);

  	Matrix a(n+1, 0);

  	for (int i = 0; i <= n; i++){
  		if (i != 0)
  			a[i][i-1] = i % MOD;
  		a[i][i] = mmul(i, m - 2);
  		if (i != n)
  			a[i][i+1] = mmul(n - i, m - 1);
  	}

  	a = a ^ d;

  	int q;
  	scanf("%d",&q);
  	for (int i = 0; i < q; i++)
  		for (int j = 0; j < n; j++)
  			scanf("%d",&t[i][j]);

	for (int i = 0; i < q; i++)
		for (int j = 0; j < q; j++){
			int cnt = 0;
			for (int k = 0; k < n; k++)
				cnt += (t[i][k] != t[j][k]);
			printf("%d%c", a[cnt][0] % MOD, " \n"[j==q-1]);
		}

      
    return 0;
}
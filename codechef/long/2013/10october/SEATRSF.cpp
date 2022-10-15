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

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "SEATRSF"

#ifdef LOCAL
static struct __timestamper {
	~__timestamper(){
		TIMESTAMP(end);
	}
} __TIMESTAMPER;
#endif

typedef long long ll;
typedef long double ld;

const int MOD = 1000000007;

int norm(int a){
	return (a * 1LL + MOD) % MOD;
}

int mult(int a,int b){
	return (norm(a) * 1LL* norm(b)) % MOD;
}

int pow(int a,int b){
	if (!b) return 1;
	if (b & 1) return mult(pow(a, b-1), a);
	return pow(mult(a,a), b/2);
}



void solve(){
	int n,m,q;
	scanf("%d %d %d %*d",&n,&m,&q);
	if (q >= m) {
		printf("0\n");
		return;
	}               

/*	vector<int> dp(q+1);
	dp[0] = 1;
	int sum = 1;

    for (int i = 1; i <= q; i++){
    	dp[i] = (pow(i+1, n) - pow(i, n) + MOD) % MOD;
    	dp[i] = (dp[i] - sum + MOD) % MOD;
    	sum = (sum + dp[i]) % MOD;        	
    	assert(sum == (pow(i+1, n) - pow(i, n) + MOD) % MOD);
    }*/

    ll ans = 0;

    if (q == 1)
    	ans = (pow(2, n) - 2 + MOD) % MOD;
    else
    	ans = (pow(q+1, n) - 2LL * pow(q,n) + pow(q-1, n) + 2*MOD) % MOD;

//    eprintf("%d %d %d\n", n, m, q);
//    assert(ans == dp[q]);

//    ll ans = (pow(q+1, n) - pow(q-1, n) + MOD) % MOD;

	printf("%d\n", int((ans * 1LL * (m-q)) % MOD));
}

int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif
	int t;
	scanf("%d",&t);
	while (t-->0)
		solve();      
  return 0;
}
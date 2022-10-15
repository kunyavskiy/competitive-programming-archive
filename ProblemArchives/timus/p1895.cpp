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
#define prev prev_i_love_std

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

#define TASKNAME "1895"

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



#ifndef LOCAL
#undef assert
#define assert(x) if (!(x)) { int res = 1 / 0; printf("%d\n", res);}
#endif

int dp[1010][55][55];
int prev[1010][55][55][3];


int t[55];
int x, k;
int ans[2][55];
int n;

void relax(int& a, int* prev, int b, int i, int j, int k){
	if (a > b){
		a = b;
		prev[0] = i;
		prev[1] = j;
		prev[2] = k;
	}
}


void restore(int pos, int ptr1, int ptr2){
	if (pos == 0) return;
	if (dp[pos-1][ptr1][ptr2] == dp[pos][ptr1][ptr2]){
		restore(pos-1, ptr1, ptr2);
		return;
	}
	assert(prev[pos][ptr1][ptr2][0] != -1);
	restore(prev[pos][ptr1][ptr2][0], prev[pos][ptr1][ptr2][1],prev[pos][ptr1][ptr2][2]);
	for (int i = prev[pos][ptr1][ptr2][1]; i < ptr1; i++)
		ans[0][i] = pos-1;
	for (int i = prev[pos][ptr1][ptr2][2]; i < ptr2; i++)
		ans[1][i] = pos-1;
}

int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif

    scanf("%d%d",&x,&k);
    scanf("%d",&n);

    for (int i = 0; i < n; i++){
    	scanf("%d",&t[i]);
    }

    memset(dp, 1, sizeof(dp));
    memset(prev, -1, sizeof(prev));
    dp[0][0][0] = 0;

    for (int i = 0; i <= t[n-1]; i++)
    	for (int j = 0; j <= n; j++)	
    		for (int k = 0; k <= j; k++) {
    			if (dp[i][j][k] > 10000) continue;
    			if (k < n && i >= t[k]) continue;
    			relax(dp[i+1][j][k], prev[i+1][j][k],  dp[i][j][k],i,j,k);
    			for (int nj = j; nj <= n; nj++) {
    				for (int nk = k; nk <= j && (nk - k + nj - j) <= ::k; nk++){
    					relax(dp[i+1][nj][nk], prev[i+1][nj][nk], dp[i][j][k]+1, i, j, k);
    				}
    				if (t[nj] - x > i) break;
    			}
    		}
    if (dp[t[n-1]+1][n][n] > 10000){
    	printf("-1\n");
    } else {
    	printf("%d\n", dp[t[n-1]+1][n][n]);
    	restore(t[n-1]+1,n,n);
    	vector<int> cnt(1010);
    	for (int i = 0; i < n; i++) {
    		printf("%d %d\n", ans[0][i], ans[1][i]);
    		assert(t[i] - x <= ans[0][i]);
    		assert(ans[0][i] < ans[1][i]);
    		assert(ans[1][i] < t[i]);
    		assert(cnt[ans[0][i]]++ <= k);
    		assert(cnt[ans[1][i]]++ <= k);
    	}
    }
      
    return 0;
}
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

#define TASKNAME "B"

typedef long long ll;
typedef long double ld;

const int MAXN = 1<<16;

int cnt[2][MAXN+10];
ll res[MAXN+10];


int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif
    int n,m,k;
    scanf("%d %d %d",&n,&m,&k);

    for (int i = 0; i < n; i++){
    	int k;
    	scanf("%d",&k);
    	cnt[0][k]++;
    }

    for (int i = 0; i < m; i++){
    	int k;
    	scanf("%d",&k);
    	cnt[1][k]++;
    }

    for (int it = 0; it < 2; it++){
    	for (int i = 0; i < MAXN; i++)
    		for (int j = (i|(i+1)); j < MAXN; j = (i | (j+1))){
    			assert((i & j) == i);
    			cnt[it][i] += cnt[it][j];
    		}
    }

    for (int i = 0; i < MAXN; i++)
    	res[i] = cnt[0][i] * 1LL * cnt[1][i];

    for (int i = MAXN; i >= 0; i--){
    	for (int j = (i|(i+1)); j < MAXN; j = (i | (j+1)))
    		res[i] -= res[j];
    }


    for (int i = 0; i < k; i++){
    	int x;
    	scanf("%d",&x);
    	printf(LLD"\n",res[x]);
    }


      
    TIMESTAMP(end);
    return 0;
}
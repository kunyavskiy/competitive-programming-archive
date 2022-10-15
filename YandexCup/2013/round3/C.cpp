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

#define TASKNAME "C"

typedef long long ll;
typedef long double ld;

const int MOD = 1000200013;

int c[1010][1010];

pair<int,int> a[15];

int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif
  	c[0][0] = 1;
  	for (int i = 0; i < 1010; i++)
  		for (int j = 0; j < 1010; j++){
  			if (i) c[i][j] += c[i-1][j];
  			if (i && j) c[i][j] += c[i-1][j-1];
  			c[i][j] %= MOD;
  		}

  	int n,k;
  	scanf("%d %d",&n,&k);

  	for (int i = 0; i < k; i++)
  		scanf("%d",&a[i].first), a[i].second = i;

  	sort(a,a+k);

  	int ans = 0;

  	do {       	
  		int n1 = n;
  		for (int i = 1; i < k; i++)
  			n1 -= max(0, a[i].first - a[i-1].first);
  		n1 = max(n1, 0);
  		ans = (ans + c[n1][k]) % MOD;
  	} while (next_permutation(a,a+k));
      

    printf("%d\n",ans);

    TIMESTAMP(end);
    return 0;
}
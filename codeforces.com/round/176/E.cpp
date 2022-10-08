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

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "E"

typedef long long ll;
typedef long double ld;


int START = clock();

bool can[1000100];
bool need[1000100];
vector<int> ans;

int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif

  	int n,m;
  	scanf("%d %d",&n,&m);
  	int m1 = 1;
  	for (int i = 0; i < n;i++){
  		int t;
  		scanf("%d",&t);
  		need[t] = 1;
  		if (i < 2) m1 = min(m1 * 1LL * t, m*1LL);
  	}

  	can[0] = true;

  	int cnt = 0;

  	for (int i = 1; i <= m && cnt < n; i++){
  		if (i % 100){
  			if ((clock() - START) > 7.5 * CLOCKS_PER_SEC)
  				break;

  		}

  		if (!need[i] || can[i]) continue;

  		ans.pb(i);
  		for (int j = i; j <= m; j++){
  			cnt += !can[j] && can[j-i];
  			can[j] |= can[j-i];
			if (!need[j] && can[j]){
	  			printf("NO\n");
  				return 0;
  			}
  		}
  		if (i == 1)
  			m = min(m, m1);
  	}


  	printf("YES\n");
  	printf("%d\n",(int)ans.size());
  	for (int i = 0; i < (int)ans.size(); i++)
  		printf("%d%c",ans[i]," \n"[i==n-1]);
      
    TIMESTAMP(end);
    return 0;
}
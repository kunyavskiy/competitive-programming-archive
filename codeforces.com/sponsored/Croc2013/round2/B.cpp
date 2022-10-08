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

#define TASKNAME "B"

typedef long long ll;
typedef long double ld;

int mask[15][15];
int curm[15][15];
int n,m,k;
int ans;

void dfs(int x,int y){
	if (x == n+1){
		ans++;
		return;
	}
	if (y == m+1){                                      		
		dfs(x+1,1);
		return;
	}
	curm[x][y] = curm[x][y-1] & curm[x-1][y];

	for (int i = 0; i < k; i++)
		if ((mask[x][y] & (1<<i)) && (curm[x][y] & (1<<i))){
			curm[x][y] &= ~(1<<i);
			dfs(x,y+1);
			curm[x][y] |= (1<<i);
		}
}


int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif
  	scanf("%d %d %d",&n,&m,&k);

  	if (n + m - 1 > k){
  		printf("0\n");
  		return 0;
  	}

  	memset(mask,-1,sizeof(mask));
  	for (int i = 1; i <= n; i++)
  		for (int j = 1; j <= m; j++){
  			int x;
  			scanf("%d",&x);
  			if (x){
  				--x;
  				mask[i][j] = (1<<x);
  				for (int i1 = 1; i1 <=i; i1++)
  					for (int j1 = 1; j1 <=j; j1++)
  						if (i1 != i || j1 != j)
								mask[i1][j1] &= ~(1<<x);
  						
  			}
  		}

/*	for (int i = 1 ; i <= n; i++)
		for (int j = 1; j <= m; j++)
			eprintf("%d%c",mask[i][j]," \n"[j==m-1]);*/
                                 

    for (int i = 0; i <= n; i++)
    	for (int j = 0; j <= m; j++)
    		curm[i][j] = (1<<k)-1;
    dfs(1,1);

    printf("%d\n",ans);
      
    TIMESTAMP(end);
    return 0;
}
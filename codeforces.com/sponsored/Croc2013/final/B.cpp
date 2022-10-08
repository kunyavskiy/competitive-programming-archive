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

const int MAXN = 1100000;

int n,m;
ll need[35];
ll have[35];


int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif

  	scanf("%d %d",&n,&m);
  	for (int i = 0; i <n ; i++){
  		int a;
  		scanf("%d",&a);
  		for (int j = 0; j <= 30; j++)
  			if (a & (1<<j))
  				have[j]++;
  	}

  	for (int i = 0; i < m; i++){
  		int b;
  		scanf("%d",&b);
  		need[b]++;
  	}

  	ll ans = 0;

  	for (int i = 0; i <= 30; i++){
  		while (need[i] > 0){
  			if (have[i]){
  				ll temp = min(need[i],have[i]);
  				ans += temp;
  				need[i] -= temp;
  				have[i] -= temp;
				continue;
  			}
  			bool any = 0;
  			for (int j = i+1; j <= 30; j++){
  				if (have[j]){
  					ll divide = (need[i] + (1LL<<(j-i))-1)/(1LL<<(j-i));
  					divide = min(divide,have[j]);
  					any = true;
  					have[j-1] += 2*divide;
  					have[j] -= divide;
  					break;
  				}
			}
		    if (!any) break;	
  		}
  	}
  		
	printf(LLD"\n",ans);	
      
    TIMESTAMP(end);
    return 0;
}
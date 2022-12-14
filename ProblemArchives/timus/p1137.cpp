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

#define TASKNAME "1137"

typedef long long ll;
typedef long double ld;

vector<int> g[11000];
int ptr[11000];
vector<int> res;


void dfs(int v){
	eprintf("%d \n",v);
	while (ptr[v] < (int)g[v].size()){
		dfs(g[v][ptr[v]++]);
	}
	res.pb(v);
}


int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif

  	int n;
  	scanf("%d",&n);
  	for (int i = 0; i < n; i++){
  		int m;
  		scanf("%d",&m);
  		int last;
  		scanf("%d",&last);
  		for (int j = 1; j <= m; j++){
  			int nlast;
  			scanf("%d",&nlast);
  			g[last].pb(nlast);
  			last = nlast;
  		}
  	}        
  	for (int i = 0; i <= 10000; i++)
  		if (g[i].size()){
  			dfs(i);
  			break;
  		}

    reverse(res.begin(),res.end());
    printf("%d\n",(int)res.size()-1);
    for (int i = 0; i < (int)res.size(); i++)
    	printf("%d%c",res[i]," \n"[i==(int)res.size()-1]);
      
    TIMESTAMP(end);
    return 0;
}
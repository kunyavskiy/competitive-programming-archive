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

#define TASKNAME "E"

typedef long long ll;
typedef long double ld;

const int MAXN = 110000;

set<int> g[MAXN];
set<pair<int,int> > d;

int used[MAXN], usedptr;


int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif

  	int n,m;
  	scanf("%d %d",&n,&m);
/*  	for (int i = 0; i < m; i++){
  		int a,b;
  		scanf("%d %d",&a,&b);
  		--a,--b;
  		g[a].insert(b);
  		g[b].insert(a);
  	}

  	for (int i = 0; i < n; i++)
  		d.insert(mp(g[i].size(),i));

  	ll ans = 0;

  	for (int it = 0; it < n; it++){
  		int i = d.begin()->second;
  		d.erase(d.begin());
  		vector<int> v(g[i].begin(),g[i].end());
  		++usedptr;
  		int cnt = v.size();
  		for (int j = 0; j < (int)v.size(); j++)
  			for (int k = 0; k < (int)v.size() && used[v[j]] != usedptr; k++){
  				if (g[v[j]].count(v[k])){
  					used[v[j]] = used[v[k]] = usedptr;
  					cnt -= 2;
  				}
  			}
  		eprintf("%d\n",cnt);
  		ans += cnt / 2;
  		for (int j = 0; j < (int)v.size(); j++){
  			d.erase(mp(g[v[j]].size(), v[j]));
  			g[v[j]].erase(i);
  			d.insert(mp(g[v[j]].size(), v[j]));
  		}	
  	}

  	printf(LLD"\n",ans);*/

  	printf("%d\n",n + n/3 - m);
      
    TIMESTAMP(end);
    return 0;
}
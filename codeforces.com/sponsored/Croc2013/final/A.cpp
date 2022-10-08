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

#define TASKNAME "A"

typedef long long ll;
typedef long double ld;

const int MAXN   = 1000010;
const int MAXLEN = 5000010;


char buf[MAXLEN+MAXN];int bufptr;

char* s[MAXN];
int sz[MAXN];
int n,r,c;
int next[MAXN];
vector<int> g[MAXN];
int st[MAXN];
int lf,lfr;

void dfs(int v,int pos){
	if (pos){
		int rg = (pos < r)?st[0]:st[pos-r];
//    	eprintf("%d %d [pos = %d]\n",v,rg,pos);

		if (rg - v > lfr - lf){
			lfr = rg;
			lf = v;
		}
	}
	st[pos] = v;
	for (int i = 0; i < (int)g[v].size(); i++)
		dfs(g[v][i],pos+1);
}               

int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif
    scanf("%d %d %d",&n,&r,&c);
    for (int i = 0; i < n; i++){
    	scanf("%s",buf+bufptr);
    	s[i] = buf+bufptr;
    	sz[i] = strlen(s[i])+1;
    	bufptr += sz[i];
    }
    c++;

    {

    for (int lf = 0,rg = 0,tot = 0; lf < n; lf++){
    	while (rg < n && tot+sz[rg] <= c)
    		tot += sz[rg++];
    	next[lf] = rg;
    	tot -= sz[lf];
//    	eprintf("%d%c",next[lf]," \n"[lf == n-1]);
    }

    }

    for (int i = 0; i < n; i++)
    	if (i != next[i])
	    	g[next[i]].pb(i);
	next[n] = n;

	lfr = -1,lf = 0;

	for (int i = 0; i <= n; i++)
		if (next[i] == next[next[i]])
			dfs(i,0);

//	eprintf("%d %d\n",lf,lfr);

	for (int i = ::lf; r > 0 && i < n; r--){
		bool any = false;
		int cur = 0;
		while (cur + sz[i] <= c && i < n){
			cur += sz[i];
			if (any)
				printf(" ");
			any = true;
			printf("%s",s[i]);
			i++;
		}
		printf("\n");
//		eprintf("%d %d\n",i,r);
	} 
      
    TIMESTAMP(end);
    return 0;
}
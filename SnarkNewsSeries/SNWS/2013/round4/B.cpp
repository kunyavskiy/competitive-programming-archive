#include <iostream>
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

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "B"

typedef long long ll;
typedef long double ld;

const int MAXN = 310000;

vector<int> g[MAXN];
vector<int> c[MAXN];

int lx,rx;
int n,m;

int val[MAXN];
int color[MAXN];

void intersec(int l,int r){
//	cerr <<"!"<<l<< " "<<r<<endl;
	lx = max(lx,l);
	rx = min(rx,r);
	if (lx > rx){
		printf("0\n");
		exit(0);
	}
}

void dfs(int v,int col,int cur){            
	if (color[v] == col){
		if (val[v] != cur){
			printf("0\n");
			exit(0);
		}
		return;
	}
	if (color[v] == 1 - col){
		return;
	}
	color[v] = col;
	val[v] = cur;
	if (col == 0) intersec(1-cur,n-cur);
	if (col == 1) intersec(cur-n,cur-1);
    for (int i = 0; i < (int)g[v].size(); i++)
    	dfs(g[v][i],1-col, c[v][i] - cur);	
}




int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif

  	scanf("%d %d",&n,&m);

  	lx = 1, rx = n;

  	memset(color,-1,sizeof(color));

  	for (int i = 0; i < m; i++){
  		int a,b,s;
  		scanf("%d %d %d",&a,&b,&s);
  		--a,--b;
  		g[a].pb(b);
  		g[b].pb(a);
  		c[a].pb(s);
  		c[b].pb(s);
  	}

  	dfs(0,0,0);


  	for (int i = 0; i < n; i++)
  		for (int j = 0; j < (int)g[i].size(); j++)
  			if (color[g[i][j]] != color[i]){
  				if (val[i] + val[g[i][j]] != c[i][j]){
  					printf("0\n");
  					return 0;
  				}   					
  			}
  			else {
  				if (abs(val[i] + val[g[i][j]]) % 2 != c[i][j] % 2){
  					printf("0\n");
  					return 0;
  				}
  				if (color[i] == 0)
	 				intersec((c[i][j] - val[i] - val[g[i][j]])/2,(c[i][j] - val[i] - val[g[i][j]])/2);
	 			else
	 				intersec(-(c[i][j] - val[i] - val[g[i][j]])/2,-(c[i][j] - val[i] - val[g[i][j]])/2);
  			}


	bitset<MAXN> can;
	bitset<MAXN> Ro,Re;
	for (int i = 0; i < n; i++){
		if (color[i] == 1){
			assert(val[i] >= 0 && val[i] <= 2*n);
			if (val[i] % 2 == 0)
				Re[val[i]/2] = 1;
			else
				Ro[val[i]/2] = 1;
		}
	}

	for (int i = lx; i <= rx; i++)
		can[i] = 1;


	for (int i = 0; i < n; i++){
		if (color[i] == 0){
			if (val[i] % 2 == 0) {
				if (val[i] > 0)
					can &= ~(Re >> (val[i]/2));
				else
					can &= ~(Re << (-val[i]/2));
			}
			else {
				if (val[i] > 0)
					can &= ~(Ro >> ((val[i]+1)/2));
				else 
					can &= ~(Ro << ((-val[i]+1)/2));
			}
		}
	}

	vector<pair<int,int> > used;
	for (int i = 0; i < n; i++)
		used.pb(mp(color[i],val[i]));
	sort(used.begin(),used.end());

	if (unique(used.begin(),used.end()) != used.end()){
		printf("0\n");
		return 0;
	}


	printf("%d\n",can.count());
	if (can.count()){
     	int X = -1;
     	for (int i = 1; i <= n; i++)
     		if (can[i]){
     			X = i;
     			break;
     		}
     	assert(X != -1);

     	for (int i = 0; i < n; i++)
     		if (color[i] == 0)
     			printf("%d ",X + val[i]);
     		else
     			printf("%d ",val[i] - X);

		for (int i = 0; i < n; i++){
			assert(color[i] != -1);
			for (int j = 0; j < (int)g[i].size(); j++)
				assert(((color[i] == 0)?(X+val[i]):(val[i]-X)) + ((color[g[i][j]] == 0)?(X+val[g[i][j]]):(val[g[i][j]]-X)) == c[i][j]);
		}
	}

      
    return 0;
}
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

namespace dsu{
	int p[310];
	int sum[310];

	void init(int n,int* val){
		for (int i = 0; i < n; i++)
			p[i] = i, sum[i] = val[i];
	}

	int get(int v){
	    if (v == p[v]) return v;
	    return p[v] = get(p[v]);
	}

	bool join(int a,int b){
		a = get(a);
		b = get(b);
		if (a == b) return false;
		p[a] = b;
		sum[b] += sum[a];
		return true;
	}
}   	

int val[310];
int nval[310];
int cap;

vector<int> g[310];
vector<int> ansa,ansb,answ;


void norm(int v,int toval,int p = -1){
	eprintf("%d %d\n",v,toval);
	for (int i = 0; i < (int)g[v].size(); i++){
		if (g[v][i] == p) continue;
		if (val[v] < toval) {
			norm(g[v][i], cap, v);
			int temp = min(val[g[v][i]], toval - val[v]);
			ansa.pb(g[v][i]);
			ansb.pb(v);
			answ.pb(temp);
			val[g[v][i]] -= temp;
			val[v] += temp;
		}
		if (val[v] > toval) {
			norm(g[v][i], 0, v);
			int temp = min(cap - val[g[v][i]], val[v] - toval);
			ansa.pb(v);
			ansb.pb(g[v][i]);
			answ.pb(temp);
			val[g[v][i]] += temp;
			val[v] -= temp;
		}
	}
}


int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif
  	
    int n,e;
    scanf("%d %d %d",&n,&cap,&e);

    for (int i = 0; i < n; i++){
    	int a;
    	scanf("%d",&a);
    	val[i] += a;
    }

    for (int i = 0; i < n; i++){
    	int a;
    	scanf("%d",&a);
    	nval[i] = a;
    	val[i] -= a;
    }

    dsu::init(n,val);

    for (int i = 0; i < n; i++)
    	val[i] += nval[i];

    for (int i = 0; i < e; i++){
    	int a,b;
    	scanf("%d %d",&a,&b);
    	--a,--b;
    	if (dsu::join(a,b))
    		g[a].pb(b),g[b].pb(a);
    }

    for (int i = 0; i < n; i++){
    	if (dsu::sum[dsu::get(i)]){
    		printf("NO\n");
    		return 0;
    	}
    }

    while (true){
    	int good = -1;
    	for (int j = 0; j < n; j++)
    		if (g[j].size() == 1){
    			good = j;
    			break;
    		}
    	if (good == -1)
    		break;
		norm(good,nval[good]);
		assert(val[good] == nval[good]);
		int to = g[good][0];
		for (int j = 0; j < (int)g[to].size(); j++)
			if (g[to][j] == good){
				swap(g[to][j],g[to].back());
				g[to].pop_back();
				break;
			}
		g[good].clear();
    }

    printf("%d\n", (int)ansa.size());
    for (int i = 0; i < (int)ansa.size(); i++)
    	printf("%d %d %d\n",ansa[i]+1,ansb[i]+1,answ[i]);

      
    TIMESTAMP(end);
    return 0;
}
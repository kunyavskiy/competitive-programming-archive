#include <iostream>
#include <cassert>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <deque>
#include <stack>
#include <algorithm>
#include <memory.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iterator>

#define mp make_pair
#define pb push_back

#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;


const int MAXN = 251;

vector<int> dp[MAXN][MAXN];

vector<int> g[MAXN];
vector<int> c[MAXN];
int p[MAXN];

vector<int> ans;

int calc(int v,int k,int p,int last){
	if (last == -1 || k == 0)
		return 0;
	if (dp[v][k].size() == 0)
		dp[v][k].resize(g[v].size()+1,-1);
	int& ans = dp[v][k][last];
	if (ans != -1)
		return ans;
	ans = -(1<<30);
	if (last == (int)g[v].size())
		return ans = max(calc(v,k-1,p,last-1) + ::p[v],calc(v,k,p,last-1));

	if (g[v][last] == p){
		return ans = calc(v,k,p,last-1);
	}
	
	for (int i = 0; i <= k; i++)
		ans = max(ans, min(c[v][last],calc(g[v][last],i,v,g[g[v][last]].size())) + calc(v,k-i,p,last-1));
	return ans;
}


void get(int v,int k,int p,int last){
	if (last == -1 || k == 0)
		return;
	if (last == (int)g[v].size()){
		if (calc(v,k,p,last) == calc(v,k-1,p,last-1) + ::p[v]){
			ans.pb(v);
			get(v,k-1,p,last-1);
			return;
		}
		--last;
	}

	if (g[v][last] == p){
		get(v,k,p,last-1);
		return;
	}
	for (int i = 0; i <= k; i++)
		if (calc(v,k,p,last) == min(c[v][last],calc(g[v][last],i,v,g[g[v][last]].size())) + calc(v,k-i,p,last-1)){
		    get(g[v][last],i,v,g[g[v][last]].size());
		    get(v,k-i,p,last-1);
		    return;
		}
	assert(false);		
}

int main(){
    #ifdef LOCAL
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif

    int n,k;
    scanf("%d %d",&n,&k);
    for (int i = 0; i < n; i++){
		scanf("%d",&p[i]);
    }
    for (int i = 0; i < n-1; i++){
    	int a,b,c;
    	scanf("%d %d %d",&a,&b,&c);
    	--a,--b;
    	g[a].pb(b);
    	g[b].pb(a);
    	::c[a].pb(c);
    	::c[b].pb(c);
    }

    cout << calc(0,k,-1,(int)g[0].size()) << endl;
    get(0,k,-1,(int)g[0].size());
    cout << ans.size() << endl;
    sort(ans.begin(),ans.end());
    for (int i = 0; i < (int)ans.size(); i++)
    	cout << ans[i]+1 << " ";
    cout << endl;
    return 0;
} 
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <queue>
#include <memory.h>
#include <stack>
#define mp make_pair
#define pb push_back                     
#define setval(a,v) memset(a,v,sizeof(a))

#if ( _WIN32 || __WIN32__ )
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

using namespace std;

typedef long long int64;
typedef long double ld;


const int MAXN = 2100;
const int MAXM = 1001000;

vector<pair<int,int> > g[MAXN];
int used[MAXM],uit;
int vused[MAXN],vuit;
int n,m;


void dfs(int v,vector<int>& ans){
	vused[v] = vuit;
	for (int i=0,sz=g[v].size();i<sz;i++)
		if (vused[g[v][i].first]!=vuit && used[g[v][i].second] != uit){
			ans.pb(g[v][i].second+1);
			used[g[v][i].second] = uit;
			dfs(g[v][i].first,ans);
		}
}



int main(){
	int start = clock();
  #ifdef LOCAL
    freopen("information.in","r",stdin);
    freopen("information.out","w",stdout);
  #endif
	scanf("%d %d",&n,&m);
	for (int i=0;i<m;i++){
		int a,b;
		scanf("%d %d",&a,&b);
		--a,--b;
		g[a].pb(mp(b,i));
//		num[a].pb(i);
	}
	vector<int> ans1,ans2;
	
	for (;clock() - start < 1.5 * CLOCKS_PER_SEC;){
		for (int i=0;i<n;i++)
			random_shuffle(g[i].begin(),g[i].end());	
		ans1.clear(),ans2.clear();
		vuit++,uit++;
		dfs(0,ans1);
		vuit++;
		dfs(0,ans2);
		if (ans1.size() == n-1 && ans2.size() == n-1){
			for (int i=0;i<n-1;i++)
				printf("%d ",ans1[i]);
			printf("\n");
			for (int i=0;i<n-1;i++)
				printf("%d ",ans2[i]);
			printf("\n");			
			return 0;	
		}
	}
//	assert(false);
	cout << "NONE" << endl;
	return 0;
}
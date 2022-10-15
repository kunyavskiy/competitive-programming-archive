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
#define int64 long long
#define ld long double  
#define setval(a,v) memset(a,v,sizeof(a))
using namespace std;

vector<int> g[310];
int mt[310];
bool used[310];
int n,m;
vector<int> ans;

bool kunn(int v){
	if (used[v])
		return false;
	used[v]=true;
	for (int i=0;i<g[v].size();i++){
		int to=g[v][i];
		if (mt[to]==-1 || kunn(mt[to])){
			mt[to]=v;
			return true;
		}
	}
	return false;
}

void check(int ANS){
	vector<int> mot;
	for (int i=0;i<ans.size();i++)
		for (int j=0;j<g[ans[i]].size();j++)
			mot.pb(g[ans[i]][j]);
	sort(mot.begin(),mot.end());
	mot.erase(unique(mot.begin(),mot.end()),mot.end());
	assert(int(ans.size())-int(mot.size()) == ANS);
}

void dfs(int v){
	if (used[v])
		return;
	used[v]=true;
	for (int i=0;i<g[v].size();i++){
		assert(mt[g[v][i]]!=-1);
		dfs(mt[g[v][i]]);
	}
		
}




int main()
{                        
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	scanf("%d %d",&n,&m);
	for (int i=0;i<n;i++){
		int cnt=0;
		scanf("%d",&cnt);
		g[i].resize(cnt);
		for (int j=0;j<cnt;j++){		
			scanf("%d",&g[i][j]);
			--g[i][j];
		}
	}
	memset(mt,-1,sizeof(mt));
	int mtsize=0;
	for (int i=0;i<n;i++){
		memset(used,0,sizeof(used));
		mtsize+=kunn(i);
	}
	
	memset(used,false,sizeof(used));
	
	for (int i=0;i<n;i++){
		if (used[i]) continue;
		bool q=true;
		for (int j=0;j<m;j++)
			if (mt[j]==i)
				q=false;
		if (q)
			dfs(i);		
	}	

	for (int i=0;i<n;i++)
		if (used[i])
			ans.pb(i);	
	
	check(n-mtsize);
	cout<<ans.size()<<endl;
	for (int i=0;i<ans.size();i++)
		printf("%d ",ans[i]+1);
	printf("\n");
    return 0;
}
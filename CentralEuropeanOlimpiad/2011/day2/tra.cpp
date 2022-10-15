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

const int MAXN = 310000;

vector<int> g[MAXN];
int n,m;
int x[MAXN];
int y[MAXN];
int A,B;

vector<int> por;

bool cmp(int a,int b){
	if (x[a] != x[b])
		return x[a] < x[b];
	return y[a] > y[b];
}

int used[MAXN],usedit;

int calc(int v){
	if (used[v] == usedit)
		return 0;
	used[v] = usedit;
	int ans = (x[v] == A);
	for (int i=0;i<g[v].size();i++)
		ans += calc(g[v][i]);
	return ans;
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	scanf("%d %d %d %d",&n,&m,&A,&B);
	for (int i=0;i<n;i++)
		scanf("%d %d",&x[i],&y[i]);
	
	for (int i=0;i<m;i++){
		int a,b,t;
		scanf("%d %d %d",&a,&b,&t);
		--a,--b;
		g[a].pb(b);
		if (t == 2)
			g[b].pb(a);			
	}
	
	for (int i=0;i<n;i++)
		por.pb(i);
		
	sort(por.begin(),por.end(),cmp);
	
	
	
	for (int i=0;i<n;i++){
	//	cerr << por[i] <<" " <<x[por[i]] << endl;
		if (x[por[i]] != 0)
			break;
		++usedit;
		printf("%d\n",calc(por[i]));
	}
	
	
	return 0;
}
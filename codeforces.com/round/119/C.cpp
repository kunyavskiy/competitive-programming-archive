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

typedef long long ll;
typedef long double ld;

const int MAXN = 110000;

vector<int> g[MAXN];

bool good[MAXN];

int d[MAXN];
bool used[MAXN];
int n,s,t,m,k;

void bfs(){
	queue<int> q;
	memset(d,63,sizeof(d));

	for (int i = 0; i < n; i++)
		if (good[i]){
			d[i] = 0;
			q.push(i);
		}

	while (!q.empty()){
		int v = q.front();
		q.pop();

		for (int i = 0; i  < (int)g[v].size(); i++)
			if (d[g[v][i]] > d[v] + 1){
				d[g[v][i]] = d[v] + 1;
				q.push(i);
			}
	}

}

bool dfs(int v,int q,int cnt){
//	cerr << v <<" "<<q<<" "<<cnt << " "<<d[v] << endl;
	if (v == t)
		return true;

	if (q - cnt < d[v])	
		return false;

	cnt = d[v];

	assert(cnt <= d[v]);

	if (used[v])
		return false;

	used[v] = true;

	for (int i = 0; i < (int)g[v].size(); i++)
		if (dfs(g[v][i],q,cnt+1))
			return true;

    return false;		
}

bool check(int q){
	memset(used,0,sizeof(used));
	return dfs(s,q,0);
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  scanf("%d %d %d",&n,&m,&k);

  for (int i = 0; i < k; i++){
  	int a;
  	scanf("%d",&a);
  	--a;
  	good[a] = true;
  }

  for (int i = 0; i < m; i++){
  	int a,b;
  	scanf("%d %d",&a,&b);
  	--a,--b;
  	g[a].pb(b);
  	g[b].pb(a);
  }

  scanf("%d %d",&s,&t);
  --s,--t;

  good[s] = good[t] = true;

  bfs();


  int l = 0, r = n;
  
  if (!check(r)){
    printf("-1\n");
  	return 0;
  }
                      

  for (;r-l > 1;){
  	int m = (l+r)/2;
  	if (check(m))
  		r = m;
  	else
  		l = m;
  }

  cout << r << endl;

  return 0;
}
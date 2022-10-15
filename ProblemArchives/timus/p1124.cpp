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

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "1124"

typedef long long ll;
typedef long double ld;

vector<int> g[510];
bool used[510];


void dfs(int v){
	used[v] = true;
	for (int i = 0; i < (int)g[v].size(); i++)
		if (!used[g[v][i]])
			dfs(g[v][i]);
}

int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif
  	int m,n;
  	scanf("%d %d",&m,&n);


  	int res = n*m-1;

  	for (int i = 0; i < m; i++)
  		for (int j = 0; j < n; j++){
  			int a;
  			scanf("%d",&a);
  			if (a-1 == i)
  				res--;
  			else {
  				g[a-1].pb(i);
  				g[i].pb(a-1);
  			}
  		}

  	for (int i = 0; i < m; i++)	
  		if (!used[i] && g[i].size())
	  		dfs(i), res++;

	cout << max(res,0) << endl;
      
    return 0;
}
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

#define TASKNAME "1218"

typedef long long ll;
typedef long double ld;


bool used[210];

char name[210][210];
int a[210];
int b[210];
int c[210];
int n;           

int dfs(int v){
	if (used[v]) return 0;
	used[v] = 1;
    int ans = 1;
    for (int i = 0; i < n; i++)
    	if ((a[v] > a[i]) + (b[v] > b[i]) + (c[v] > c[i]) >= 2)
    		ans += dfs(i);
    return ans;
}


int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif

  	scanf("%d",&n);
  	for (int i = 0; i < n; i++)
  		scanf("%s %d %d %d",name[i],&a[i],&b[i],&c[i]);

  	for (int i = 0; i < n; i++){
  		memset(used,0,sizeof(used));
  		
  		if (dfs(i) == n)
  			puts(name[i]);
  	}
      
    return 0;
}
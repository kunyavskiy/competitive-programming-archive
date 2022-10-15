#ifndef LOCAL
    #pragma comment(linker, "/STACK:33554432")
#endif

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

#ifndef M_PI
	#define M_PI 3.1415926535897932384626433832795
#endif


#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

int d[1100];
vector<int> g[1100];

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  int n,m;
  scanf("%d %d",&n,&m);
  for (int i = 0; i < m; i++){
  	int a,b;
  	scanf("%d %d",&a,&b);
  	--a,--b;
  	d[b]++;
  	g[a].pb(b);
  }

  for (int i = 0; i < n; i++){
  	int x;
  	cin >> x;
  	--x;

  	if (d[x]){
  		printf("NO\n");
  		return 0;  		
  	}   
  	for (int j = 0; j < g[x].size(); j++)
  		d[g[x][j]]--;
  }

  printf("YES\n");

  return 0;
}
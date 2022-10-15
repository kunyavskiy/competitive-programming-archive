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

ld dist[2][1100];
bool di[1100][1100];

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  int n,m;
  cin >> n >> m;
  int k;
  cin >> k;

  for (int i = 0; i < k; i++){
  	int a,b;
  	cin >>a  >> b;
  	di[a-1][b-1] = true;
  }

  for (int j = 0; j <= m; j++)
  		dist[0][j] = dist[1][j] = 1e100;

  dist[0][0] = 0;

  for (int i = 0; i <= n; i++)
  	for (int j = 0; j <= m; j++){
  		if (i == n && j == m)
  			continue;
  		int I = i & 1;
//  		cerr << i <<" "<<j<<" "<<dist[i][j] <<endl;
  		dist[I^1][j] = min(dist[I^1][j],dist[I][j]+100);
  		dist[I][j+1] = min(dist[I][j+1],dist[I][j]+100);
  		if (di[i][j])
  			dist[I^1][j+1] = min(dist[I^1][j+1],dist[I][j] + sqrt(2.0)*100);
  		dist[I][j] = 1e100;
  	}
  	
  cout << int(dist[n&1][m]+0.5) << endl;
  return 0;
}
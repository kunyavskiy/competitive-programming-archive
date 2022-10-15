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

#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

bool ok[110];
vector<int> g[110];

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  int n;
  cin >> n;
  for (int i = 0; i < n; i++){
  	int x;
  	for (cin>>x; x != 0; cin >> x)
  		g[i].pb(x-1);
  }
  
  vector<int> ans;

  for (int i = 0; i < n; i++)
  	if (!ok[i]){
  		ans.pb(i+1);
  		for (int j = 0; j < g[i].size(); j++)
  			ok[g[i][j]] = true;
  	}

  cout << ans.size() << endl;
  for (int i = 0; i < ans.size(); i++)
  	cout << ans[i] << " ";

  return 0;
}     
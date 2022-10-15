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

#define forn(i,n) for(int i=0;i<(n);i++)
#define ford(i,n) for(int i=(n)-1;i>=0;i--)

#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long int64;
typedef long long ll;
typedef long double ld;

vector <int> g, b;

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  int n, m;
  cin >> n >> m;
  g.resize(n);
  b.resize(m);
  int minn = 0;
  forn(i, n){
    cin >> g[i];
    minn += g[i];
  }
  forn(i, m)
    cin >> b[i];
  sort(g.rbegin(), g.rend());
  sort(b.rbegin(), b.rend());
  forn(i, min(g.size(), b.size())){
    int help = 0;
    for (int j = i + 1; j < g.size(); j ++)
        help += g[j];
    for (int j = i + 1; j < b.size(); j ++)
        help += (i + 1) * b[j];
    minn = min(minn, help); 
  }
    cout << minn; 
  return 0;
}
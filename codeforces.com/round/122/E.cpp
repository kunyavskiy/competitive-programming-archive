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


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  set<pair<ll,ll> > s;

  ll a = 0, b = 1;

  int cnt = 0;

  while (true){
    ll c = (a+b)%(10000000000000LL);
    a = b;
    b = c;
    if (s.find(mp(a,b)) != s.end())
        break;
    cnt++;
    s.insert(mp(a,b));

  }

  cout << cnt;

  return 0;
}
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

map<string,int> v;

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  string s,t;
  int n;
  cin >> n;
  
  for (int i = 0; i < (1<<n); i++)
    cin >> s>>t,v[t]++;

  int mx = 0;

  for (map<string,int>::iterator iter = v.begin(); iter != v.end(); ++iter)
    mx = max(mx,iter->second);

  int ans = n;

  for (; (1<<(n-ans)) < mx; ans--);

  printf("%d\n",ans);
  return 0;
}
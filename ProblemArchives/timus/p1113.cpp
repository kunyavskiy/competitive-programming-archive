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
    #define M_PI 3.1415926535897932384626433832795
    #define prev prev_dsfdfgfhgfh
    #define next next_mkdlsmfdgkl
    #define hash hash_mdfdsgdhgfm
    #undef assert
    #define assert(x) if (!(x)) throw 1
    #define sqrt(x) sqrt((double)(x))
#endif

using namespace std;

typedef long long ll;
typedef long double ld;


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  int a,m,n;
  ld d,o,w;

  cin >> n >> m;
  a = w = o = 0;

  while (true){
    a++;
    d = ld(m) / (2*a - 1);
    if (w+d>=n) break;
    w = w+d;
    o = o+m;
  }

  d = n-w;
  o = o+d*(a*2-1);
  cout << (int(o+0.999999999999)) << endl;

  return 0;
}
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

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  int n;
  cin >> n;
  cout << 4 * n - 2 << endl;
  forn(i, n)
    printf ("%d ", i + 1);
  ford(i, n - 1)
    printf ("%d ", i + 1);
  forn(i, n)
    printf ("%d ", i + 1);
  ford(i, n - 1)
    printf ("%d ", i + 1);
  return 0;
}
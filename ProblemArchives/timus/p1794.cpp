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

int a[200100];
int col[200100];
bool use[200100];

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  int n;
  cin >> n;
  memset(use, false, sizeof(use));
  forn(i, n){
    scanf ("%d ", &a[i]);
    a[i]--;
    col[(i - a[i] + n) % n] ++;
  }
  int maxx = 0, maxi;
  forn(i, n)
        if (maxx < col[i]){
            maxx = col[i];
            maxi = i;
    } 
    cout << maxi + 1;
  return 0;
}
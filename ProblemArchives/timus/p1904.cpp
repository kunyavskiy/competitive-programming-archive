#ifndef LOCAL
   #pragma comment(linker, "/STACK:67108864")
#endif

#include <stdio.h>
#include <ctype.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <string.h>
#include <algorithm>
#include <stdlib.h>
#include <functional>
#include <iterator>
#include <time.h>
#include <assert.h>
#include <queue>
#include <stack>
#include <deque>
#include <set>
#include <map>
#include <string>
#include <vector>
#include <utility>

#define MPI 3.141592653589793238462643
#define eps 1e-8
#define inf ((int)1e9)
#define pb push_back
#define mp make_pair
#define zero(a) memset(a,0,sizeof(a))
#define sqr(x) ((x)*(x))

#if defined(__WIN32__) && defined(__GNUC__)
   #define LLD "%I64d"
#else
   #define LLD "%lld"
#endif

#ifndef __GNUC__
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
typedef double ld;

#ifdef LOCAL
    ld START = clock();
    #define TIME (clock()-START)/CLOCKS_PER_SEC
    #define PRINT_TIME cerr << "Time: "<< TIME <<"s"<< endl;
#else
  #define PRINT_TIME (void)0
#endif

const int MAXN = 110000;

bool ok[3*MAXN+1];
int a[11];
int n;


bool good(int x){
    for (int i = 0; i < n; i++)
         x = abs(x - a[i]);
    return x <= 1;
}


int main(){
  #ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
  #endif

  scanf("%d",&n);
  for (int i = 0; i < n; i++)
    scanf("%d",&a[i]);

  int sdv = MAXN+100;

  for (int i = -MAXN+1; i < MAXN; i++)
      if (good(i))
        ok[sdv+i] = true;

  vector<pair<int,int> > v;

  for (int i = 1; i < MAXN+sdv+10; i++){
       if (ok[i] && !ok[i-1])
         v.pb(mp(i-sdv,-1));
       if (!ok[i] && ok[i-1])
         v.back().second = i-sdv-1;
  }

  printf("%d\n",v.size());

  for (int i = 0; i < (int)v.size(); i++)
    printf("%d %d\n",v[i].first,v[i].second);
  PRINT_TIME;
  return 0;
}

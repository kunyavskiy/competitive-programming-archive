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

int a[MAXN];
bool used[MAXN];
int n,s;

int main(){
  #ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
  #endif

  scanf("%d %d",&n,&s);
  for (int i = 0; i < n; i++)
    scanf("%d",&a[i]);

  sort(a,a+n);
  vector<int> ans;

  int ptr = 0;

  for (int i = n-1; i > ptr; i--){
      while (ptr < i && a[ptr] + a[i] <= s)
        ptr++;
      if (ptr < i){
         ans.pb(a[ptr]);
         ans.pb(a[i]);
         used[i] = used[ptr++] = true;
      }
  }

  for (int i = n-1; i >= 0; i--)
    if (!used[i])
        ans.pb(a[i]);

  int cnt = 0;

  for (int i = 0; i < n; i++){

    cnt++;
    if (i != n-1 && ans[i] + ans[i+1] <= s)
        i++;
  }

  printf("%d\n",cnt);

  for (int i = 0; i < n; i++)
    printf("%d%c",ans[i]," \n"[i==n-1]);

  PRINT_TIME;
  return 0;
}

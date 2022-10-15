#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <ctime>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cassert>
#include <queue>
#include <string>
#include <ctime>
#include <stack>

#define sqr(x) ((x)*(x))
#define sz(a) (int)a.size()
#define pb push_back
#define mp make_pair
#define zero(a) memset (a, 0, sizeof(a))



#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

#define maxn 101

int a[maxn][maxn];

int n;

#define taskname ""

const int inf = (int)1e9;

int main (void){
#ifdef LOCAL
  freopen ("input.txt", "r", stdin);
    freopen ("output.txt", "w", stdout);
#endif
  scanf ("%d", &n);

  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      scanf ("%d", &a[i][j]);

  int ans = 0;

  for (int i = 1; i < n; i++)
  {
    int sum = 0;
    for (int j = 0; j < i; j++)
      for (int k = i; k < n; k++)
        sum += a[j][k];
    ans = max (ans, sum / 36 + !!(sum % 36 != 0));
  }


//  cerr<<ans<<endl;

  for (int i = n - 2; i >= 0; i--)
  {
    int sum = 0;
    for (int j = n - 1; j > i; j--)
      for (int k = i; k >= 0; k--)
        sum += a[j][k];
    ans = max (ans, sum / 36 + !!(sum % 36 != 0));
  }


  printf ("%d\n", ans);

  return 0;
  
}
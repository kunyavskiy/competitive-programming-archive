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

#define taskname ""

const int inf = (int)1e9;

#define maxn 101

double a[maxn];

int main (void){
#ifdef LOCAL
  freopen ("input.txt", "r", stdin);
    freopen ("output.txt", "w", stdout);
#endif
  int n;

  scanf ("%d", &n);

  double sum = 0.0;

  for (int i = 0; i < n; i++)
    scanf ("%lf", &a[i]), sum += a[i];

  double k = 0;

  for (int i = 0; i < n; i++)
  {
    if (a[i] > sum / (n + 1))
      a[i] -= sum / (n + 1), k += a[i];
    else
      a[i] = 0.0;
      
  }

  for (int i = 0; i < n; i++)
  {
    printf ("%d ", (int)(a[i] * 100 / k + 1e-9));
  }

  return 0;
  
}
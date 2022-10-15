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

bool u[3][220]; //y, x+y, x-y;
int Y[220], n;
int G[110000];

int gcd (int a, int b)
{
  if (b==0)
    return a;
  return gcd(b,a%b);
}

void gen (int x)
{
  int i;
  if (x==n)
  {
    puts("Yes");
    for (i=0; i<n; i++)
      printf("%d ", Y[i]+1);
    printf("\n");
    exit(0);
  }
  for (i=0; i<n; i++)
    if (!(u[0][i] || u[1][(x+i)%n] || u[2][(x-i+n)%n]))
    {
      u[0][i]=1, u[1][(x+i)%n]=1, u[2][(x-i+n)%n]=1, Y[x]=i;
      gen(x+1);
      u[0][i]=0, u[1][(x+i)%n]=0, u[2][(x-i+n)%n]=0;
    }
}

int main (void){
/*#ifdef LOCAL
  freopen ("input.txt", "r", stdin);
    freopen ("output.txt", "w", stdout);
#endif*/
  scanf("%d", &n);
  if (n<12)
  {
    gen(0);
    puts("No");
    return 0;
  }
  int i, j, c;
  for (i=1; i<=n; i++)
    G[i]=gcd(i,n);
  for (i=2; i<n-1; i++)
    if (G[i]==1 && G[i+1]==1 && G[i-1]==1)
    {
      puts("Yes");
      for (c=0, j=0; j<n; j++, c=(c+i)%n)
        printf("%d ", c+1);
      printf("\n");
      return 0;
    }
  puts("No");
  return 0;
  
}
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <list>
#include <queue>
#include <stack>
#include <deque>
#include <iterator>

#define mp make_pair
#define pb push_back
#define sqr(a) ((a) * (a))
#define zero(a) memset (a, 0, sizeof(a))
#define sz(a) (int)(a.size())

#ifdef LOCAL
	#define LLD "%I64d"
#else 
	#define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef unsigned int uint;

#define taskname "d6"

const int inf = 1000000000;
const ld eps = 1e-9;


int D[105][5100], S[105][5100], n, k, p, res;

int add (int a, int b)
{
  int c=a+b;
  if (c>=p)
    c-=p;
  return c;
}

int sub (int a, int b)
{
  int c=a-b;
  if (c<0)
    c+=p;
  return c;
}

int main(){
  int it, j, i, l;
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);
  scanf("%d%d%d", &n, &k, &p);
  D[50][0]=1;
  int w=k/2+1, ls=w;
  if (k%2==0)
    ls--;
  for (it=0; it<n; it++)
  {
    for (j=50-it; j<=50+it; j++)
      for (l=0; l<=it*k; l++)
        if (D[j][l]!=0)
        {
          S[j-1][0]=add(S[j-1][0],D[j][l]);
          S[j-1][ls]=sub(S[j-1][ls],D[j][l]);

          S[j][l+ls]=add(S[j][l+ls],D[j][l]);
          S[j][l+w]=sub(S[j][l+w],D[j][l]);

          S[j+1][l+w]=add(S[j+1][l+w],D[j][l]);
          S[j+1][l+k+1]=sub(S[j+1][l+k+1],D[j][l]);
        }
    for (i=0; i<=100; i++)
      for (D[i][0]=S[i][0], j=1; j<=(it+1)*k; j++)
      {
        D[i][j]=add(D[i][j-1],S[i][j]);
        if (D[i][j])
          cerr<<it<<" "<<i<<" "<<j<<endl;
      }
    memset(S,0,sizeof(S));
  }
  for (i=0; i<50; i++)
    for (j=((n*k)/2)+1; j<=n*k; j++)
    {
      if (D[i][j])
        cerr<<D[i][j]<<endl;
      res=add(res,D[i][j]);
    }
  res=add(res,res);
  printf("%d\n", res);
  return 0;
}


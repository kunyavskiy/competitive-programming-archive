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

#define taskname "b"

const int inf = 1000000000;
const ld eps = 1e-9;

int res=inf, G[110000][2];
bool L[110000];
int Sz[110000], n;

void dfs (int v)
{
  if (G[v][0]==n || G[v][1]==n)
    L[v]=1;
  if (G[v][0]!=n)
    dfs(G[v][0]);
  if (G[v][1]!=n)
    dfs(G[v][1]);
  if (G[v][1]!=n && G[v][0]==n)
    res=min(res,v);
  if (!L[v])
    Sz[v]=1+min(Sz[G[v][0]],Sz[G[v][1]]);
  if ((!L[v]) && Sz[G[v][0]]<Sz[G[v][1]])
    res=min(res,v);
}

int main(){
  int i, j;
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);
  scanf("%d", &n);
  for (i=0; i<n; i++)
    for (j=0; j<2; j++)
    {
      scanf("%d", &G[i][j]);
      if (G[i][j]!=-1)
        G[i][j]--;
      else
        G[i][j]=n;
    }
  dfs(0);
  if (res==inf)
    puts("-1");
  else
    printf("%d\n", res+1);
  return 0;
}


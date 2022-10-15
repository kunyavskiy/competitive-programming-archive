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

#define taskname "j"

const int inf = 1000000000;
const ld eps = 1e-9;

int A[(1<<21)+10];

int get (int l, int r)
{
  l+=(1<<20), r+=(1<<20);
  int res=0;
  while (l<r)
  {
    if (l&1)
      res+=A[l], l++;
    if (r&1)
      r--, res+=A[r];
    l/=2, r/=2;
  }
  return res;
}

void add (int v, int d)
{
  v+=(1<<20);
  while (v>0)
    A[v]+=d, v/=2;
}

int main(){
  int x, y, i, n, q;
  char c;
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);
  scanf("%d%d", &n, &q);
  for (i=0; i<n; i++)
    scanf("%d", &A[i+(1<<20)]);
  for (i=(1<<20)-1; i>=0; i--)
    A[i]=A[2*i]+A[2*i+1];
  for (i=0; i<q; i++)
  {
    scanf(" %c%d%d", &c, &x, &y);
    if (c=='?')
      printf("%d\n", get(x-1,y));
    else
      add(x-1,y);
  }
  return 0;
}


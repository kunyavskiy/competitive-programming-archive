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

#define taskname "m"
#define mod (1000007ll)
#define maxp (239017ll)

const int inf = 1000000000;
const ld eps = 1e-9;

long long Deg[6];

struct point{
  int X[5];
  point neg ()
  {
    point ret;
    for (int i=0; i<5; i++)
      ret.X[i]=-X[i];
    return ret;
  }
  int sz(){
    int ret=0; 
    for (int i=0; i<5; i++)
      if (X[i]!=0)
        ret=i+1;
    return ret;
  }
  int hash ()
  {
    long long ret=0;
    for (int i=0; i<5; i++)
      ret+=X[i]*Deg[i];
    return ((ret%mod)+mod)%mod;
  }
};

point dir, A[41000], tp;
long long res1, res2;
int n, d, k, cnt;
int F[mod][2];

bool operator < (point a, point b)
{
  for (int i=0; i<5; i++)
    if (a.X[i]!=b.X[i])
      return a.X[i]<b.X[i];
  return 0;
}

int main(){
  int i, j;
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);
  scanf("%d%d%d", &d, &n, &k);
  for (Deg[0]=1, i=1; i<6; i++)
    Deg[i]=(Deg[i-1]*maxp)%mod;
  for (i=0; i<k; i++)
    for (j=0; j<d; j++)
      scanf("%d", &A[i].X[j]);
  for (dir.X[0]=-1; dir.X[0]<=1; dir.X[0]++)
  for (dir.X[1]=-1; dir.X[1]<=1; dir.X[1]++)
  for (dir.X[2]=-1; dir.X[2]<=1; dir.X[2]++)
  for (dir.X[3]=-1; dir.X[3]<=1; dir.X[3]++)
  for (dir.X[4]=-1; dir.X[4]<=1; dir.X[4]++)
    if (dir.sz()<=d && dir.sz()>0 && dir.neg()<dir)
    {
      cnt++;
      //cerr<<cnt<<endl;
      int tmp=dir.sz()-1;
      for (i=0; i<k; i++)
      {
        //cerr<<"???"<<endl;
        tp=A[i];
        int coef=-(A[i].X[tmp]*dir.X[tmp]);
        for (j=0; j<d; j++)
          tp.X[j]+=dir.X[j]*coef;
        assert(tp.X[tmp]==0);
        int y=tp.hash();
        if (F[y][0]<cnt)
          F[y][0]=cnt, F[y][1]=0;
        res1+=F[y][1], F[y][1]++;
        if (F[y][1]>1)
          res2++;
      }
    }
  cout<<res1<<endl<<res2<<endl;
  return 0;
}


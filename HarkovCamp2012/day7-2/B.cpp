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
#define maxp (239017ll)

const int inf = 1000000000;
const ld eps = 1e-9;

long long DM[(1<<16)+20];
int res, n, m, sz;
int G[1300][100];
int C[100];
set <long long> H;
long long ch, Deg[2000];

void gen (int v)
{
  if (H.count(ch))
    return;
  H.insert(ch);
  cerr<<v<<" "<<C[0]<<" "<<sz<<" "<<ch<<"     "<<res<<endl;
  if (v==n)
  {
    res+=sz;
    return;
  }
  int i;
  int up=(v+31)/32;
  bool fl=0;
  for (i=0; i<up; i++)
    if ((G[v][i]&C[i])!=C[i])
    {
      fl=1;
      break;
    }
  if (fl)
  {
    ch++, gen(v+1), ch--;
    int fu=v/16, r=v%16;
    int osz=sz, OC[100];
    long long och=ch;
    ch=0;
    memcpy(OC,C,sizeof(C));
    for (sz=1, i=0; i<fu; i++)
      C[i]&=G[v][i], sz+=__builtin_popcount(C[i]), ch+=Deg[i*16]*DM[C[i]];
    for (i=0; i<r; i++)
      if (C[fu]&(1<<i))
        (G[v][fu]&(1<<i))?(sz++, ch+=Deg[fu*16+i]):(C[fu]^=(1<<i));
    C[fu]+=(1<<r), ch+=Deg[v];
    ch*=maxp, ch+=v+1;
    gen(v+1);
    sz=osz, memcpy(C,OC,sizeof(C)), ch=och;
    return;
  }
  ch++, sz++, C[v/16]|=(1<<(v%16)), ch+=Deg[v+1];
  gen(v+1);
  sz--, ch--, C[v/16]^=(1<<(v%16)), ch-=Deg[v+1];
}   

void add (int a, int b)
{
  G[a][b/32]|=(1<<(b%32));
}

int main(){
  int i, a, b;
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);
  scanf("%d%d", &n, &m);
  for (i=0; i<m; i++)
    scanf("%d%d", &a, &b), add(a,b), add(b,a);
  for (Deg[0]=1ll, i=1; i<2000; i++)
    Deg[i]=Deg[i-1]*maxp;
  for (i=1; i<(1<<16); i++)
  {
    if (i&1)
      DM[i]=DM[i-1]+maxp;
    else
      DM[i]=maxp*DM[i/2];
  }
  gen(0);
  printf("%d\n", res);
  return 0;
}


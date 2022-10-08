//#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <cstdlib>
#include <cstdio>
#include <iterator>
#include <functional>
#include <bitset>
#define mp make_pair
#define pb push_back

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

#if ( ( _WIN32 || __WIN32__ ) && __cplusplus < 201103L)
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "C"

#ifdef LOCAL
static struct __timestamper {
    string what;
    __timestamper(const char* what) : what(what){};
    __timestamper(const string& what) : what(what){};
	~__timestamper(){
        TIMESTAMPf("%s", what.data());
	}
} __TIMESTAMPER("end");
#endif

typedef long long ll;
typedef long double ld;


namespace dinic {

const int maxn = 20 * 20 + 10;
const int maxe = maxn * 5;

// you can see this code at  http://acm.math.spbu.ru/~kuniavski/notebook/dinic.cpp
//finds maxflow from "st" to "end"
//V - throughput of edges
//reverse edge has num "edge_num^1"

int Head[maxn], Next[2*maxe];
int Dest[2*maxe], e, mfl;
int V[2*maxe];
int u[maxn], uit, Lv[maxn], end, st, B[maxn];
long long flow;
int Q[maxn], bq, eq;

void add (int v1, int v2, int v)
{
  Dest[e]=v2, Next[e]=Head[v1];
  Head[v1]=e, V[e]=v, e++;
  assert(e<=2*maxe); 
}

int dfs (int v, int fl)
{ 
  int nfl, nv, ne;
  u[v]=uit;
  if (v==end)
  {
    flow+=fl;
    return fl;
  }
  for ( ; B[v]!=-1; B[v]=Next[B[v]])
  {
    ne=B[v], nv=Dest[ne]; /*BOXNEXT*/
    if (u[nv]!=uit && V[ne]>=mfl && Lv[nv]==Lv[v]+1)
    {
      nfl=dfs(nv,min(V[ne],fl));
      if (nfl) 
      {
        V[ne]-=nfl, V[ne^1]+=nfl;
        return nfl;
      }
    }
  }
  return 0;
}

long long dinic (int n, int _st, int _end)
{
  int v, r, i;
  flow=0;
  st=_st, end=_end, mfl=(1<<29);
  while (mfl)
  {
    while (true)
    {
      for (i=0; i<n; i++)
        Lv[i]=inf, B[i]=Head[i];
      Lv[st]=0, Q[0]=st, bq=0, eq=1;
      
      
      while (bq<eq) 
      {
        v=Q[bq++];
        for (r=Head[v]; r!=-1; r=Next[r])
          if (V[r]>=mfl && Lv[Dest[r]]==inf) {
            Lv[Dest[r]]=Lv[v]+1;
            Q[eq++]=Dest[r];
          }
      }
      if (Lv[end]==inf)
        break;
      uit++;
      while (dfs(st,inf))
        uit++;
    }
    mfl>>=1;
  }
  return flow;
}

}


int n,m;   
char s[25][25];




int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif
    scanf("%d %d",&n,&m);
    for (int i = 0; i < n; i++)
    	scanf(" %s",s[i]);

      
  return 0;
}
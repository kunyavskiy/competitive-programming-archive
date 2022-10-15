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

int n, m, R[110000][4], T[110000];
vector <pair <int, int> > V[110000];
int Cur[110000];
int bq, eq, Q[110000];
int Prev[110000];
int er=-2;
int sp, fp, st, ft;
vector <int> RV;

void update (int v, int r) 
{
  int nv, id;
  while (V[v][Cur[v]].first>=T[v])
  {
    id=V[v][Cur[v]].second, nv=R[id][1];
    if (T[nv]>R[id][3])
    {
      Q[eq++]=id, Prev[id]=r;
      if (nv==fp && ft>=R[id][3] && er == -2)
        er=id;
    }
    Cur[v]--;
  }
}

int main(){
  int i, j;
  #ifdef LOCAL
    freopen(".in", "r", stdin);
    freopen(".out", "w", stdout);
  #endif
  scanf("%d%d", &n, &m);
  for (i=0; i<m; i++)
  {
    for (j=0; j<4; j++)
      scanf("%d", &R[i][j]);
    R[i][0]--, R[i][1]--;
    V[R[i][0]].pb(mp(R[i][2],i));
  }   
  for (i=0; i<n; i++)
    Cur[i]=(int)V[i].size(), V[i].pb(mp(-1,-1)), sort(V[i].begin(),V[i].end()), T[i]=inf;
  scanf("%d%d%d%d", &sp, &fp, &st, &ft), sp--, fp--;
  if (sp==fp && st<=ft)
  {          
    puts("0");
    return 0;
  }
  memset(Prev,-1,sizeof(Prev));
  T[sp]=st, update(sp,-3);
  while (bq<eq)
  {
    if (T[R[Q[bq]][1]]>R[Q[bq]][3])
      T[R[Q[bq]][1]]=R[Q[bq]][3], update(R[Q[bq]][1],Q[bq]);
    bq++;
  }
  if (er==-2)
  {
    puts("Impossible");
    return 0;
  }
  while (er!=-3)
    RV.pb(er+1), er=Prev[er];
  assert(er==-3);
  printf("%d\n", (int)RV.size());
  reverse(RV.begin(),RV.end());
  for (i=0; i<(int)RV.size(); i++)
    printf("%d ", RV[i]);
  printf("\n");
  PRINT_TIME;
  return 0;
}

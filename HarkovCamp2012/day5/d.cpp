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

#define taskname "d"

const int inf = 1000000000;
const ld eps = 1e-9;

map <char, int> M;
char s[21000];
int n, A[21000], D[21000];
vector <int> V[10];
int B[50], e;

void add (int v, int m)
{
  for (int i=0; i<(int)V[v].size(); i++)
    B[e++]=m*V[v][i];
}

int calc (int l, int r)
{
  int res=0, i;
  for (i=l; i<=r; i++)
  {
    if (A[i]<A[i+1] && i!=r)
      res-=A[i];
    else
      res+=A[i];
  }
  //cerr<<l<<"    "<<r<<"  "<<res<<endl;
  int tmp=res;
  if (res>3999 || res<=0)
    return inf;
  //cerr<<"!!!!  "<<res<<endl;
  e=0;
  add(tmp/1000,1000), tmp%=1000;
  add(tmp/100, 100), tmp%=100;
  add(tmp/10,10), tmp%=10;
  add(tmp,1);
  /*cerr<<"!!!!  "<<res<<endl;
  for (i=0; i<e; i++)
    cerr<<B[i]<<" ";
  cerr<<endl;*/

  if (e!=r-l+1)
    return inf;
  for (i=0; i<e; i++)
    if (B[i]!=A[l+i])
      return inf;
  //cerr<<l<<" "<<r<<"    "<<res<<endl;
  return res;
}

int main(){
  int i, j;
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);
  gets(s);
  n=strlen(s);
  M['I']=1, M['V']=5, M['X']=10, M['L']=50, M['C']=100, M['D']=500, M['M']=1000;
  for (i=0; i<n; i++)
    A[i]=M[s[i]];
  for (i=0; i<4; i++)
    for (j=0; j<i; j++)
      V[i].pb(i);
  V[4].pb(1), V[4].pb(5);
  V[5].pb(5);
  for (i=6; i<9; i++)
    for (V[i].pb(5), j=0; j<i-5; j++)
      V[i].pb(1);
  V[9].pb(1), V[9].pb(10);
  for (i=1; i<=n; i++)
  {
    for (D[i]=inf, j=1; j<=20 && j<=i; j++)
      D[i]=min(D[i],D[i-j]+calc(i-j,i-1));
    //cerr<<i<<" "<<D[i]<<endl;
  }
  printf("%d\n", D[n]);
  return 0;
}


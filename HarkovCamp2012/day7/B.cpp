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


map <pair <int, int>, int> M;
pair <int, int> RM[210];
int sz, Snm[210];
int A[310][2], B[310][2], ea, eb;
set <int> S;

int SNM (int v)
{
  if (Snm[v]==v)
    return v;
  Snm[v]=SNM(Snm[v]);
  return Snm[v];
}

void join (int a, int b)
{
  a=SNM(a), b=SNM(b);
  Snm[a]=b;
}

bool check ()
{
  int i;
  for (i=0; i<sz; i++)
    Snm[i]=i;
  for (i=0; i<ea; i++)
    join(M[mp(A[i][0],0)],M[mp(A[i][1],1)]);
  for (i=0; i<eb; i++)
    if (SNM(M[mp(B[i][0],0)])==SNM(M[mp(B[i][1],1)]))
      return 0;
  return 1;
}

int main(){
  int f, s, i, j, n, ls, lt, k;
  char c;
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);
  scanf("%d%d%d", &n, &ls, &lt);
  for (i=0; i<n; i++)
  {
    scanf("%d %c%d", &f, &c, &s), f--, s--;
    if (!M.count(mp(f,0)))
      M[mp(f,0)]=sz, RM[sz]=mp(f,0), sz++;
    if (!M.count(mp(s,1)))
      M[mp(s,1)]=sz, RM[sz]=mp(s,1), sz++;
    if (c=='=')
      A[ea][0]=f, A[ea][1]=s, ea++;
    else
      B[eb][0]=f, B[eb][1]=s, eb++;
  }       
  if (!check())
  {
    //cerr<<"!@"<<endl;
    puts("0");
    return 0;
  }
  int oea=ea;
  for (i=0; i<sz; i++)
    for (j=0; j<sz; j++)
    {
      if (RM[i].second!=0 || RM[j].second!=1)
        continue;
      int b=RM[j].first-RM[i].first;
      if (b>=0 && b<=lt-ls)
      {
        for (k=0; k<sz; k++)
          if (RM[k].second==0)
          {
            if (!M.count(mp(RM[k].first+b,1)))
              continue;
            A[ea][0]=RM[k].first, A[ea][1]=RM[k].first+b, ea++;
          }
        //cerr<<ea<<" "<<oea<<endl;
        if (!check())
          S.insert(b);
        ea=oea;
      }
    }
  printf("%d\n", max(lt-ls+1,0)-((int)S.size()));
  return 0;
}


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

#define taskname "l"

const int inf = 1000000000;
const ld eps = 1e-9;

const int SZ=2001;
const int MC=12000/SZ;
double tt=clock();

vector <pair <int, int> > V[MC][MC];
pair <int, int> P[MC+2][MC+2];
int a, b, c;
int n, m;

bool solve (pair <int, int> p)
{
  return a*p.first+b*p.second+c>=0;
}

int main(){
  int i, j, k, l;
  int x, y;
  bool f1, f2, f3, f4;
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);
  scanf("%d%d%d", &n, &m, &c);
  for (i=0; i<n; i++)
  {
    scanf("%d%d", &x, &y);
    V[x/SZ][y/SZ].pb(mp(x,y));
  }
  for (i=0; i<MC+2; i++)
    for (j=0; j<MC+2; j++)
      P[i][j]=mp(i*SZ,j*SZ);
  for (i=0; i<m; i++)
  {
    int res=0;
    scanf("%d%d%d", &a, &b, &c);
    for (j=0; j<MC; j++)
      for (k=0; k<MC; k++)
      {
        f1=solve(P[j][k]), f2=solve(P[j][k+1]), f3=solve(P[j+1][k]), f4=solve(P[j+1][k+1]);
        if (f1 && f2 && f3 && f4)
        {
          res+=(int)V[j][k].size();
          continue;
        }
        if (!(f1 || f2 || f3 || f4))
          continue;
        int sz = V[j][k].size();
        vector<pair<int,int> > & vjk= V[j][k];
        for (l=0; l<sz; l++)
          if (solve(vjk[l]))
            res++;
      }
    printf("%d\n", res);
  }
  cerr<<(clock()-tt)/CLOCKS_PER_SEC<<endl;
  return 0;
}


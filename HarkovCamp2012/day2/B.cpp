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

void out (int x, int y)
{
  if (x<26)
    printf("%c", 'a'+x);
  else
    printf("%c", 'A'+x-26);
  printf("%d\n", y+1);
}

int D[50][50], n, b, cnt, fr, now;
int dx[8]={0,0,-1,1,1,1,-1,-1};
int dy[8]={1,-1,0,0,-1,1,-1,1};
bool F[50][50];
int res;
vector <pair <int, int> > Ans;

bool good (int x, int y)
{
  return (x>=0 && x<n && y>=0 && y<n);
}

void gen (int x, int y)
{
  //cerr<<now<<" "<<fr<<"   "<<x<<" "<<y<<"   "<<n<<" "<<b<<endl;
  int i, nx, ny, j;
  if (now+fr<res)
    return;
  if (y==n)
    y=0, x++;
  if (x==n)
  {
    bool fl=1;
    for (i=0; i<n && fl; i++)
      for (j=0; j<n && fl; j++)
        if (F[i][j] && D[i][j]!=b+1)
          fl=0;
    if (fl && res<now)
    {
      cerr<<res<<" "<<now<<endl;
      res=now;
      Ans.clear();
      for (i=0; i<n; i++)
        for (j=0; j<n; j++)
          if (F[i][j])
            Ans.pb(mp(i,j));
    }
    return;
  }
  if (D[x][y]<=b)
  {
    bool fl=0;
    F[x][y]=1, D[x][y]++;
    fr--;
    for (i=0; i<8; i++)
      for (nx=x+dx[i], ny=y+dy[i]; good(nx,ny); nx+=dx[i], ny+=dy[i])
      {
        D[nx][ny]++;
        if (D[nx][ny]==b+1 && mp(x,y)>mp(nx,ny))
          fr--;
        if (D[nx][ny]>b+1 && F[nx][ny])
          fl=1;
      }
    if (!fl)
      now++, gen(x,y+1), now--;
    for (i=0; i<8; i++)
      for (nx=x+dx[i], ny=y+dy[i]; good(nx,ny); nx+=dx[i], ny+=dy[i])
      {
        D[nx][ny]--;
        if (D[nx][ny]==b && mp(x,y)>mp(nx,ny))
          fr++;
      }
    fr++;
    D[x][y]--, F[x][y]=0;
  }
  if (D[x][y]<=b)
    fr--;
  gen(x,y+1);
  if (D[x][y]<=b)
    fr++;
}

int main(){
  int i;
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);
  scanf("%d%d", &n, &b);
  if (n<10)
  {
    fr=n*n;
    gen(0,0);
    for (i=0; i<(int)Ans.size(); i++)
      out(Ans[i].first, Ans[i].second);
    return 0;
  } 
  if (b==1)
  {
    if (n&1)
      n--;
    int f=0, s=n-1, cnt=0;
    while (f<s)
      out(cnt,f), out(cnt,s), f+=2, s-=2, cnt++;
    cnt=n-1, f=1, s=n-2;
    while (f<s)
      out(cnt,f), out(cnt,s), f+=2, s-=2, cnt--;
    return 0;
  }
  if (b==2)
  {
  	if (n <= 10){
  		for (i=0; i<n; i++)
		   out(i,0);
		out(n-1,n-1);
	    return 0;
  	}
    if (n % 2 == 1)
    	--n;
    for (i=0; i<n/2; i++)
      out(0,i);
	out(0,n/2+1);
	out(1,n/2+1);
	out(2,n/2+2);
	for (int i = n/2+4; i < n-3; i++)
		out(2,i);
	out(2,n-2);
	out(2,n-1);	
	for (int i = n/2+1; i < n-1; i++)
		out(i,n/2);
	out(n-1,n/2);
	out(n-1,0);
    return 0;
  }
  if (b==3)
  {
    for (i=0; i<n; i++)
      out(0,i), out(n-1,i);
    return 0;
  }
  for (i=1; i<n-1; i++)
    out(0,i);
  for (i=1; i<n-1; i++)
    out(i,0), out(i,n-1);
  out(n-1,1), out(n-1,n-2);
  return 0;
}


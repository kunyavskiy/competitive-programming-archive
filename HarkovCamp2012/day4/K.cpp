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

#define taskname "k"

const int inf = 1000000000;
const ld eps = 1e-9;

int Next[110000][30];
bool C[11000];
bool T[110000];
char s[11000];

int norm (char c)
{
  if ((int)c==39)
    return 26;
  if ((int)c==96)
    return 27;
  if (c>='A' && c<='Z')
    return c-'A';
  return c-'a';
}

int main(){
  int n, len, i, v, j, e=1, k;
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);
  scanf("%d ", &n);
  memset(Next,-1,sizeof(Next));
  memset(Next,-1,sizeof(Next));
  for (i=0; i<n; i++)
  {
    gets(s);
    len=strlen(s);
    for (v=0, j=0; j<len; v=Next[v][norm(s[j])], j++)
    {
      int tmp=norm(s[j]);
      if (Next[v][tmp]==-1)
        Next[v][tmp]=e++;
    }
    T[v]=1;
  }
  gets(s), len=strlen(s);
  C[0]=1;
  for (i=0; i<len; i++)
    if (C[i])
    {
      for (v=0, k=i; k<len; k++)
      {
        int tmp=norm(s[k]);
        if (Next[v][tmp]!=-1)
          v=Next[v][tmp];
        else
          break;
        if (T[v])
          C[k+1]=1;
      }
    }
  if (C[len])
    puts("YES");
  else
    puts("NO");
  return 0;
}


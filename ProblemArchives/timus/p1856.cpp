#include <cstdio>
#include <cmath>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

typedef long long ll;
typedef long double ld;

#define zero(a) memset (a, 0, sizeof(a))
#define pb push_back
#define mp make_pair
#define sz(a) ((int)(a.size()))
#define sqr(a) ((a) * (a))

int n, G[1100][2];
int D[1100][1100][2];
vector <int> Prev[1100];
int b, e;
short Q[10000000][3];
bool fl;

inline int next (int a)
{
  a++;
  if (a==10000000)
    a=0;
  return a;
}

inline void add (int a, int b, int c)
{
  int i, j;
  for (i=0; i<(int)Prev[a].size(); i++)
    for (j=0; j<(int)Prev[b].size(); j++)
    {
      /*if (e>6100000)
      { 
        puts("WQWERTRYTU");
        exit(0);
      } */
      if (D[Prev[a][i]][Prev[b][j]][1-c]==0)
        Q[e][0]=Prev[a][i], Q[e][1]=Prev[b][j], Q[e][2]=1-c, e=next(e);
    }
}

void solve (int a, int bb)
{
  //cerr<<a<<" "<<b<<endl;
  b=0, e=0;
  int i, x, y, z;
  if (!fl)
  {
   fl=1;
  memset(D,0,sizeof(D));
  for (i=0; i<n; i++)
  {
    D[i][i][1]=1;
    add(i,i,1);
  }
  while (b<e)
  {
    
    x=Q[b][0], y=Q[b][1], z=Q[b][2];
    if (D[x][y][z]==0) 
    {
      if (D[G[x][0]][G[y][0]][1-z]==-1 || D[G[x][1]][G[y][1]][1-z]==-1)
      {
        D[x][y][z]=1;
        add(x,y,z);
      }
      if (D[G[x][0]][G[y][0]][1-z]==1 && D[G[x][1]][G[y][1]][1-z]==1)
      {
        D[x][y][z]=-1;
        add(x,y,z);
      }
    }
    b=next(b);
  }
  }
  /*for (i=0; i<n; i++)
    for (int j=0; j<n; j++)
      for (int k=0; k<2; k++)
        cerr<<i<<" "<<j<<" "<<k<<" "<<D[i][j][k]<<endl;
   cerr<<a<<" "<<b<<" "<<D[a][b][0]<<endl;*/
  if (D[a][bb][0]!=-1)
  {
    puts("Peace");
    exit(0);
  }
}

int main(void)
{
  int a, b, t, i, j;
//  freopen("input.txt", "r", stdin);
//  freopen("output.txt", "w", stdout);
  scanf("%d", &n);
  srand(time(NULL));
  for (i=0; i<n; i++)
     for (j=0; j<2; j++)
     {
       scanf("%d", &G[i][j]), G[i][j]--;
       Prev[G[i][j]].pb(i);
     }
  for (t=0; t<30000; t++)
  {
    a=rand()%n, b=rand()%n;
    while (a==b)
      a=rand()%n, b=rand()%n;
    solve(a,b);
  }
  for (i=0; i<n; i++)
    for (j=i+1; j<n; j++)
      solve(i,j);
  printf("War\n");
  return 0;
}
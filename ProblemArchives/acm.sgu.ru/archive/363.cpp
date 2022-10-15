#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <queue>
#include <memory.h>
#include <stack>
#define mp make_pair
#define pb push_back                     
#define int64 long long
#define ld long double  
#define setval(a,v) memset(a,v,sizeof(a))
using namespace std;

deque<int> q[100];

int t[100];
int c[100];
int aq[100];
int st[100];
int at[100];
int n,m;


void dotime(int T)
{
	for (int i=0;i<m;i++)
		if (!q[i].empty())
		{
			int f=q[i][0];
			if (st[f]+t[f]==T)
			{
				at[f]=T;
				q[i].pop_front();
				if (!q[i].empty())
					st[q[i][0]]=T;
			}
		}
	for (int i=0;i<n;i++)
		if (c[i]==T)
			{
				int minnum=0;
				for (int j=1;j<m;j++)
					if (q[minnum].size()>q[j].size())
						minnum=j;
				if (q[minnum].empty())
					st[i]=T;
				q[minnum].pb(i);
				aq[i]=minnum;
			}
}

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	scanf("%d %d",&n,&m);
	for (int i=0;i<n;i++)
		scanf("%d %d",&c[i],&t[i]);
	for (int i=0;i<15000;i++)
	{
		dotime(i);
	}
	for (int i=0;i<n;i++)
		printf("%d %d\n",aq[i]+1,at[i]);  
  return 0;
}
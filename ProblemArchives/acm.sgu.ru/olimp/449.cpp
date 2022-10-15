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

const int inf=10000000;

int d[110];
vector<int> g[110];
bool need[110];
int n;


int main()
{                        
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
	string s;
	getline(cin,s);
	n=s.size();
	for (int i=0;i<n;i++)
		need[i]=(s[i]=='D');
	int m;
	scanf("%d\n",&m);
	for (int i=0;i<m;i++){
		getline(cin,s);
		int a,b;
		if (sscanf(s.data(),"%d %d",&a,&b)==2){
			g[a].pb(b);
			g[b].pb(a);
		}
		else {
			sscanf(s.data(),"%d",&a);
			g[n].pb(a);
		}
	}
	++n;
	queue<int> q;
	q.push(n-1);
	for (int i=0;i<n;i++)
		d[i]=inf;
	d[n-1]=0;
	for (;!q.empty();){
		int v=q.front();
		q.pop();
//		cerr<<v<<endl;
		for (int i=0;i<g[v].size();i++)
			{
				if (d[g[v][i]]>d[v]+1){
					d[g[v][i]]=d[v]+1;
					q.push(g[v][i]);
				}
			}
	}
	int ans=0;
	for (int i=0;i<n;i++)
		if (need[i]){
			if (d[i]==inf)
				{
					printf("-1\n");
					return 0;
				}
			ans+=d[i];
		}
	cout<<ans<<endl;
  return 0;
}
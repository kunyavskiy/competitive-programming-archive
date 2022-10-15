#include <fstream>
#include <vector>
#include <utility>
#define mpair make_pair
using namespace std;

vector<vector<vector<pair<int,int>>>> g,tg;
vector<pair<int,int>> top;
bool used [2][16000];
int comp [2][16000];
int n,m;

void addrebg(pair<int,int> a,pair<int,int> b)
{
	g[a.first][a.second].push_back(b);
	tg[b.first][b.second].push_back(a);
	return;
}

void topsort(pair<int,int> v)
{
	if (used[v.first][v.second]) return;
	used[v.first][v.second]=true;
	if (v.second%2==1)
		topsort(mpair(1-v.first,v.second+1));
	else
	   topsort(mpair(1-v.first,v.second-1));	
	int l=g[v.first][v.second].size()-1;
	for (int i=0;i<=l;i++)
		topsort(g[v.first][v.second][i]);
	top.push_back(v);   
};

void dfs(pair<int,int> v,int compnum)
{
	if (used[v.first][v.second])  return;
	used[v.first][v.second]=true;
	if (v.second%2==1)
		dfs(mpair(1-v.first,v.second+1),compnum);
	else
	    dfs(mpair(1-v.first,v.second-1),compnum);	
	int l=tg[v.first][v.second].size()-1;
	for (int i=0;i<=l;i++)
		dfs(tg[v.first][v.second][i],compnum); 
	comp[v.first][v.second]=compnum;

};

int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
    scanf("%d %d",&n,&m);
    n*=2;
	g.resize(2);
	g[0].resize(n+1);
	g[1].resize(n+1);
	tg.resize(2);
	tg[0].resize(n+1);
	tg[1].resize(n+1);
	int i;
	//for (i=1;i<=n;i++)
	//{
	//	if (i%2==1)
	//	{
	//	  addrebg(mpair(1,i),mpair(0,i+1));
	//	  addrebg(mpair(0,i),mpair(1,i+1));				
	//	}
	//	else
	//	{
	//	  addrebg(mpair(1,i),mpair(0,i-1));
	//	  addrebg(mpair(0,i),mpair(1,i-1));				
	//	}
	//}
	for (i=1;i<=m;i++)
	{
		int a,b;
		scanf("%d %d",&a,&b);
		addrebg(mpair(1,a),mpair(0,b));
		addrebg(mpair(1,b),mpair(0,a));
	}
	for (int j=0;j<=1;j++)
		for (i=1;i<=n;i++)
			topsort(mpair(j,i));
	int  compnum=0;
	for (i=1;i<=n;i++)
	{
		used[1][i]=false;
		used[0][i]=false;
	}
	for (i=2*n-1;i>0;i--)
	{
		if (!used[top[i].first][top[i].second])
		{
			compnum++;
			dfs(top[i],compnum);
		}
	}
	for (i=1;i<=n;i++)
		if (comp[1][i]==comp[0][i])
		{
			printf("NO");
			return 0;
		}
    for (i=1;i<=n;i++)
		if (comp[1][i]>comp[0][i])
		{
			printf("%d\n",i);
		}
	return 0;	
}
#include <vector>
#include <fstream>
#include <utility>
#include <queue>
#include <stack>
#define forc(i,n) for(int i=1;i<=n;i++)
#define read(n) scanf("%d",&n);
#define mp make_pair

using namespace std;

int n,m,k;
vector<vector<pair<int,int>>> g;
int dest[101][101],a[101][101];
vector<pair<int,int>> ub,voi;
char from[101][101];
const int inf=1<<29;
vector<int> mt;
vector<bool> used;


void bfs(int x,int y)
{
	forc(i,n)
	  forc(j,m)
	     dest[i][j]=inf;
    dest[x][y]=0;
	queue<pair<int,int>> q;
	q.push(mp(x,y));
	for (;q.empty()==false;q.pop())
	{
		pair<int,int> temp=q.front();
		int xt=temp.first,yt=temp.second;
		if ((dest[xt+1][yt]==inf) && (a[xt+1][yt]!=1))
		{
             dest[xt+1][yt]=dest[xt][yt]+1;
			 from[xt+1][yt]='S';
			 q.push(mp(xt+1,yt));
		}
		if ((dest[xt-1][yt]==inf) && (a[xt-1][yt]!=1))
		{
             dest[xt-1][yt]=dest[xt][yt]+1;
			 from[xt-1][yt]='N';
			 q.push(mp(xt-1,yt));
		}
		if ((dest[xt][yt+1]==inf) && (a[xt][yt+1]!=1))
		{
             dest[xt][yt+1]=dest[xt][yt]+1;			 
			 from[xt][yt+1]='E';
			 q.push(mp(xt,yt+1));
		}
		if ((dest[xt][yt-1]==inf) && (a[xt][yt-1]!=1))
		{
             dest[xt][yt-1]=dest[xt][yt]+1;
			 from[xt][yt-1]='W';
			 q.push(mp(xt,yt-1));
		}
	}

}

bool kuhn (int v,int t) {
	if (used[v])  return false;
	used[v] = true;
	for (size_t i=0; i<g[v].size(); ++i)
		if (g[v][i].second<=t )
	   {
		   int to = g[v][i].first;
		if (mt[to] == -1 || kuhn (mt[to],t)) {
			mt[to] = v;
			return true;
		}
	}
	return false;
}


bool ok(int t)
{
	mt.resize(k+1);
	forc(i,k)
	    mt[i]=-1;
	for (int i=1; i<=k; ++i) {
		used.assign (k+1, false);
		kuhn (i,t);
	}
	forc(i,k)
		if (mt[i]==-1)
			return false;
	return true;
}

int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	read(m);
	read(n);
	forc(i,n)
		forc(j,m)
		  read(a[i][j]);
	k=0;
	ub.push_back(mp(0,0));
	forc(i,n)
		forc(j,m)
		  if (a[i][j]==2)
		  {
			  ub.push_back(mp(i,j));
			  k++;
		  }
	g.resize(k+1);
	voi.resize(k+1);
    forc(i,k)
	{
		read(voi[i].second);
		read(voi[i].first);
		bfs(voi[i].first,voi[i].second);
		forc(j,k)
			g[j].push_back(mp(i,dest[ub[j].first][ub[j].second]+3));

	}
	int l=2;int r=n*m+100;
	int mid=(l+r)/2;
	for (;r-l>1;mid=(r+l)/2)
		if (ok(mid)==true)
			r=mid;
		else
		    l=mid;
    if (r==n*m+100)
	{
		printf("0");
		return 0;
	}
    l=r;
    printf("%d\n",l);
	ok(l);
	vector<stack<char>> res(k+1);
	forc(i,k)
	{
		res[i].push('D');
		res[i].push('D');
		res[i].push('D');
		bfs(voi[i].first,voi[i].second);
		int xt=ub[mt[i]].first,yt=ub[mt[i]].second;
		for (;(xt!=voi[i].first)  || (yt!=voi[i].second);)
		{
			res[i].push(from[xt][yt]);
			switch (from[xt][yt])
			{
			case 'S': xt--;
					  break;
			case 'N': xt++;
					  break;
			case 'E': yt--;
					  break;
			case 'W':yt++;
					 break;
			}
		}
    
	}
	forc(i,l)
	{
		forc(j,k)
			if (!res[j].empty())
			{
				printf("%d %c ",j,res[j].top());
					res[j].pop();
			}
		printf("\n");
	}

	return 0;
}
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
const int MAXN=2010;
const int MAXM=200010;
vector<int> g[MAXN*2],g2[MAXN*2];
int E[MAXM][2];
int p[2*MAXN],t[MAXN*2],color[MAXN*2];
vector<int> res[MAXN];

int cnt,cc;
void dfs(int u)
{
     if(color[u]) return;
     color[u]=1;
     int i;
     for(i=0;i<(int)g[u].size();i++)
         dfs(g[u][i]);
     t[--cnt]=u;    
}
void dfs2(int u)
{
     if(color[u]) return;
     color[u]=cc;
     int i;
     for(i=0;i<(int)g2[u].size();i++)
         dfs2(g2[u][i]);
}
void findSCC(int n)
{
    cnt=n;
    int i;
    memset(color,0,sizeof(color));
    for(i=0;i<n;i++)
	{
        if(color[i]==0) dfs(i);
    }
    memset(color,0,sizeof(color));
    cc=0;
    for(i=0;i<n;i++)
	{
        if(color[t[i]]==0)
		{
           cc++;
           dfs2(t[i]);
        }
    }
}

int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int n,i,k,v,u,m=0;
    scanf("%d",&n);
    for(u=0;u<n;u++)
	{
       scanf("%d",&k);
       for(;k;k--)
	   {
          E[m][0]=u;
          scanf("%d",&E[m][1]);
          E[m][1]+=n-1;m++;
       }
    }
    for(u=0;u<n;u++)
	{
       scanf("%d",&v);
       v+=n-1;
       p[u]=v;p[v]=u;
    }
    for(i=0;i<m;i++)
	{
       u=E[i][0];v=E[i][1];
       if(p[u]==v)
	   {
          g[v].push_back(u);
          g2[u].push_back(v);
          continue;
       }
       g[u].push_back(v);          
       g2[v].push_back(u);
    }
    findSCC(2*n);

    printf("\n");
    for(i=0;i<m;i++)
	{
	u=E[i][0];v=E[i][1];
	if(color[u]==color[p[v]]) res[u].push_back(v-n+1);
    }
    for(u=0;u<n;u++)
	{
	printf("%d",res[u].size());
        for(i=0;i<(int)res[u].size();i++)
	    printf(" %d",res[u][i]);
 	printf("\n");
    }
    return 0;
}
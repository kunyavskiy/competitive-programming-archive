#include <iostream>
using namespace std;

int a[40][40];
int used[40][40];
int k,n,m;


void dfs(int x,int y,int h)
{
	if (used[x][y]<=h)
		return;
	if (h<=k)
		used[x][y]=h;
	else
		return;
	for (int i=-1;i<=1;i++)
		for (int j=-1;j<=1;j++)
		if (((i==0)^(j==0)) && (x+i<n) && (x+i>=0) && (y+j<m) && (y+j>=0) && (a[x+i][y+j]<=a[x][y]))
		{
			dfs(x+i,y+j,a[x+i][y+j]==a[x][y]?h+1:0);
		}
}
inline void used0()
{
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++)
			used[i][j]=1000;
}

int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	scanf("%d %d %d\n",&n,&m,&k);
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<m;j++)
		{
			char c;
			scanf("%c",&c);
			a[i][j]=c-'0';
		}
		scanf("\n");
	}
	int maxval=0;
	int maxx=-1;
	int maxy=-1;
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++)
		{
			used0();
			dfs(i,j,0);
			int res=0;
			for (int i1=0;i1<n;i1++)
				for (int j1=0;j1<m;j1++)
					if (used[i1][j1]!=1000)
						res++;
			if (res>maxval)
			{
				maxval=res;
				maxx=i;
				maxy=j;
			}
		}
	used0();
	dfs(maxx,maxy,0);
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<m;j++)
		{
			if (used[i][j]==1000)
				printf("%d",a[i][j]);
			else if ((i==maxx) && (j==maxy))
				printf("*");
			else
				printf("~");
		}
		printf("\n");
	}
	return 0;
}
#include <iostream>
#include <vector>
#define reb pair< pair<int , int>, int>
#define ver1 first.first
#define ver2 first.second
#define mp make_pair
#define weight second
using namespace std;

int n,m;
reb g[10000];
const int inf = 1<<29;
int fordbelman(int x)
{
	int a[100];
	int b[100];
	for (int i=0;i<n;i++)
		a[i]=inf;
	a[x]=0;
	for (int i=0;i<n;i++)
		b[i]=inf;
	b[x]=0;
	for (int j=1;j<=n;j++)
	{
		for (int i=0;i<m;i++)
		{
			b[g[i].ver1]=min(a[g[i].ver2]+g[i].weight,b[g[i].ver1]);
		}
		if (b[x]<0)
			return j;
	    for (int i=0;i<n;i++)
	   	    a[i]=b[i];
	}
	return inf;
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d %d",&n,&m);
	int k=0;
	for (int i=0;i<m;i++)
	{
		int a,b,c,d;
		scanf("%d %d %d %d",&a,&b,&c,&d);
		g[k++]=mp(mp(--a,--b),-c);
		g[k++]=mp(mp(b,a),-d);
	}
	m=2*m;
	int res=inf;
	for (int i=0;i<n;i++)
		res=min(res,fordbelman(i));
	printf("%d",res==inf?0:res);

}
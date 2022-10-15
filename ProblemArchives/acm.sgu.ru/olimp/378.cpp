#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

char color[7500];
int size2sqr;
int x[7500];
int y[7500];
int n;
int q[7600];
int h,t;

int p[7500];


bool bfs(int v)
{
	q[t++]=v;
	color[v]=1;
	for (;h!=t;){
		int v=q[h++];
		for (int i=0;i<n;i++)
			if (i!=v && (x[i]-x[v])*(x[i]-x[v])+(y[i]-y[v])*(y[i]-y[v])<size2sqr)
			{
				if (color[i]==color[v])
					return false;
				if (color[i]==0){
					q[t++]=i;
					color[i]=3-color[v];
				}						
			}
	}
	return true;
}

inline bool bfsok() 
{
	h=t=0;
	random_shuffle(p,p+n);
	memset(color,0,sizeof(color));
	for (int i=0;i<n;i++)
		if (color[p[i]]==0)
			if (!bfs(p[i]))
				return false;
	return true;
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d",&n);
	int l=1;
	int r=0;
	for (int i=0;i<n;i++){
		scanf("%d %d",&x[i],&y[i]);
		p[i]=i;
	}
	for (int i=0;i<n;i++)
		for (int j=i;j<n;j++)
			r=max(r,(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
	++r;
	
	for (int i=0;i<10;i++){
		int a=rand()%n;
		int b=rand()%n;
		size2sqr=(x[a]-x[b])*(x[a]-x[b])+(y[a]-y[b])*(y[a]-y[b]);
		if (l<=size2sqr && size2sqr<=r)
			if (bfsok())
				l=size2sqr;
			else
				r=size2sqr;
	}
		
	for(;l!=r-1;)
	{
		size2sqr=(l+r)/2;
		if (bfsok())
			l=size2sqr;
		else
			r=size2sqr;
	}
	size2sqr=l;
	printf("%.10f\n",sqrt(((double)size2sqr))/2);
	bfsok();
	for (int i=0;i<n;i++)
		printf("%d ",color[i]);
	return 0;

}
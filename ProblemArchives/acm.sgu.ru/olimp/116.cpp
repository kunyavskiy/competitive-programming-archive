#include <iostream>

using namespace std;

int a[3][3];
bool de[3][3];
int n;
int upcolor(int x,int y)
{
	for (int i=x-1;i>=0;i--)
		if (a[i][y]!=0)
			return a[i][y];
	return 0;
}

int lfcolor(int x,int y)
{
	for (int i=y-1;i>=0;i--)
		if (a[x][i]!=0)
			return a[x][i];
	return 0;
}

long long per(int x,int y,int cs)
{
	if (y==3)
		return per(x+1,0,cs);
	if (x==3)
		return 1;
	if (!de[x][y])
		return per(x,y+1,cs);
	long long res=0;
	for (int i=1;i<=cs;i++)
		if ((upcolor(x,y)!=i) && (lfcolor(x,y)!=i))
		{
			a[x][y]=i;
			res+=per(x,y+1,cs);
		}
	if (cs<n)
	{
		a[x][y]=cs+1;
		res+=(per(x,y+1,cs+1)*(n-cs));
	}
	return res;
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d",&n);
	char c;
	for (int i=0;i<3;i++)
		for (int j=0;j<3;j++)
		{
			scanf(" %c ",&c);
			de[i][j]=(c=='x');
			a[i][j]=0;
		}
	printf("%I64d",per(0,0,0));
	return 0;
	
}
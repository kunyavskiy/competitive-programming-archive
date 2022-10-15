#include <vector>
#include <fstream>
#define forc(i,n) for(int i=1;i<=n;i++)
#define read(n) scanf("%d",&n);

using namespace std;

int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	int n;
	read(n);
	vector<bool> str(n+1);
	for (int i=1;i<=n;i++)
	{
		int a;
		read(a);
		str[i]=(a==1);
	}
	vector<int> kol(n+1);
	int kolwr=0;
	for (int i=0;i<=n;i++)
	{
		if ((i!=0) && !str[i])
			kolwr++;
		kol[i]=kolwr;
	}
	kolwr=0;
	for (int i=n;i>=0;i--)
	{
		if ((i!=n) &&  str[i+1])
			kolwr++;
		kol[i]+=kolwr;
	}
	int minval=1<<25;
	int minnum=0;
	int minkol=0;
	for(int i=0;i<=n;i++)
	{
		if (kol[i]==minval) 
			minkol++;
		if (kol[i]<minval)
		{
			minval=kol[i];
			minnum=i;
			minkol=1;
		}
	}
  printf("%d\n%d\n",minval,minkol);
  int i=minnum;
  for (int j=1;j<=n;j++)
			if ((j<=i) ^ str[j])
				printf("%d ",j);
	return 0;
}
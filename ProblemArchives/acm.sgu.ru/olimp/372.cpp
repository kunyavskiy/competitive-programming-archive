#include <vector>
#include <fstream>
#include <utility>
#define forc(i,n) for(int i=1;i<=n;i++)
#define read(n) scanf("%d",&n);

using namespace std;

int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	int n;
	read(n);
	vector<pair<int,int>> lic((n+3)/4+10),obr((n+3)/4+10);
	int k=0;
	for(int i=1;i<=(n+3)/4;i++)
	{
		lic[i].first=k!=n?++k:0;
		obr[i].first=k!=n?++k:0;
	}
	for(int i=(n+3)/4;i>=1;i--)
	{
		obr[i].second=k!=n?++k:0;
		lic[i].second=k!=n?++k:0;
	}
	for(int i=1;i<=(n+3)/4;i++)
	{
		if ((lic[i].second!=0)|| (lic[i].first!=0))
		   printf("%d 1 %d %d\n",i,lic[i].second,lic[i].first);
		if ((obr[i].second!=0)|| (obr[i].first!=0))
			printf("%d 2 %d %d\n",i,obr[i].first,obr[i].second);
	}
	return 0;
}
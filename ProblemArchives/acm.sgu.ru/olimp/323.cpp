#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	int t,n,k,m;
	scanf("%d %d %d %d",&t,&n,&k,&m);
	vector<int> sh,pe,ma;
	sh.resize(2*n+1);
	pe.resize(2*m+1);
	ma.resize(2*k+1);
	for (int i=1;i<=2*n;i++)
		 scanf("%d",&sh[i]);	
	for (int i=1;i<=2*k;i++)
		scanf("%d",&ma[i]);
	for (int i=1;i<=2*m;i++)
		 scanf("%d",&pe[i]);
	sort(sh.begin()+1,sh.end());
	sort(pe.begin()+1,pe.end());
	sort(ma.begin()+1,ma.end());
	int shp=1,pep=1,map=1;
	int tcd=0;
	bool shi=true,mai=true, peo=false;
	for (int i=1;i<=1000;i++)
	{
		if (shp<=2*n && shi)
		  if (sh[shp++]==i)
		    shi=shi^true;
		  else
		     shp--;      
		if (map<=2*k  && mai)
		if (ma[map++]==i)
			mai=mai^true;
		else
		   map--;
		if (pep<=2*m  && !peo)
		if (pe[pep++]==i)
			peo=peo^true;
		else
		   pep--;
		tcd=(shi && mai && peo)?tcd+1:0;
		if (tcd==t)
		{
			printf("%d",i-t+1);
			return 0;
		}
		if (shp<=2*n && !shi)
		  if (sh[shp++]==i)
		    shi=shi^true;
		  else
		     shp--;      
		if (map<=2*k  && !mai)
		if (ma[map++]==i)
			mai=mai^true;
		else
		   map--;
		if (pep<=2*m  && peo)
		if (pe[pep++]==i)
			peo=peo^true;
		else
		   pep--;
	}
	printf("NO");
	return 0;
}
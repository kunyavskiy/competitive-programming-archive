#include <fstream>
#include <vector>
#define read(n) scanf("%d",&n)
using namespace std;

int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	int n,i;
	vector<int> kol1(10000),kol2(10000);
	read(n);
	for(i=1;i<=n;i++)
	{
		int a,b;
		read(a);
		read(b);
		if (a!=b)
		  {
			   kol1[a]++;
			   kol1[b]++;
		  }
		else
		  {
			  kol1[a]++;
			  kol2[a]++;
		  }
	}
	int min1=0,min2=0;
	for(i=0;i<=9999;i++)
	  {
		  if (min1<kol1[i])
		    {
				min2=min1;
				min1=kol1[i];
		    }
		  else
		  if (min2<kol1[i])
		            min2=kol1[i];
      }
	int min3=0;
	for(i=0;i<=9999;i++)
		min3=max(min3,kol1[i]+kol2[i]);
    printf("%d",2*n-max(min3,min1+min2));
	return 0;
}
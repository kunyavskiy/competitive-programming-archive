#include <vector>
#include <fstream>
#define forc(i,n) for(int i=1;i<=n;i++)
#define read(n) scanf("%d",&n);

using namespace std;
int n;

int kol(int k)
{
	int res=0;
	forc(i,min(n,k))
       res+=min(n,k/i);
	return res;
}

int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	int k;
    read(n);
	read(k);
	int l=0,r=n*n,m=(l+r)/2;
	for (;r-l>1;m=(l+r)/2)
	  {
		  int t=kol(m);
		  if (t<k)
			  l=m;
		  else
		      r=m;
	  }
	printf("%d",r);
	return 0;
}
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
    int t;
	scanf("%d",&t);
	string yes="YES";
	string no="NO";
	int n,m,p;
	for (int l=1;l<t||l==t;l++)
	{
		scanf("%d", &n);
		scanf("%d", &m);
		scanf("%d", &p);
		if (n>m)
		{
			int t=n;
			n=m;
			m=t;
		}
		bool q=false;
		for (int i=1;i*i<=p;i++)
          q=q||((p%i==0) && (i<=n) && (p/i<=m));
		if (q==true) printf("Yes\n");
		if (q==false) printf("No\n");
		
	}
  return 0;
}
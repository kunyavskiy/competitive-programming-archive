#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int min(int a,int b)
{
	return a<b?a:b;

}
int main()
{
    freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	int n,s;
    scanf("%d %d\n",&n,&s);
	vector<int> to(1001);
	vector<int> tn(1001);
	int i;
	for (i=0;i<=s;i++)
	   to[i]=0;
	for (int l=1; l<=n;l++)
	{		
		int t1,t2,t3,c1,c2,c3;
		scanf ("%d %d %d %d %d %d\n",&c1,&t1,&c2,&t2,&c3,&t3);
		for (i=0;i<=s;i++)
		{
			if (i>0)
				tn[i]=tn[i-1];
			else tn[i]=100000000;
			if ((c1>-1) && (c1<=i))
		      tn[i]=min(to[i-c1]+t1,tn[i]);
	        if ((c2>-1) && (c2<=i))
		      tn[i]=min(to[i-c2]+t2,tn[i]);
            if ((c3>-1) && (c3<=i))
		      tn[i]=min(to[i-c3]+t3,tn[i]);

		}
      to=tn;
	}
  int r=10000000;
  for (i=0;i<=s;i++)
     r=min(r,tn[i]);
  if (r==10000000)
	  printf("-1");
  else  printf("%d",r);
  return 0;
}
#include <vector>
#include <fstream>
#include <algorithm>
#define forc(i,n) for(int i=1;i<=n;i++)
#define read(n) scanf("%d",&n);

using namespace std;

struct euclidres{
	       int x,y;
                };


euclidres make(int a, int b)
{
	euclidres res;
	res.x=a;
	res.y=b;
	return res;
}
euclidres euclid(int a, int b)
{
	if (b==0)
		 return make(1,0);
	euclidres res1=euclid(b,a%b);
	return make(res1.y,res1.x-(a/b)*res1.y);
}
int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	int n,p;
	read(n);
	if (n==2)
	  {
		  printf("1 1");
		  return 0;
	}
	read(p);
	bool q=false,q1=false;
	int fn0;
	vector<int> a(n+1);
	forc(i,n)
	{
		read(a[i]);
		if (q && (a[i]==0)) 
		{
			q1=true;     
		}
		if (a[i]!=0)
			fn0=i;
		q=(a[i]==0);
	}
	if (q1)
	{
		printf("%d 1",fn0);
		return 0;
	}
	euclidres obr=(euclid(a[2],p));
	int k1=((obr.x));
	for (;k1<0;k1+=p);
	for (;k1>=p;k1-=p);
	k1=(k1*a[3])%p;

	q=true;
	int t=(a[3]*k1)%p;
	for (int i=4;i<=n;i++,t=(t*k1)%p)
		q=q && (a[i]==t);
    if (q)
	  {
		  printf("1 %d",k1);
		  return 0;
	  }


	obr=(euclid(a[1],p));
    k1=((obr.x));
	for (;k1<0;k1+=p);
	for (;k1>=p;k1-=p);
	k1=(k1*a[3])%p;
	 q=true;
	 t=(a[3]*k1)%p;
	for (int i=4;i<=n;i++,t=(t*k1)%p)
		q=q && (a[i]==t);
    if (q)
	  {
		  printf("2 %d",k1);
		  return 0;
	  }
    

	obr=(euclid(a[1],p));
	 k1=((obr.x));
	for (;k1<0;k1+=p);
	for (;k1>=p;k1-=p);
	k1=(k1*a[2])%p;
	 q=true;
	 t=(a[2]*k1)%p;
	for (int i=3;i<=n;i++,t=(t*k1)%p)
		 if (a[i]!=t)
		  {
		    printf("%d %d",i,k1);
		    return 0;
	      }
}
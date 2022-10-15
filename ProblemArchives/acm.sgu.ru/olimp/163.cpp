#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;


int min(int a, int b)
{
	return a<b?a:b;
}
int main()
{
    freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
    vector<int> a(30),b(30);
	int i;
	vector<int> t(16000,100000000);
	for (i=1;i<=9;i++)
	{
		a[i] = i;
        b[i] = 1;
	}
	for (i=1;i<=9;i++)
	{
		a[i+9] = i*i;
        b[i+9] = 3;
	}
	for (i=1;i<=9;i++)
	{
		a[i+18] = i*i*i;
        b[i+18] = 3;
	}
	int n;
	scanf("%d",&n);
	t[0]=-1;
	for (i=1;i<=n;i++)
       for (int j=1;j<=27;j++)
		   if (i-a[j]>=0)
			   t[i]=min(t[i],t[i-a[j]]+b[j]+1); 
	printf("%d",t[n]);
     return 0;
}
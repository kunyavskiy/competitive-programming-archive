#include <iostream>
#include <vector>
using namespace std;

const int grandy[7]={0,0,1,1,2,2,3};

int grandyf(int a)
{
	return grandy[a%7];
}

int main()
{
//	freopen("input.txt","r",stdin);
//	freopen("output.txt","w",stdout);
	int t;
	scanf("%d",&t);
	for (;t>0;t--)
	{
		int n;
		scanf("%d",&n);
		vector<int> a(n);
		int res=0;
		for (int i=0;i<n;i++)
		{
			scanf("%d",&a[i]);
			res=res^grandyf(a[i]);
		}
		if (res==0)
			printf("Robert wins.\n");
		else
		{
			bool q=false;
			printf("Julia wins.\n");
			for (int i=0;i<n;i++)
				if ((a[i]>=5) && ((grandyf(a[i])^grandyf(a[i]-5))==res))
				{
					q=true;
					printf("Take 5 sticks from heap number %d.\n",i+1);
					break;
				}
			if (!q)
			for (int i=0;i<n;i++)
				if ((a[i]>=3) && ((grandyf(a[i])^grandyf(a[i]-3))==res))
				{
					q=true;
					printf("Take 3 sticks from heap number %d.\n",i+1);
					break;
				}
			if (!q)
			for (int i=0;i<n;i++)
				if ((a[i]>=2) && ((grandyf(a[i])^grandyf(a[i]-2))==res))
				{
					q=true;
					printf("Take 2 sticks from heap number %d.\n",i+1);
					break;
				}
		}
		if (t!=1)
			printf("\n");


	}
}
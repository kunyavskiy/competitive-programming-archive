#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	int n;
	scanf("%d",&n);
	vector<int> a(n);
	vector<int> after(n);
	for (int i=0;i<n;i++)
		scanf("%d",&a[i]);
	sort(a.begin(),a.end());
	after[n-1]=1;
	for (int i=n-2;i>=0;i--)
		after[i]=(a[i]==a[i+1])?after[i+1]+1:1;
   long long  res=0;
	for (int i=0;i<n;i++)
	{
		int k=0;
		for (int j=0;j<n;j+=after[j])
		{
			for (;(k<n)&& (a[j]+a[i]>a[k]);k++);
			if (k==n)
				break;
			for (;(k<n)&& (a[i]+a[j]==a[k]);k++)
			if (k!=i)
			{
				res+=after[j];
				if ((k>=j) && (k<(j+after[j])))
					res--;
                if ((i>=j) && (i<(j+after[j])))
					res-- ; 
			}
		}
	}
	printf("%d",res);
	return 0;
}
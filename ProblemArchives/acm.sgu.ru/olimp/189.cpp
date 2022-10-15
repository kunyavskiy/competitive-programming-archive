#include <vector>
#include <iostream>
#include <fstream>
using namespace std;


vector<int> operator* (vector<int> a,int b)
{
	int asz=a.size();
	vector<int> res(asz+10);
	int c=0;
	for (int i=0;i<asz;i++)
	{
		c+=a[i]*b;
		res[i]=c%10000;
		c/=10000;
	}
	for (int i=asz;c>0;i++,c/=10000)
		res[i]=c%10000;
	for (;(res.size()!=0) && (res[res.size()-1]==0);res.pop_back());
	return res;
}

void print(vector<int> a,int zn)
{
	for (;(a.size()!=0) && (a[a.size()-1]==0);a.pop_back());
	if (a.size()==0)
	{
		printf("0");
		return;
	}
	if (zn==-1)
		printf("-");
	printf("%d",a[a.size()-1]);
	for (int i=a.size()-2;i>=0;i--)
		printf("%04d",a[i]);
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n;
	scanf("%d",&n);
	int a[1000];
	for (int i=0;i<n;i++)
		scanf("%d",&a[i]);
	vector<int> res;
	res.push_back(1);
	int zn=1;
	for (int i=0;i<n;i++)
		for (int j=i+1;j<n;j++)
		{
			if (a[j]<a[i])
				zn=-zn;
			res=res*abs(a[j]-a[i]);
		}
	print(res,zn);
	return 0;

}
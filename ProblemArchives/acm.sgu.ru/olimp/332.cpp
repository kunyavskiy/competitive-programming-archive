#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	int x1,x2,y1,y2,dx,dy;
	scanf("%d %d %d %d %d %d",&x1,&y1,&x2,&y2,&dx,&dy);
	dx%=x2;
	dy%=y2;
	vector<int> xs,ys,sizes;
	for (int i=0;i<x1;i++)
	{
		xs.push_back(dx);
		dx+=x2;
	};
	xs.push_back(dx);
	dx=0;
	for (int i=0;i<x2;i++)
	{
		xs.push_back(dx);
		dx+=x1;
	};
	xs.push_back(dx);
	sort(xs.begin(),xs.end());
	for (int i=xs.size()-1;i>0;i--)
		xs[i]-=xs[i-1];

	for (int i=0;i<y1;i++)
	{
		ys.push_back(dy);
		dy+=y2;
	};
	ys.push_back(dy);
	dy=0;
	for (int i=0;i<y2;i++)
	{
		ys.push_back(dy);
		dy+=y1;
	};
	ys.push_back(dy);
	sort(ys.begin(),ys.end());	
	for (int i=ys.size()-1;i>0;i--)
		ys[i]-=ys[i-1];

	for (int i=0;i<xs.size();i++)
		for (int j=0;j<ys.size();j++)
			sizes.push_back(xs[i]*ys[j]);

	set<int> a;
	for (int i=0;i<sizes.size();i++)
		if (sizes[i]!=0)
			a.insert(sizes[i]);
	printf("%d\n",a.size());
		for (set<int>::iterator iter=a.begin();iter!=a.end();iter++)
			printf("%d\n",*iter);
}
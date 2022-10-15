#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;
vector<int> p;

int root(int a)
{
	return p[a]==a?a:p[a]=root(p[a]);
}

bool uni(int a,int b)
{
	a=root(a);
	b=root(b);
	if ((a!=b))
	{
		if (rand()%2==0)
			p[a]=b;
		else p[b]=a;
		return true;
	}
	else
	{
		return false;

	}
}
int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	int n,m;
	scanf("%d %d\n",&n,&m);
	int ans1=0;
	string ans2="",ans3="";
	p.resize(n);
	for (int i=0;i<n;i++)
		p[i]=i;
	map<string,int>  towns;
	int kol=1;
	for (int i=0;i<m;i++)
	{
		string s1,s2;
		cin>>s1>>s2;
		if (!uni(towns[s1]==0?(towns[s1]=kol++)-1:towns[s1]-1,towns[s2]==0?(towns[s2]=kol++)-1:towns[s2]-1))
		{
			ans2=s1;
			ans3=s2;
		};
	}
	for (int i=0;i<n;i++)
		if (p[i]==i)
			ans1++;
	if (ans1!=1)
		printf("No\n%d\n",ans1-1);
	else
	    printf("Yes\n\n");
	if (ans2!="")
		printf("No\n%s %s\n",ans2.data(),ans3.data());
	else
		 printf("Yes\n\n");

}
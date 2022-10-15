#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

void norm (string &a)
{
	sort(a.begin(),a.end());
	if (a[a.size()-1]=='0')
	{
		a[0]='6';
		return;
	}
	int i=0;
	if (a[0]=='0')
	{
	for (;a[i]=='0';i++);
	if (a[i]=='8')
		a[0]='6';
	else
	{
	char t=a[0];
	a[0]=a[i];
	a[i]=t;
	}
	}
}


bool operator< (string &a,string &b)
{
	norm(a);
	norm(b);
	if (a.length()!=b.length())
		return a.length()<b.length();
	else
	{
		for (int i=0;i<a.length();i++)
			if (a[i]!=b[i])
				return a[i]<b[i];
		return false;
	}
}

bool operator>(string &a,string &b)
{
	return !(a<b);
}

int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	//for (int n=1;n<=128;n++)
	//{
	vector<string> a;
	int n;
	scanf("%d",&n);
	const string st[3]={"1","2",""};
	const int cost[3]={2,5,0};
	for (int start=0;start<3;start++)
	{
		string s="000000", s1="";
		int spich=cost[start]+6*s.size();
		for (;s.length()!=0;s.erase(s.begin()))
		{
				for (;spich<=n;spich+=7)
					s1+="8";
				a.push_back(st[start]+s+s1);
				spich-=6;
		}
		for (;spich<=n;spich+=7)
			s1+="8";
		a.push_back(st[start]+s+s1);
	}
	string min="88888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888";
	for (int i=0;i<a.size();i++)
		if (min>a[i])
			min=a[i];
	printf("%s\n",min.data());
	//}
	return 0;
}
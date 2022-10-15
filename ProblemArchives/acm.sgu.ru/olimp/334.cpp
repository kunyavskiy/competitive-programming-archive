#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#define ll long long
#define vll vector<ll>

using namespace std;
const ll base=100000000000000000;
vector<vll> f;

vll operator+(vll a,vll b)
{
	int l1=a.size(),l2=b.size(),l=max(l1,l2);
	vll res (l);
	ll ost=0;
	for (int i=0;i<l;i++)
	{
		if (i<l1)
			ost+=a[i];
	    if (i<l2)
			ost+=b[i];
		res[i]=ost%base;
		ost/=base;
	};
	if (ost!=0)
		res.push_back(ost);
	return res;	
}

vll operator- (vll a,vll b)
{
  vll res;
  ll ost=0;
  for (int i=0;i<a.size();i++)
  {
	  ost=ost+a[i]-(b.size()>i?b[i]:0);
	  res.push_back((ost+base)%base);
	  ost=(ost<0?-1:0);
  }
  for (;(res[res.size()-1]==0) && (res.size()!=1) ;res.pop_back());
  return res;
}

bool operator<= (vll a,vll b)
{
	if (a.size()!=b.size())
		return a.size()<b.size();
	for (int i=a.size()-1;i>=0;i--)
		if (a[i]!=b[i])
			return a[i]<b[i];
	return true;
}

bool operator >(vll a,vll b)
{
	return !(a<=b);
}

void fib(int n)
{
   vll a;
   a.push_back(1);
   f.push_back(a);
   a[0]=2;
   f.push_back(a);
   for (int i=2;i<n;i++)
   f.push_back(f[i-1]+f[i-2]);
}

vll fibtoint (string s)
{
	vll res;
	for (int i=0;i<s.length();i++)
	if (s[i]=='1')
	{
		res=res+f[s.length()-i-1];       
	}
	return res;
}

string inttofib (vll a)
{
	string res;
	for (int i=f.size()-1;i>=0;i--)
		if ((f[i]>a))
		{
			if (res.length()!=0)
			  res=res+'0';
		}
		else
		{
			res=res+'1';
            a=a-f[i];
		};
	if (res.length()==0)
		res='0';
	return res;
}
int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	string s,s1;
	getline(cin,s);
	getline(cin,s1);
	fib(max(s.length(),s1.length())+10);
	vll a1=fibtoint(s),a2=fibtoint(s1);
	s=inttofib(a1+a2);
	printf("%s",s.data());     
}
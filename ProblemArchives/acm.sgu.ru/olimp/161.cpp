#include <vector>
#include <fstream>
#include <iostream>
#include <utility>
#define mp make_pair
#define base 10000
#define outform "%04d"

using namespace std;


vector<pair<int,int>> prost;
void erotosfen(int n)
{
	vector<int> a(n+1);
	for (int i=2;i<=n;i++)
	{
		if (a[i]==0)
		{
			pair<int,int> tup;
			tup.first=i;
			tup.second=0;
			prost.push_back(tup);
			a[i]=i;
		}
		for (int j=0;(j<prost.size()) && (i*prost[j].first<=n) && (prost[j].first<=a[i]);j++)
			a[i*prost[j].first]=prost[j].first;
	}
}

vector<int> operator* (vector<int> a,int b)
{
	int l=a.size();
	vector<int> res(l+5);
	int ost=0,i;
	for (i=0;i<l;i++)
	{
		ost+=a[i]*b;
		res[i]=ost%base;
		ost/=base;
	}
	//i++;
	for (;ost!=0;i++,ost/=base)
		res[i]=ost%base;
	for (i=res.size()-1;res[i]==0;i--)
		res.pop_back();
	return res;
}

vector<int> operator* (int b,vector<int> a)
{
	return a*b;
}


vector<int> operator+(vector<int> a,vector<int> b)
{
	int l1=a.size(),l2=b.size(),l=max(l1,l2);
	vector<int> res (l);
	int ost=0;
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


vector<int> operator*(vector<int> a,vector<int> b)
{
	int l1=a.size();
	int l2=b.size();
	vector<int> res(l1+l2+10);
	for (int i=0;i<l1;i++)
		for (int j=0;j<l2;j++)
		{
			res[i+j]+=a[i]*b[j];
			res[i+j+1]+=res[i+j]/base;
			res[i+j]%=base;
		}
	for (;res[res.size()-1]==0;res.pop_back());
	return res;
}

void nullprost()
{
	for(int i=0;i<prost.size();i++)
		prost[i].second=0;
}

void rasl(int a,int sign)
{
	for (int i=0;i<prost.size();i++)
		for (int j=prost[i].first ;j<=a;j*=prost[i].first)
			prost[i].second+=(sign*(a/j));
}

vector<int> sochet(int n,int k)
{
	if (n<k)
	{
		vector<int> res;
		res.push_back(0);
		return res;
	}
	if (k==0)
	{
		vector<int> res;
			res.push_back(1);
		return res;
	}
	nullprost();
	rasl(n,1);
	rasl(k,-1);
	rasl(n-k,-1);
	vector<int> res;
	res.push_back(1);
	for (int i=0;i<prost.size();i++)
		for(int j=0;j<prost[i].second;j++)
			res=res*prost[i].first;
	return res;
}

void print(vector<int> a)
{
	int l=a.size()-1;

	if (a[a.size()-1]==0)
		for (;1;);
	

	printf("%d",a[a.size()-1]);
	l--;
	for (int i=l;i>=0;i--)
	{
		printf(outform,a[i]);
	}
	return;
}
int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	int p,q,k;
	scanf("%d %d %d",&p,&q,&k);
	erotosfen(max(p,q));
	vector<int> res=(sochet(p-1,k-1)+sochet(p-1,k))*(sochet(q-1,k-1)+sochet(q-1,k));
	print(res);
}
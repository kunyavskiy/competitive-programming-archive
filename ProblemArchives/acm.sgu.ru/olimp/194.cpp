#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <queue>
#include <memory.h>
#include <stack>
#define mp make_pair
#define pb push_back                     
#define int64 long long
#define ld long double  
#define setval(a,v) memset(a,v,sizeof(a))
using namespace std;

int x[50];
int y[50];
int n;

ld dest(ld X,ld Y)
{
	ld res=0;
	for (int i=0;i<n;i++)
		res+=sqrt((x[i]-X)*(x[i]-X)+(y[i]-Y)*(y[i]-Y));
	return res;
}

ld triny(ld X)
{
	ld l=-20000;
	ld r=20000;
	for (;r-l>1E-08;)
	{
		ld y1=l+(r-l)/3;
		ld y2=r-(r-l)/3;
		ld f1=dest(X,y1);
		ld f2=dest(X,y2);
		if (f1<f2)
			r=y2;
		else
			l=y1;
	}
	return (l+r)/2;
}


ld trinx()
{
	ld l=-20000;
	ld r=20000;
	for (;r-l>1E-08;)
	{
		ld x1=l+(r-l)/3;
		ld x2=r-(r-l)/3;
		ld f1=dest(x1,triny(x1));
		ld f2=dest(x2,triny(x2));
		if (f1<f2)
			r=x2;
		else
			l=x1;
	}
	return (l+r)/2;
}


int main()
{                        
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
  cin>>n;
  for (int i=0;i<n;i++)
  	cin>>x[i]>>y[i];
  ld x=trinx();
  ld y=triny(x);
  cout<<fixed;
  cout.precision(15);
  cout<<x<<" "<<y<<endl;
  return 0;
}
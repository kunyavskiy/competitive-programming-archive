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
#define setval(a,v) memset(a,v,sizeof(a))

using namespace std;

typedef double ld;                              

struct myless{
	bool operator()(ld a,ld b)
	{
		return a-b>1E-09;
	}
};

typedef set<ld,myless> myset;

void mult(set<ld,myless>& a,const set<ld,myless> &b,set<ld,myless>& res)
{
	for (set<ld,myless>::iterator iter=a.begin();iter!=a.end();++iter)
		for (set<ld,myless>::iterator jiter=b.begin();jiter!=b.end();++jiter)
		{
			ld r1=*iter;
			ld r2=*jiter;			
			res.insert(r1+r2);
			res.insert((r1*r2)/(r1+r2));
		}
	return;
}

set<ld,myless> res[128];

int main()
{                        
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
  int n;
  scanf("%d",&n);  
	ld to;
	ld close=0;
	cin>>to;
  for (int i=0;i<n;i++)
  	{
  		ld a;
  		cin>>a;
  		res[1<<i].insert(a);
  	}
  for (int i=0;i<(1<<n);i++)
  	for (int j=i;j;j=(j-1)&i)
  	{
  	  if (j!=i && ((i&(~j))<j))
	 			mult(res[j],res[i&(~j)],res[i]);
	 	}
	for (int i=0;i<(1<<n);++i)
		for (set<ld,myless>::iterator iter=res[i].begin();iter!=res[i].end();++iter)
		{
			if (abs(*iter-to)<abs(close-to))
				close=*iter;
		}
	cout<<fixed;
	cout.precision(15);
	cout<<close<<endl;
  return 0;
}
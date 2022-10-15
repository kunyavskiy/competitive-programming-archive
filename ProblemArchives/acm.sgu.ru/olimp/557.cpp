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

int d[1000];
vector<int> len;
int n,m;


bool check(multiset<int>& a)
{
	multiset<int>::iterator iter=a.begin();
	int ptr=0;
	for (;iter!=a.end();++iter)
	{               
		for (;len[ptr]<*iter && ptr<m;++ptr);
		if (ptr==m)
			return false;
		ptr++;			
	}
	return true;
}

int main()
{                        
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
  scanf("%d %d",&n,&m);
  for (int i=0;i<n;i++)
  	scanf("%d",&d[i]);
  len.resize(m);
	for (int i=0;i<m;i++)
		scanf("%d",&len[i]);
	sort(len.begin(),len.end());
	multiset<int> a;
	int l=0;
	int r=0;          
	int ans=0;
	int lans=-1,rans=-1;
	for (;;)
	{
		r++;                                
		if (r==n)
			break;                        
		a.insert(d[r]-d[r-1]);
		for (;check(a)==false && l<r;)
		{       
			l++;  
			a.erase(d[l]-d[l-1]);
		}
		if (ans<d[r]-d[l])
			ans=d[rans=r]-d[lans=l];
	}                           
	if (lans==-1 || rans==-1)
		lans=rans=1;
  printf("%d %d\n",lans+1,rans+1);
 	return 0;
}
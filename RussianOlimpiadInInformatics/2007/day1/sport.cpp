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

int a[100000];

int main()
{
  freopen("sport.in","r",stdin);
  freopen("sport.out","w",stdout);
	int n,p,k;
	scanf("%d %d %d",&n,&p,&k);
	--p;
	for (int i=0;i<n;i++)
		scanf("%d",&a[i]);
	int slb=0;
	for (int i=0;i<p;i++)
		if (a[i]<=a[p])
			slb++;
	//cerr<<slb<<endl;
	int it=p-slb;
	int pos=slb+1;
	set<int> kol;
	for (int i=p+1;i<n;i++)
		if (a[i]<a[p])
			kol.insert(i-p);
	string ans;
	for (int i=0;i<it;i++)
		ans+='-';
	for (int i=1;it<n-1-k;it++,i++)
		{
			ans+='-';
			while (!kol.empty() && *kol.begin()<=i)
				{
					kol.erase(kol.begin());
					pos++;
					i++;
				}				
		}
  for (;it<n-1;it++)
  	ans+='+';
  printf("%d\n%s\n",pos,ans.data());
  return 0;
}
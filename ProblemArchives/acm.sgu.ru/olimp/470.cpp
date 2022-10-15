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

int a[110];
bool t[110];
int n;

bool check(int delt){
	t[0]=true;
	for (int i=1;i<=n;i++)
	{
		t[i]=false;
		for (int j=i-1;j>0 && a[i]-a[j]<=delt;--j)
			if (t[j-1])
				{
					t[i]=true;
					break;
				}
	}
	return t[n]==true;
}

int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	int l=-1;
	int r=1000000100;
	for (;r-l>1;){
		int m=(l*1ll+r)/2;
		if (check(m))
			r=m;
		else
			l=m;
	}
	printf("%d\n",r);
	return 0;
}
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

int a[100];
int n;

set<int64> sums

int64 per(int l,int k){
	if (l==n)
		{
			if (check())
				return 1;
			return 0;
		}
	int64 res=0;
	for (int i=0;i<=k;i++)
		{
			a[l]=i;
			res+=per(l+1,k);
		}
	return res;
}

int main()
{
	int k;
	scanf("%d %d",&n,&k);
	cout<<per(0,k)<<endl;
	return 0;
}
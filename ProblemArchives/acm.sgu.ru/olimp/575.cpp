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

bool cmp(const pair<int,int>& a,const pair<int,int>& b){
	return a.first*b.second < b.first* a.second;
}

int gcd(int a,int b){
	if (b==0) return a;
	return gcd(b,a%b);
}

pair<int,int> a[500*500];

int main()
{                        
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	int cnt = 0;
	int n;
	cin>>n;
	for (int i=0;i<=n;i++)
		for (int j=i;j<=n;j++)
			if (gcd(i,j)==1)
				a[cnt++]=mp(i,j);
	sort(a,a+cnt,cmp);
	printf("%d\n",cnt);
	for (int i=0;i<cnt;i++)
		printf("%d %d\n",a[i].first,a[i].second);			
    return 0;
}
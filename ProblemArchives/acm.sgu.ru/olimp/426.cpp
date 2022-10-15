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

int a[51000];


void solve(int l,int r){
	if (l==r-1){
		a[l]=0;
		return;
	}
	if (l == r-2){
		a[l]=0;
		a[l+1]=1;
		return;
	}
	int m=(l+r)/2;
	solve(l,m);
	solve(m,r);
	for (int i=l;i<m;i++)
		a[i]=a[i]*2+1;
	for (int i=m;i<r;i++)
		a[i]=a[i]*2;	
}

int main()
{                        
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	int n;
	cin>>n;
	solve(0,n);
	for (int i=0;i<n;i++)
		printf("%d ",a[i]);	
	printf("\n");
    return 0;
}
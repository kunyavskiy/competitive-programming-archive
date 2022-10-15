#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <deque>
#include <stack>
#include <algorithm>
#include <memory.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iterator>

#define mp make_pair
#define pb push_back

#ifdef LOCAL
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

#define taskname "crisis"

using namespace std;

typedef long long int64;
typedef long double ld;

int a[11000];
int b[11000];
bool used[12000];

int gcd(int a,int b){
	while (a && b){
		swap(a,b);
		b%=a;
	}
	return a+b;
}

void solve(){
	int n,m;
	scanf("%d %d",&n,&m);
	int ptr=0;
	for (int i=0;i<n;i++)
		scanf("%d",&a[i]);
	for (int j=0;j<m;j++)
		scanf("%d",&b[j]);
	sort(a,a+n);
	sort(b,b+m);
	if (a[0]>b[m-1] || b[0]>a[n-1]){
		printf("NO\n");
		return;
	}
	bool q1,q2;
	q1=q2=true;
	int g=0;
	int tmp;
	for (int i=0;i<n;i++){
		if (g!=0 && i!=0 && a[i]%g==a[0]%g)
			continue;
		for (int j=0;j<m && g!=1;j++){
			tmp=a[i]-b[j];
			g=gcd(g,abs(tmp));
		}		
	}
	if (g>=11000 || g==0 || !q1 || !q2){
		printf("NO\n");
		return;
	}
	for (int i=1;i<g;i++)
		used[i]=0;
	for (int i=0;i<n;i++)
		used[a[i]%g]=true;
//	for (int i=0;i<m;i++)
//		used[g-b[i]%g]=true;
	for (int i=1;i<g;i++)
		if (!used[i]){
			printf("NO\n");
			return;
		}
	printf("YES\n");
}

int main(){
	#ifndef taskname
		#error taskname is not defined
	#else
		freopen(taskname".in","r",stdin);
		freopen(taskname".out","w",stdout);
	#endif
	int t;
	scanf("%d",&t);
	for (;t;--t)
		solve();
	return 0;
} 
#ifndef LOCAL
    #pragma comment(linker, "/STACK:33554432")
#endif

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
#define setval(a,v) memset(a,v,sizeof(a))

#ifndef M_PI
	#define M_PI 3.1415926535897932384626433832795
#endif


#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;


struct comp{
	int x;
	comp(int x):x(x){
	}
    bool operator()(int a){
    	return x < a;
    }

};

int a[3100];

void solve(int l,int r){
	if (l >= r - 1)
		return;
	int mid = stable_partition(a+l,a+r-1,comp(a[r-1])) - a;
	solve(l,mid);
	solve(mid,r-1);
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	int n;
	scanf("%d",&n);
	for (int i = 0; i < n; i++)
		scanf("%d",&a[i]);

	solve(0,n); 

	for (int i = 0; i < n; i++)
		printf("%d ",a[i]);
  return 0;
}
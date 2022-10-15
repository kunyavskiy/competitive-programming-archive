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

int a[20000];

int up(int a,int b){
	int c = a/b;
	while (c*b < a)
		c++;
	return c;
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  	int n,m;
  	scanf("%d %d",&n,&m);

  	for (int i = 0; i < n+m-1; i++)
  		scanf("%d",&a[i]);

  	int cur = 0;

  	for (int i = 0; i < n; i++){
  		int x = -(1<<30);
  		for (int j = 0; j < m; j++)
  			x = max(x,up(a[i+j]-cur,j+1));
  		cur += x;
  		cout << x << " \n"[i==n-1];;
  	}                     
  return 0;
}
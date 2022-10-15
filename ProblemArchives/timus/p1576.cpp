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

#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	int n1,c1;
	int n2,c2,t2;
	int n3;
	cin >> n1 >> c1 >> n2 >> t2 >> c2 >> n3;

	int t = 0;
	int m;
	scanf("%d",&m);

	for (int i = 0; i < m; i++){
		int a,b;
		scanf("%d:%d",&a,&b);
		if (a || b>6)
			t += a + !!b;
	}

	printf("Basic:     %d\n",n1 + c1*t);
	printf("Combined:  %d\n",n2 + c2*max(0,t-t2));
	printf("Unlimited: %d\n",n3);
	  
	return 0;
}
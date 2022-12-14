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

#if ( _WIN32 || __WIN32__ )
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

using namespace std;

typedef long long int64;
typedef long double ld;

int a[110000];
int n;

void check(int x){
	if (n/x < 3)
		return;
	for (int i=0;i<x;i++){
		bool q = true;
		for (int j = i;j<n;j+=x)
			q &= a[j];
		if (q){
			printf("YES\n");
			exit(0);
		}
	}
}

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	scanf("%d",&n);
	for (int i=0;i<n;i++)
		scanf("%d",&a[i]);
	for (int i=1;i*i<=n;i++)
		if (n%i == 0){
			check(i);
			check(n/i);
		}
	printf("NO\n");
	return 0;
}
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

typedef long long ll;
typedef long double ld;

int n;
int a[110];

void solve(){
	scanf("%d",&n);
	for (int i = 0; i < n; i++)
		scanf("%d",&a[i]);

	for (int j = 0; j < n; j++){
		for (int k = 0; k < j-1; k++)
			if (a[k] > a[j]){
				printf("NO\n");
				return;
			}
	}
	printf("YES\n");
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    int t;
    scanf("%d",&t);

    while (t-->0)
    	solve();

  return 0;
}
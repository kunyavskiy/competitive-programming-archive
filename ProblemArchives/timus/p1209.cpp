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

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	int n;
	scanf("%d",&n);
	for (int i = 0; i < n; i++){
		ll k;
		scanf(LLD,&k);
		--k;
		ll x = ll((-1 + sqrt(1 + 8.0*ld(k)))/ 2.0);
		ll x2 = x;
		for (; (x+1)*(x+2) <= 2*k; x++);
		for (; x * (x+1) > 2*k; x--);

/*		if (abs(x2-x) > 10)
			cerr << x2 <<" "<<x <<" "<<k << endl;
		assert (abs(x2 - x) < 10);*/
		if (x * (x+1) == 2*k)
			printf("1\n");
		else
			printf("0\n");
	}
  return 0;
}
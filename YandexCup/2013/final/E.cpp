//#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <cstdlib>
#include <cstdio>
#include <iterator>
#include <functional>
#include <bitset>
#define mp make_pair
#define pb push_back

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "E"

typedef long long ll;
typedef long double ld;


int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif

    int n;
    scanf("%d",&n);
    if (n <= 2){
    	puts("Impossible");
    	return 0;
    }
    if (n == 3){
    	printf("2 2 2\n3 3\n2\n3\n");
    	return 0;
    }
    assert(n != 4);

    int x = n - 2;
    vector<ll> a,b,c,d;
    for (int i = 0; i < x; i++)
    	a.pb(2);
    if (x <= 50){
		a.pb((1LL<<(x-1)) - 1);
	    a.pb(2);
		
		b.pb((1LL<<x) - 1);
		b.pb((1LL<<x) - 1);

		c.pb((1LL<<(x-1)) - 1);
		c.pb(2);

		d.pb((1LL<<x) - 1);
	} else {
	    if (x % 2 == 0){
	    	assert(false);
		} else {
			assert(false);
		}
	}

    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    sort(c.begin(),c.end());
    sort(d.begin(),d.end());

    for (int i = 0; i < (int)a.size(); i++)
    	printf(LLD" ",a[i]);
    printf("\n");
    for (int i = 0; i < (int)b.size(); i++)
    	printf(LLD" ",b[i]);
    printf("\n");
    for (int i = 0; i < (int)c.size(); i++)
    	printf(LLD" ",c[i]);
    printf("\n");
    for (int i = 0; i < (int)d.size(); i++)
    	printf(LLD" ",d[i]);
    printf("\n");

      
    TIMESTAMP(end);
    return 0;
}
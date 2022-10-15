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

#define TASKNAME "1279"

typedef long long ll;
typedef long double ld;

int a[10010];


int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif

  	int n,m,k;
  	scanf("%d %d %d",&n,&m,&k);
  	n *= m;

  	for (int i = 0; i < n; i++){
  		scanf("%d",&a[i]);
  	}

  	sort(a,a+n);
  	a[n] = 1e9;
  	int sum = 0;

    for (int i = 0; i < n; i++){
    	sum += a[i];
    	int can = a[i+1] * (i+1) - sum;
    	if (can > k){
    		printf("%d\n", (k + sum) / (i + 1));
    		return 0;
    	}
    } 
    assert(false);
    TIMESTAMP(end);
    return 0;
}
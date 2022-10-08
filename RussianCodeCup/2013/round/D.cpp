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

#define TASKNAME "D"

typedef long long ll;
typedef long double ld;


void bitprint(int x,int n){
	static int last = -1;
	assert(last == -1 || __builtin_popcount(last ^ x) <= 2);
	last = x;
	for (int i = 0; i < n; i++)
		printf("%d",!!(x & (1<<i)));
	printf("\n");
}

int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif
  	int n;
  	scanf("%d",&n);

  	for (int i = n; i >= 0; i--){
  		for (int j = 0; j < (1<<n); j++)
  			if (__builtin_popcount(j ^ (j>>1)) == i)
  				bitprint(j ^ (j>>1),n);
  	}
      
  TIMESTAMP(end);
  return 0;
}
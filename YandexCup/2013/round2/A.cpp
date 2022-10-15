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

#define TASKNAME "A"

typedef long long ll;
typedef long double ld;


int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif
  	int sum, cnt1, cnt2, n;
  	sum = cnt1 = cnt2 =  n = 0;
  	assert(scanf("%d",&n) == 1);
  	assert(n >= 2);


  	vector<int> v;

  	for (int i = 0; i < n; i++){
  		int a;
  		assert(scanf("%d",&a) == 1);
  		assert(1 <= a && a <= n-1);
  		sum += a;
  		v.pb(a);
  		cnt1 += a > 1;
  		cnt2 += a > 2;
  	}

  	int tmp;
  	assert(scanf("%d",&tmp) != 1);

  	sort(v.begin(),v.end(),greater<int>());

  	if (sum != 2*n - 2){
  		printf("None\n");                
  	} else if (cnt1 <= 2 || cnt2 == 0 || (cnt1 == 3 && v[0] == v[2])){
  		printf("Unique\n");
  	} else {
  		printf("Multiple\n");
  	}
      
  TIMESTAMP(end);
  return 0;
}
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
#define TASKMOD "large"

typedef long long ll;
typedef long double ld;

void PreCalc(){
}

void solve(){
	int n;
	scanf("%d",&n);
	vector<int> v(n);
	int p, q, r, s;
	scanf("%d %d %d %d",&p,&q,&r,&s);

	ll sum = 0;
	for (int i = 0; i < n; i++) {
		v[i] = (i * 1LL * p + q) % r + s;
		sum += v[i];
	}
	ll L = -1;
	ll R = sum;
	while (R - L > 1) {
		ll mid = (L + R) / 2;
		int ptr = 0;
		for (int i = 0; i < 3; i++) {
			ll cur = mid;
			while (ptr < n && cur >= v[ptr])
				cur -= v[ptr++];
		}
		if (ptr == n)
			R = mid;
		else
			L = mid;
	}

	printf("%.18lf\n", ((double)(sum - R))/sum);	
}


int main(){
  freopen(TASKNAME"-"TASKMOD".in","r",stdin);
  freopen(TASKNAME"-"TASKMOD".out","w",stdout);
	
  PreCalc();
  TIMESTAMP(PreCalc);	

  char buf[1000];
  int testNum;
  gets(buf);
  sscanf(buf,"%d",&testNum);

  for (int testId = 1; testId <= testNum; testId++){
  	if (testId <= 20 || testId >= testNum - 20 || testId % 10 == 0)
	  	TIMESTAMPf("Test %d",testId);
  	printf("Case #%d: ",testId);
  	solve();                        
  }
      
  TIMESTAMP(end);
  return 0;
}
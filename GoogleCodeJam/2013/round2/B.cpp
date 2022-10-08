#include <iostream>
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

#define TASKNAME "B"
#define TASKMOD "large"

typedef long long ll;
typedef long double ld;

void PreCalc(){
}

ll getBad(int level,ll cnt){
	if (cnt == 0) 
		return 0;
    return getBad(level - 1, (cnt - 1) / 2) + (1LL << (level - 1));
}

ll getGood(int level,ll cnt){
    if (cnt == (1LL<<level)-1)
    	return (1LL<<level)-1;
    return getGood(level - 1, (cnt + 1) / 2);
}

ll getAlways(int n, ll cnt){
	ll L = 0;
	ll R = (1ll<<n);
	while (R - L > 1){
		ll mid = (L + R) / 2;
		if (getBad(n, mid) < cnt)
			L = mid;
		else
			R = mid;
	}
	return L;
}

ll getCan(int n, ll cnt){
	ll L = 0;
	ll R = (1ll<<n);
	while (R - L > 1){
		ll mid = (L + R) / 2;
		if (getGood(n, mid) < cnt)
			L = mid;
		else
			R = mid;
	}
	return L;
}


void solve(){
	ll n,p;
	cin >> n >> p;
	cout << getAlways(n,p) <<" "<<getCan(n,p) << endl;
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
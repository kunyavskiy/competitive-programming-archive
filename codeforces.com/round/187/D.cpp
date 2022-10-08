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

const int MAXN = 110000;

pair<ll,ll> p[MAXN];
int n;


bool check(ll dist){
	multiset<ll> sec;

	for (int i = 0; i < n; i++)
		sec.insert(p[i].second);

	int ptr = 0;
	for (int i = 0; i < n; i++){
		while (ptr < n && p[ptr].first - p[i].first <= dist){
			sec.erase(sec.find(p[ptr].second));
			ptr++;
		}
		if (sec.empty() || *sec.rbegin() - *sec.begin() <= dist)
			return true;
		sec.insert(p[i].second);
	}
	return false;
}


int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif
  	scanf("%d",&n);

  	for (int i = 0; i < n; i++){
  		int _x,_y;
  		scanf("%d %d",&_x,&_y);
  		p[i] = mp(_x + _y,_x - _y);
  	}

  	sort(p,p+n);

  	ll L = -1;
  	ll R = p[n-1].first - p[0].first;

  	for (int i = 0; i < 21; i++){
  		ll mid = (L + R)/2;
//  		eprintf(LLD" "LLD"\n",L,R);
  		if (check(mid))
  			R = mid;
  		else
  			L = mid;
  	}

  	R = (L+R+1)/2;

  	
  	printf(LLD"."LLD,R / 2, (R % 2) * 5);
      
    TIMESTAMP(end);
    return 0;
}
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

#define TASKNAME "1942"

typedef long long ll;
typedef long double ld;

int read(){
	double temp;
	scanf("%lf",&temp);
	int val = round(temp * 1000);
	val = (val % 1000 + 1000) % 1000;
	if (val > 500)
		val -= 1000;
	return val;
}

int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif

  	int n;
  	scanf("%d",&n);
    vector<pair<int,int> > a(n);

    for (int i = 0; i < n; i++){
    	int x,y;
    	x = read();
    	y = read();
    	eprintf("%d %d\n",x,y);
    	a[i] = mp(x,y);
    }

    sort(a.begin(),a.end());
    pair<int,int> best;

    for (int i = 0; i < n; ){
    	int j = i;
    	for (; j < n && a[i] == a[j]; j++);
    	best = min(best, mp(i - j, a[i].first * a[i].first + a[i].second * a[i].second));
    	i = j;
    }

    printf("%d %.10lf\n", -best.first,sqrt(best.second)/1000.0);    	
    TIMESTAMP(end);
    return 0;
}
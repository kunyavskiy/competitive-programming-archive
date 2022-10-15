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

#define TASKNAME "1328"

typedef long long ll;
typedef long double ld;


ld angle(int x,int y){
	ld res = atan2(y,x);
	if (y < 0 || res < 0)
		res += 2*M_PI;
	res = max(res, ld(0));
	return res / M_PI * 180;
}

const int M = 200;

int w,h;

int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif

    int n;
    int x1,y1,x2,y2;

    scanf("%d %d %d %d %d %d %d",&w,&h,&n,&x1,&y1,&x2,&y2);


    ll anslen;
    ld ansang;
    anslen = 1<<30;
    ansang = 1e100;

    for (int i = -M; i <= M; i++)
    for (int j = -M; j <= M; j++){
    	int nx2 = i * w + (i % 2 == 0 ? x2 : w - x2);
    	int ny2 = j * h + (j % 2 == 0 ? y2 : h - y2);
    	if (abs(i) + abs(j)  != n) continue;
    	ll dist = (x1 - nx2) * 1LL* (x1 - nx2) + (y1 - ny2) *1LL* (y1 - ny2);
//    	eprintf(LLD" %.5lf\n",dist, (double)angle(nx2 - x1, ny2 - y1));
    	if (anslen > dist){
    		anslen = dist; 
    		ansang = 1e100;
    	}
    	if (anslen == dist){
    		ansang = min(ansang, angle(nx2 - x1, ny2 - y1));
    	}
    }

    printf("%.2lf\n",(double)ansang);
      
    TIMESTAMP(end);
    return 0;
}